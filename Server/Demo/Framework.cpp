module;
#include <Windows.h>
#include <cstdint>
#include <utility>

module Demo.Framework;
import Iconer.Net;
import Iconer.Net.ErrorCode;
import Iconer.Application.User;

using namespace iconer;

constexpr std::uint16_t serverPort{ 40000 };
constexpr app::User::HandleType serverID = 0;

void Framework::Awake()
{
	myLogger.Awake(L"server.log");

	if (const auto startup_err = net::Startup())
	{
		myLogger.LogError(L"Error when starting network system.");

		throw std::exception{ "Error when starting network system." };
	}

	myLogger.Log(L"\tcreating the listener...\n");

	if (not net::Socket::TryCreate(net::IoCategory::Asynchronous, net::InternetProtocol::TCP, net::IpAddressFamily::IPv4, serverListener))
	{
		throw std::exception{ "Error when creating the listener socket." };
	}

	myLogger.Log(L"\tbinding the listener to port {}...\n", ::serverPort);

	serverListener.BindHost(::serverPort).and_then(
		[](net::ErrorCode&& code) -> std::optional<bool> {
		const std::string msg = std::format("Error when binding a address to the listener socket ({})", code);
		throw msg;
	});

	auto result = net::IoCompletionPort::Create(uint32_t(workersCount)).and_then(
		[&](net::IoCompletionPort&& port) noexcept -> std::expected<bool, net::ErrorCode> {
		ioCompletionPort = std::move(port);
		return true;
	}).transform_error([](net::ErrorCode&& code) noexcept -> std::expected<bool, net::ErrorCode> {
		return false;
	});

	if (not result.value())
	{
		throw std::exception{ "Error when creating the io completion port." };
	}

	myLogger.Log(L"\tregistering the listener with id {}...\n", ::serverID);
	if (ioCompletionPort.Register(serverListener, serverID))
	{
		throw std::exception{ "Error when registering the listener." };
	}

	myLogger.Log(L"\tallocating memory of buffers...\n");

	userManager.Reserve(userNumber);
	serverWorkers.reserve(workersCount);

	auto user_factory = app::SessionFactory<app::User>{};

	myLogger.Log(L"\tcreating {} users...\n", userNumber);

	app::User::HandleType id = beginUserID;
	for (size_t i = 0; i < userNumber; ++i)
	{
		net::Socket socket;
		if (not net::Socket::TryCreate(net::IoCategory::Asynchronous, net::InternetProtocol::TCP, net::IpAddressFamily::IPv4, socket))
		{
			throw std::exception{ "Error when creating a socket." };
		}

		if (not ioCompletionPort.Register(socket, id))
		{
			//auto user = user_factory.Create(std::move(socket), id++);
			app::User user{ std::move(socket), id++ };
			userManager.Add(std::move(user));
		}
		else
		{
			throw std::exception{ "Error when registering a socket." };
		}
	}

	myLogger.Log(L"\tgenerating {} workers...\n", workersCount);

	for (size_t i = 0; i < workersCount; ++i)
	{
		serverWorkers.emplace_back(::Worker, std::ref(*this), i);
	}

	myLogger.Log(L"\tawakening users...\n");

	for (auto& [id, user] : userManager)
	{
		if (not user.OnAwake())
		{
			throw std::exception{ "Error when awakening a user." };
		}
	}

	::Sleep(10);
}

void Framework::Update()
{
	char command[256]{};
	constexpr unsigned cmd_size = sizeof(command);

	while (true)
	{
		auto input = ::scanf_s("%s", command, cmd_size);
		if (EOF != input)
		{
			if (command[0] == 'q')
			{
				CancelWorkers();

				break;
			}
		}
	}
}

void Framework::Destroy()
{
}

void Framework::Cleanup()
{
	const auto cleanup_err = net::Cleanup();

	myLogger.Cleanup();
}
