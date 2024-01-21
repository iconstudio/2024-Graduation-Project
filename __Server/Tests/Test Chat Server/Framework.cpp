module;
#include <atomic>
#include <algorithm>
#include <print>

module Test.Framework;
import <thread>;

struct [[nodiscard]] MemoryFailsafe
{
	~MemoryFailsafe()
	{
		if (not ok and ptr)
		{
			delete ptr;
		}
	}

	bool ok;
	test::ChatMsgContext* ptr;
};

void
test::Worker(Framework& framework, size_t nth)
{
	std::println("Worker {} is started", nth);

	auto& socket_pool = framework.everySockets;

	while (true)
	{
		if (not socket_pool.IsAvailable())
		{
			break;
		}

		auto io_event = socket_pool.WaitForIoResult();
		auto& io_context = io_event.ioContext;
		auto& io_id = io_event.eventId;

		auto ex_context = static_cast<test::ExContext*>(io_context);
		if (ex_context)
		{
			ex_context->Clear();

			auto& op = ex_context->myOperation;
			const auto& id = ex_context->myID;

			switch (op)
			{
				case test::IoOperation::Accept:
				{
					if (not io_event.isSucceed)
					{
						std::println("Worker has been failed as acceptance on {}", id);
						break; // switch (op)
					}

					std::println("Client connected - {}", id);
					auto rr = framework.OnAccept(id);
					if (rr)
					{
						std::println("Client {}'s receive are reserved", id);
					}
					else
					{
						std::println("Client {}'s receive are not able to be reserved ({})", id, rr.error());
					}
				}
				break;

				case test::IoOperation::Recv:
				{
					if (not io_event.isSucceed)
					{
						std::println("Worker has been failed as receiving on client {}", id);

						framework.CloseClient(id);
						break; // switch (op)
					}

					auto& bytes = io_event.ioBytes;
					if (0 == bytes)
					{
						std::println("Closing client {} as receiving has been failed", id);

						framework.CloseClient(id);
						break; // switch (op)
					}

					// Restart receive
					auto rr = framework.OnReceive(id, bytes);
					if (rr)
					{
						std::println("Client {}'s receive are reserved", id);
					}
					else
					{
						std::println("Client {}'s receive are not able to be reserved ({})", id, rr.error());

						framework.CloseClient(id);
						break; // switch (op)
					}
				}
				break;

				case test::IoOperation::Send:
				{
					const auto& bytes = io_event.ioBytes;

					if (not io_event.isSucceed)
					{
						std::println("Worker has been failed as sending on the client {}", id);

						if (ex_context != nullptr)
						{
							delete ex_context;
						}

						if (0 == bytes)
						{
							std::println("Closing client {} as sending has been failed", id);

							framework.CloseClient(id);
						}

						break; // switch (op)
					}

					// Specialization for chat msgs
					auto msg_ctx = static_cast<ChatMsgContext*>(ex_context);
					if (nullptr != msg_ctx)
					{
						std::println("Message sent from the client {}", id);

						// Preserve the message buffer until they got sent
						if (msg_ctx->refCount.fetch_sub(1) <= 1)
						{
							delete msg_ctx;
						}
					}
					else
					{
						delete ex_context;
					}
				}
				break;

				// Custome event
				case test::IoOperation::BroadcastMessage:
				{
					auto msg_ctx = static_cast<ChatMsgContext*>(ex_context);
					if (nullptr == msg_ctx)
					{
						std::println("An msg error occured on the client {}", id);
						std::abort();
						break;
					}

					auto br = framework.OnChat(msg_ctx);
					if (br == 0)
					{
						std::println("Client {} has been failed on sending message(s)", id);
						//auto& err = br.error();

						//std::println("Client {} cannot send message to {}, due to {}", id, std::get<1>(err), std::get<0>(err));
					}
				}
				break;

				case test::IoOperation::Close:
				{
					std::println("Client {} is closed", id);

					// start acceptance again
					auto acceptance = framework.OnClose(id);
					if (not acceptance)
					{
						std::println("Client {} cannot be accepted due to {}", id, acceptance.error());

						std::abort();
						break; // switch (op)
					}
				}
				break;

				default:
				{
					std::println("Unknown task on {}", id);
				}
			}
		}
	}
}

test::Framework::Framework()
noexcept
	: myListener(net::Socket::EmptySocket)
	, everyClients(), everySockets(maxClientsNumber)
	, clientsRecvBuffer(), clientsNumber()
{}

test::Framework::~Framework()
noexcept
{}

void
test::Framework::Awake(test::ServerPreset&& setup)
{
	net::core::Initialize();

	myListener = net::Socket::Create(net::SocketType::Asynchronous, net::InternetProtocols::TCP, net::IpAddressFamily::IPv4);

	myListener.Bind(std::move(setup.serverAddress));
	myListener.IsAddressReusable = true;

	everySockets.Add(&myListener, std::move(setup.serverID));
	std::println("The listener is ready.");

	size_t client_index = 0;
	for (auto*& client : everyClients)
	{
		const auto id = GetIDByIndex(client_index);

		client = new test::Client{};
		client->myID = id;
		client->mySocket = everySockets.Allocate(id, net::SocketType::Asynchronous, net::InternetProtocols::TCP, net::IpAddressFamily::IPv4);
		client->mySocket->IsAddressReusable = true;

		auto& ctx = client->myContext;

		ctx = test::ExContext{ id, test::IoOperation::None };

		++client_index;
	}
	std::println("Client prefabs are ready.");
}

