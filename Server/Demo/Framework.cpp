module;
#include <Windows.h>
#include <cstdint>
#include <utility>

module Demo.Framework;
import Iconer.Net;
import Iconer.Net.ErrorCode;
import Iconer.Application.User;

using namespace iconer;

static DemoInitializerError network_init_error{ "Error when starting network system." };
static DemoInitializerError listener_create_error{ "Error when creating the listener socket." };
static DemoInitializerError completion_port_init_error{ "Error when creating the io completion port." };
static DemoInitializerError listener_register_error{ "Error when registering the listener." };
static DemoInitializerError socket_register_error{ "Error when registering a socket." };
static DemoInitializerError socket_create_error{ "Error when creating a socket." };
static DemoInitializerError user_awake_error{ "Error when awakening a user." };

void Framework::Awake()
{
	myLogger.Awake(L"server.log");

	if (const auto startup_err = net::Startup())
	{
		myLogger.LogError(L"Error when starting network system.");

		throw network_init_error;
	}

	myLogger.Log(L"\tcreating the listener...\n");

	if (not net::Socket::TryCreate(net::IoCategory::Asynchronous, net::InternetProtocol::TCP, net::IpAddressFamily::IPv4, serverListener))
	{
		throw listener_create_error;
	}

	myLogger.Log(L"\tbinding the listener to port {}...\n", serverPort);

	serverListener.BindHost(serverPort).and_then(
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

	if (not result.value_or(false))
	{
		throw completion_port_init_error;
	}

	myLogger.Log(L"\tregistering the listener with id {}...\n", serverID);
	if (ioCompletionPort.Register(serverListener, serverID))
	{
		throw listener_register_error;
	}

	myLogger.Log(L"\tallocating memory of buffers...\n");

	userManager.Reserve(usersNumber);
	serverWorkers.reserve(workersCount);

	auto user_factory = app::SessionFactory<app::User>{};

	myLogger.Log(L"\tcreating {} users...\n", usersNumber);

	auto id = beginUserID;
	for (size_t i = 0; i < usersNumber; ++i)
	{
		if (net::Socket socket; net::Socket::TryCreate(net::IoCategory::Asynchronous, net::InternetProtocol::TCP, net::IpAddressFamily::IPv4, socket))
		{
			if (not ioCompletionPort.Register(socket, id).has_value())
			{
				//auto user = user_factory.Create(std::move(socket), id++);
				app::User user{ std::move(socket), id++ };
				userManager.Add(std::move(user));
			}
			else
			{
				throw socket_register_error;
			}
		}
		else
		{
			throw socket_create_error;
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
			throw user_awake_error;
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
