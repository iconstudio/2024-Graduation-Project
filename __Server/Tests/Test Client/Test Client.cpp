#pragma comment(lib, "Modern Network.lib")
#include <windows.h>
#include <cstdlib>
#include <cstddef>
#include <string>
#include <string_view>
import <span>;
import <deque>;
import <print>;

import Net;
import Net.IpAddress;
import Net.IpAddress.IPv4;
import Net.Socket;
import Net.Coroutine;
import Net.Task;
import Net.Io.Context;

net::Socket client = net::Socket::EmptySocket;

std::byte sendBuffer[256]{};
net::io::Context sendContext{};
static inline constexpr auto sendBufferSize = static_cast<unsigned>(sizeof(sendBuffer));
std::byte recvBuffer[256]{};
net::io::Context recvContext{};
std::deque<std::string> chatContents{};
static inline constexpr size_t chatMaxCount = 20;

[[nodiscard]]
std::string_view as_string(const std::span<const std::byte> buffer) noexcept;
[[nodiscard]]
std::string_view as_string(const std::span<const std::byte> buffer, const size_t size) noexcept;

void AddChatMessage(std::string_view msg);
void PresentChat();

net::Coroutine Worker();
net::Coroutine Presenter();

int main()
{
	std::println("=========$ Client $=========");
	std::println("=========== Init ===========");
	net::core::Initialize();

	std::println("=========== Awake ===========");
	client = net::Socket::Create(net::SocketType::Asynchronous, net::InternetProtocols::TCP, net::IpAddressFamily::IPv4);

	std::println("=========== Start ===========");

	if (client.Bind(net::IPv4Address::Loopback, 52001).has_value())
	{
		std::println("The client is binded!");
	}

	client.IsAddressReusable = true;

	const net::EndPoint serverAddress{ net::IPv4Address::Loopback, 10000 };
	if (auto cr = client.Connect(serverAddress); cr)
	{
		std::println("The client is connected!");
	}
	else
	{
		std::println("The client cannot be connected due to {}", cr.error());
	}

	std::println("=========== Update ===========");

	auto w = Worker();
	auto p = Presenter();
	w.StartAsync();
	p.Start();

	while (true)
	{}

	net::core::Annihilate();
	return 0;
}

net::Coroutine Worker()
{
	auto buffer = reinterpret_cast<char*>(sendBuffer);

	while (true)
	{
		const int scan = scanf_s("%s", sendBuffer, sendBufferSize);

		if (EOF != scan)
		{
			auto sent = client.Send(sendContext, sendBuffer, as_string(sendBuffer).size());
			if (not sent)
			{
				std::println("The client cannot send due to {}", sent.error());
				break;
			}
			else if (sent != 0)
			{
				//std::println("The client sent: {}", buffer);
			}

			sendContext.Clear();
		}
	}

	co_return;
}

net::Coroutine Presenter()
{
	co_await net::coroutine::WaitForSeconds(1);

	while (true)
	{
		auto receiver = client.MakeReceiveTask(recvContext, recvBuffer, sizeof(recvBuffer));

		auto recv = co_await receiver;
		if (not recv)
		{
			std::println("The client cannot receive due to {}", recv.error());
			break;
		}
		else if (recv != 0)
		{
			//std::println("{}", as_string(recvBuffer));
			AddChatMessage(as_string(recvBuffer));
			PresentChat();
		}

		recvContext.Clear();
		std::fill(std::begin(recvBuffer), std::end(recvBuffer), std::byte{ 0 });
	}
}

static inline constexpr std::string_view chatTitle{ "===============$ Client $==============" };
static inline constexpr std::string_view chatMsgFormatter{ "{:^40}" };

void PresentChat()
{
	::system("cls");
	std::println(chatTitle);
	for (const auto& msg : chatContents)
	{
		std::println(chatMsgFormatter, msg);
	}
}

void AddChatMessage(std::string_view msg)
{
	if (chatMaxCount <= chatContents.size())
	{
		chatContents.pop_front();
	}

	chatContents.emplace_back(std::move(msg));
}

std::string_view
as_string(const std::span<const std::byte> buffer)
noexcept
{
	return std::string_view{ reinterpret_cast<const char*>(buffer.data()) };
}

std::string_view
as_string(const std::span<const std::byte> buffer, const size_t size)
noexcept
{
	return std::string_view{ reinterpret_cast<const char*>(buffer.data()), size };
}
