#include <WinSock2.h>
#include <cstdlib>
#include <array>
#include <atomic>
#include <expected>
#include <tuple>
#include <string>
#include <vector>
#include <span>
#include <thread>
#include <iostream>
#include <algorithm>

import Iconer.Net;
import Iconer.Net.ErrorCode;
import Iconer.Net.IpAddress;
import Iconer.Net.EndPoint;
import Iconer.Net.Socket;
import Iconer.Net.IoCompletionPort;
import Test.IoOperation;
import Test.Context;
import Test.ChatMsgContext;
import Test.Client;
import Test.Packet;

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

namespace test
{
	struct ServerPreset
	{
		std::uintptr_t serverID;
		iconer::net::EndPoint serverAddress;
	};

	struct EncapsuledSocket
	{
		[[nodiscard]]
		inline constexpr friend bool operator<(const EncapsuledSocket& lhs, const EncapsuledSocket& rhs) noexcept
		{
			return lhs.id < rhs.id;
		}

		iconer::net::Socket* sk;
		std::uint64_t id;
	};

	class Framework final
	{
	public:
		using ChatBroadcastingResult = std::expected<unsigned int, std::tuple<iconer::net::ErrorCode, std::uintptr_t>>;
		static constexpr std::size_t maxClientsNumber = 40;
		static constexpr std::size_t sizeRecvBuffer = 256;
		static constexpr std::size_t oneBufferSize = maxClientsNumber * sizeRecvBuffer;
		static constexpr std::uintptr_t clientIdOffset = 1;

		Framework() noexcept;
		~Framework() noexcept;

		/// <summary>
		/// Initialize the framework
		/// </summary>
		/// <param name="setup">Settings of server</param>
		void Awake(ServerPreset&& setup);
		/// <summary>
		/// Start update
		/// </summary>
		/// <param name="concurrent_hint">Number of workers</param>
		void Start(size_t concurrent_hint);
		/// <summary>
		/// Remove framework's resource
		/// </summary>
		void Destroy();
		/// <summary>
		/// Clean every system resources up
		/// </summary>
		void Cleanup();

		iconer::net::Socket::SocketResult ReserveAccept(const std::uintptr_t& id) const;
		bool CloseClient(const std::uintptr_t& id) const;

		iconer::net::Socket::SocketResult OnAccept(const std::uintptr_t& id);
		[[nodiscard]] iconer::net::Socket::SocketResult OnReceive(const std::uintptr_t& id, const size_t& bytes);
		// ChatBroadcastingResult
		[[nodiscard]] size_t OnChat(test::ChatMsgContext* sender);
		iconer::net::Socket::SocketResult OnClose(const std::uintptr_t& id);

		[[nodiscard]]
		constexpr test::Client& FindClient(const std::uintptr_t& id) const
		{
			return *everyClients[GetIndexByID(id)];
		}

		[[nodiscard]]
		static constexpr size_t GetIndexByID(const std::uintptr_t& id) noexcept
		{
			return id - clientIdOffset;
		}

		[[nodiscard]]
		static constexpr std::uintptr_t GetIDByIndex(const size_t& index) noexcept
		{
			return index + clientIdOffset;
		}

	private:
		using data_t = std::vector<EncapsuledSocket>;
		using iterator = data_t::iterator;
		using const_iterator = data_t::const_iterator;
		using view_t = std::span<EncapsuledSocket>;
		using const_view_t = std::span<const EncapsuledSocket>;
		using seek_t = std::ranges::subrange<iterator>;
		using const_seek_t = std::ranges::subrange<const_iterator>;
		using size_type = data_t::size_type;

		void AddSocket(iconer::net::Socket* const& socket_ptr, const std::uintptr_t id);
		[[nodiscard]]
		bool TryAddSocket(iconer::net::Socket* const& socket_ptr, const std::uintptr_t id) noexcept;
		iconer::net::Socket* const AllocateSocket(std::uintptr_t id, iconer::net::IoCategory type, const iconer::net::InternetProtocol& protocol, const iconer::net::IpAddressFamily& family);

		[[nodiscard]]
		bool Schedule(iconer::net::IoContext& context, std::uintptr_t id, unsigned long infobytes) noexcept
		{
			return myStation.Schedule(context, std::move(id), std::move(infobytes));
		}
		[[nodiscard]]
		bool Schedule(iconer::net::IoContext* const context, std::uintptr_t id, unsigned long infobytes) noexcept
		{
			return myStation.Schedule(context, std::move(id), std::move(infobytes));
		}
		[[nodiscard]]
		auto WaitForIoResult() noexcept
		{
			return myStation.WaitForIoResult();
		}