void
test::Framework::Start(size_t concurrent_hint)
{
	if (myListener.Open().has_value())
	{
		std::println("The listener is opened.");
	}

	myWorkers.reserve(concurrent_hint);
	for (size_t i = 0; i < concurrent_hint; ++i)
	{
		auto& worker = myWorkers.emplace_back(Worker, std::ref(*this), i);
	}

	for (auto*& client : everyClients)
	{
		auto& ctx = client->myContext;

		ctx.ResetOperation(test::IoOperation::Accept);

		auto acceptance = myListener.ReserveAccept(ctx, *client->mySocket);
		if (not acceptance)
		{
			std::abort();
			break;
		}
	}
	std::println("Clients are reverved to accept.");
}

void
test::Framework::Destroy()
{
	for (auto& th : myWorkers)
	{
		th.request_stop();
	}

	for (auto& sk : everySockets)
	{
		sk.sk->Close();
	}
}

void
test::Framework::Cleanup()
{
	net::core::Annihilate();
}

net::SocketResult
test::Framework::ReserveAccept(const std::uintptr_t& id) const
{
	auto& client = FindClient(id);
	auto& socket = client.mySocket;
	auto& context = client.myContext;

	context.ResetOperation(test::IoOperation::Accept);

	return myListener.ReserveAccept(context, *socket);
}

bool
test::Framework::CloseClient(const std::uintptr_t& id) const
{
	auto& client = FindClient(id);
	auto& socket = client.mySocket;
	auto& context = client.myContext;

	context.ResetOperation(test::IoOperation::Close);

	return socket->CloseAsync(context);
}

net::SocketReceivingResult
test::Framework::OnAccept(const std::uintptr_t& id)
{
	auto& client = FindClient(id);
	auto& socket = client.mySocket;
	auto& context = client.myContext;

	context.ResetOperation(test::IoOperation::Recv);

	auto rr = socket->Receive(context, GetBuffer(id));
	if (rr)
	{
		//std::atomic_fetch_add(std::addressof(clientsNumber), 1ULL);
		++clientsNumber;
	}

	return rr;
}

net::SocketReceivingResult
test::Framework::OnReceive(const std::uintptr_t& id, const size_t& bytes)
{
	auto& client = FindClient(id);
	auto& socket = client.mySocket;
	auto& context = client.myContext;

	auto buffer = GetBuffer(id);
	auto buffer_first_it = buffer.cbegin();
	auto buffer_last_it = buffer.cbegin() + bytes;

	std::string temp_msg{};
	temp_msg.reserve(12 + static_cast<size_t>(bytes) * 2);

	temp_msg += std::format("Client {}: ", id);
	while (buffer_first_it != buffer_last_it)
	{
		temp_msg.push_back(static_cast<const char>(*buffer_first_it));
		++buffer_first_it;
	}

	auto msg_ctx = new ChatMsgContext{};
	MemoryFailsafe failsafe{ .ptr = msg_ctx };

	msg_ctx->chatMsg = std::move(temp_msg);
	msg_ctx->myID = id;
	msg_ctx->myOperation = test::IoOperation::BroadcastMessage;
	msg_ctx->refCount = static_cast<int>(clientsNumber.load(std::memory_order_relaxed));

	if (everySockets.Schedule(msg_ctx, id, static_cast<unsigned long>(bytes)))
	{
		failsafe.ok = true;
	}
	else
	{
		std::println("Worker cannot schedule a broadcasting on the client {}", id);
	}

	context.ResetOperation(test::IoOperation::Recv);

	return socket->Receive(context, buffer);
}

//test::Framework::ChatBroadcastingResult
size_t
test::Framework::OnChat(test::ChatMsgContext* sender)
{
	const auto& msg = sender->chatMsg;
	const auto msg_data = reinterpret_cast<const std::byte*>(msg.data());
	const size_t msg_size = msg.size();

	// Do not create another context
	sender->ResetOperation(test::IoOperation::Send);

	size_t count = 0;
	for (auto& ck : everyClients)
	{
		const auto& target_id = ck->myID;

		auto& target = FindClient(target_id);
		auto& target_ctx = target.myContext;
		auto& socket = *ck->mySocket;

		//if (not socket.IsAvailable())
		constexpr auto range = std::array{ test::IoOperation::None, test::IoOperation::Accept };
		if (std::ranges::any_of(range, [&](const test::IoOperation& ops) noexcept {
			return target_ctx.myOperation == ops;
			}))
		{
			continue;
		}

		auto sr = socket.Send(*sender, msg_data, msg_size);
		if (sr)
		{
			++count;
		}
	}

	return count;
}

net::SocketResult
test::Framework::OnClose(const std::uintptr_t& id)
{
	--clientsNumber;

	return ReserveAccept(id);
}