		[[nodiscard]]
		std::span<std::byte, Framework::sizeRecvBuffer>
			GetBuffer(const std::uintptr_t& id)
			noexcept
		{
			std::byte* buf = this->clientsRecvBuffer.data();
			auto* data = buf + GetIndexByID(id) * Framework::sizeRecvBuffer;
			return std::span<std::byte, Framework::sizeRecvBuffer>(data, sizeRecvBuffer);
		}

		[[nodiscard]]
		std::span<const std::byte, Framework::sizeRecvBuffer>
			GetBuffer(const std::uintptr_t& id)
			const noexcept
		{
			const std::byte* buf = clientsRecvBuffer.data();
			auto* data = buf + GetIndexByID(id) * Framework::sizeRecvBuffer;
			return std::span<const std::byte, Framework::sizeRecvBuffer>(data, sizeRecvBuffer);
		}

		friend void Worker(test::Framework&, size_t);

		Framework(const Framework&) = delete;
		Framework(Framework&&) = delete;
		void operator=(const Framework&) = delete;
		void operator=(Framework&&) = delete;

		iconer::net::Socket myListener;
		std::array<test::Client*, test::Framework::maxClientsNumber> everyClients;
		data_t everySockets;
		iconer::net::IoCompletionPort myStation;

		// all-in-one circular buffer
		std::array<std::byte, test::Framework::oneBufferSize> clientsRecvBuffer;
		volatile std::atomic_size_t clientsNumber;
		std::vector<std::jthread> myWorkers;
	};

	void Worker(test::Framework& framework, size_t nth);
}

test::Framework serverFramework{};

int main()
{
	std::cout << ("=========$ Server $=========\n");
	test::ServerPreset my_setup
	{
		.serverID = 0,
		.serverAddress = iconer::net::EndPoint{ iconer::net::IpAddress{ iconer::net::IpAddressFamily::IPv4, "127.0.0.1" }, 40000 }
	};

	std::cout << ("=========== Init ===========\n");
	serverFramework.Awake(std::move(my_setup));

	std::cout << ("=========== Start ===========\n");
	serverFramework.Start(6);

	std::cout << ("=========== Update ===========\n");

	char command[256]{};
	constexpr unsigned cmd_size = sizeof(command);

	while (true)
	{
		auto input = ::scanf_s("%s", command, cmd_size);
		if (EOF != input)
		{
			if (command[0] == 'q')
			{
				break;
			}
		}
	}

	std::cout << ("========== Destroy ===========\n");
	serverFramework.Destroy();

	std::cout << ("========== Clean up ==========\n");
	serverFramework.Cleanup();
}

void
test::Worker(Framework& framework, size_t nth)
{
	std::cout << std::format("Worker {} is started.\n", nth);

	while (true)
	{
		//if (not socket_pool.IsAvailable())
		{
			//	break;
		}

		auto io_event = framework.WaitForIoResult();
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
						std::cout << std::format("Worker has been failed as acceptance on {}\n", id);
						break; // switch (op)
					}

					std::cout << std::format("Client connected - {}\n", id);
					auto rr = framework.OnAccept(id);
					if (rr)
					{
						std::cout << std::format("Client {}'s receive are not able to be reserved ({})\n", id, rr.value());
					}
					else
					{
						std::cout << std::format("Client {}'s receive are reserved\n", id);
					}
				}
				break;

				case test::IoOperation::Recv:
				{
					if (not io_event.isSucceed)
					{
						std::cout << std::format("Worker has been failed as receiving on client {}\n", id);

						framework.CloseClient(id);
						break; // switch (op)
					}

					auto& bytes = io_event.ioBytes;
					if (0 == bytes)
					{
						std::cout << std::format("Closing client {} as receiving has been failed\n", id);

						framework.CloseClient(id);
						break; // switch (op)
					}

					// Restart receive
					auto rr = framework.OnReceive(id, bytes);
					if (rr)
					{
						std::cout << std::format("Client {}'s receive are not able to be reserved ({})\n", id, rr.value());

						framework.CloseClient(id);
						break; // switch (op)
					}
					else
					{
						std::cout << std::format("Client {}'s receive are reserved\n", id);
					}
				}
				break;

				case test::IoOperation::Send:
				{
					const auto& bytes = io_event.ioBytes;

					if (not io_event.isSucceed)
					{
						std::cout << std::format("Worker has been failed as sending on the client {}\n", id);

						if (ex_context != nullptr)
						{
							delete ex_context;
						}

						if (0 == bytes)
						{
							std::cout << std::format("Closing client {} as sending has been failed\n", id);

							framework.CloseClient(id);
						}

						break; // switch (op)
					}

					// Specialization for chat msgs
					auto msg_ctx = static_cast<ChatMsgContext*>(ex_context);
					if (nullptr != msg_ctx)
					{
						std::cout << std::format("Message sent from the client {}\n", id);

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
						std::cout << std::format("An msg error occured on the client {}\n", id);
						std::abort();
						break;
					}

					auto br = framework.OnChat(msg_ctx);
					if (br == 0)
					{
						std::cout << std::format("Client {} has been failed on sending message(s)\n", id);
						//auto& err = br.error();

						//std::cout << std::format("Client {} cannot send message to {}, due to {}", id, std::get<1>(err), std::get<0>(err));
					}
				}
				break;

				case test::IoOperation::Close:
				{
					std::cout << std::format("Client {} is closed\n", id);

					// start acceptance again
					auto acceptance = framework.OnClose(id);
					if (acceptance)
					{
						std::cout << std::format("Client {} cannot be accepted due to {}\n", id, acceptance.value());

						std::abort();
						break; // switch (op)
					}
				}
				break;

				default:
				{
					std::cout << std::format("Unknown task on {}\n", id);
				}
			}
		}
	}
}

test::Framework::Framework()
noexcept
	: myListener(), myStation()
	, everyClients(), everySockets()
	, clientsRecvBuffer(), clientsNumber()
{
	everySockets.reserve(maxClientsNumber);
}

test::Framework::~Framework()
noexcept
{}

void
test::Framework::Awake(test::ServerPreset&& setup)
{
	iconer::net::Startup();

	myListener = iconer::net::Socket::Create(iconer::net::IoCategory::Asynchronous, iconer::net::InternetProtocol::TCP, iconer::net::IpAddressFamily::IPv4);

	myListener.Bind(std::move(setup.serverAddress));
	myListener.IsAddressReusable = true;

	myStation = iconer::net::IoCompletionPort::Create(6).value();

	AddSocket(&myListener, std::move(setup.serverID));
	std::cout << "The listener is ready.\n";

	size_t client_index = 0;
	for (auto*& client : everyClients)
	{
		const auto id = GetIDByIndex(client_index);

		client = new test::Client{};
		client->myID = id;
		client->mySocket = AllocateSocket(id, iconer::net::IoCategory::Asynchronous, iconer::net::InternetProtocol::TCP, iconer::net::IpAddressFamily::IPv4);
		client->mySocket->IsAddressReusable = true;

		auto& ctx = client->myContext;

		ctx = test::ExContext{ id, test::IoOperation::None };

		++client_index;
	}
	std::cout << "Client prefabs are ready.\n";
}

void
test::Framework::Start(size_t concurrent_hint)
{
	if (myListener.Open().has_value())
	{
		std::cout << "The listener is opened.\n";
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
	std::cout << "Clients are reverved to accept.\n";
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
	iconer::net::Cleanup();
}

void
test::Framework::AddSocket(iconer::net::Socket* const& socket_ptr, const std::uint64_t id)
{
	if (myStation.Register(*socket_ptr, id))
	{
		everySockets.push_back(EncapsuledSocket{ socket_ptr, id });
		std::sort_heap(everySockets.begin(), everySockets.end());
	}
}

bool
test::Framework::TryAddSocket(iconer::net::Socket* const& socket_ptr, const std::uint64_t id)
noexcept
{
	if (myStation.Register(*socket_ptr, id))
	{
		try
		{
			everySockets.push_back(EncapsuledSocket{ socket_ptr, id });
			std::sort_heap(everySockets.begin(), everySockets.end());
		}
		catch (...)
		{
			return false;
		}

		return true;
	}

	return false;
}

iconer::net::Socket* const
test::Framework::AllocateSocket(const std::uint64_t id, iconer::net::IoCategory type, const iconer::net::InternetProtocol& protocol, const iconer::net::IpAddressFamily& family)
{
	auto sk_result = iconer::net::Socket::Create(type, protocol, family);
	if (sk_result.IsAvailable())
	{
		auto sk = new iconer::net::Socket{ std::move(sk_result) };

		if (myStation.Register(*sk, id))
		{
			auto& ck = everySockets.emplace_back();
			ck.sk = sk;
			ck.id = id;

			return ck.sk;
		}
		else
		{
			sk->Close();
			delete sk;
		}
	}

	return nullptr;
}

iconer::net::Socket::SocketResult
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

iconer::net::Socket::SocketResult
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

iconer::net::Socket::SocketResult
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

	if (Schedule(msg_ctx, id, static_cast<unsigned long>(bytes)))
	{
		failsafe.ok = true;
	}
	else
	{
		std::cout << std::format("Worker cannot schedule a broadcasting on the client {}\n", id);
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

iconer::net::Socket::SocketResult
test::Framework::OnClose(const std::uintptr_t& id)
{
	--clientsNumber;

	return ReserveAccept(id);
}
