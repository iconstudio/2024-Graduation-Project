module;
#include <string>
#include <string_view>

module Demo.Framework;
import Iconer.Net;
import Iconer.Application.UserManager;
import Iconer.Application.Packet;

using namespace iconer;

namespace
{
	const demo::DemoInitializerError network_init_error{ "Error when starting network system." };
	const demo::DemoInitializerError listener_create_error{ "Error when creating listener sockets." };
	const demo::DemoInitializerError listener_bind_error{ "Error when binding a address to the lobby socket." };
	const demo::DemoInitializerError game_listener_bind_error{ "Error when binding a address to the game socket." };
	const demo::DemoInitializerError completion_port_init_error{ "Error when creating the io completion port." };
	const demo::DemoInitializerError listener_register_error{ "Error when registering the listener." };
	const demo::DemoInitializerError socket_register_error{ "Error when registering a socket." };
	const demo::DemoInitializerError socket_create_error{ "Error when creating a socket." };
	const demo::DemoInitializerError user_awake_error{ "Error when awakening a user." };
	const demo::DemoInitializerError room_create_error{ "Error when creating rooms." };
}

void
demo::Framework::Awake()
{
	LockPhase();

	using namespace std::string_view_literals;
	myLogger.Awake(L"server.log"sv);

	if (const auto startup_err = net::Startup())
	{
		myLogger.LogError(L"Error {} occured when starting network system.", startup_err.value());

		throw network_init_error;
	}

	myLogger.Log(L"\tcreating listener sockets...\n");

	if (not CreateListenerSockets())
	{
		throw listener_create_error;
	}

	myLogger.Log(L"\tbinding the lobby listener to port {}...\n", lobbySidePort);

	if (not InitializeLobbyListener())
	{
		throw listener_bind_error;
	}

	myLogger.Log(L"\tbinding the game listener to port {}...\n", gameSidePort);

	if (not InitializeGameListener())
	{
		throw game_listener_bind_error;
	}

	net::ErrorCode completion_port_error;
	if (not InitializeCompletionPort(completion_port_error))
	{
		throw completion_port_init_error;
	}

	myLogger.Log(L"\tregistering the lobby listener with id {}...\n", lobbyServerID);
	if (ioCompletionPort.Register(serverListener, lobbyServerID))
	{
		throw listener_register_error;
	}

	myLogger.Log(L"\tregistering the game listener with id {}...\n", gameServerID);
	if (ioCompletionPort.Register(gameListener, gameServerID))
	{
		throw listener_register_error;
	}

	myLogger.Log(L"\tcreating session managers..\n");
	userManager = new iconer::app::UserManager{};

	myLogger.Log(L"\tallocating memory of buffers...\n");
	recvSpace = std::make_unique<std::byte[]>(userRecvSize * maxUsersNumber);
	userSpace = std::make_unique<app::User[]>(maxUsersNumber);
	serializedRoomsBuffer = std::make_unique<std::byte[]>(iconer::app::packets::SC_RespondRoomsPacket::MaxSize());

	iconer::app::packets::SC_RespondRoomsPacket rooms_pk{};
	rooms_pk.Write(serializedRoomsBuffer.get());

	myLogger.Log(L"\tallocating space of objects...\n");
	userManager->Reserve(maxUsersNumber);
	serverWorkers.reserve(workersCount);

	myLogger.Log(L"\tcreating {} users...\n", maxUsersNumber);
	if (not InitializeUsers())
	{
		throw user_awake_error;
	}

	myLogger.Log(L"\tcreating {} rooms...\n", maxRoomsNumber);
	if (not InitializeRooms())
	{
		throw room_create_error;
	}

	myLogger.Log(L"\tcreating {} contexts...\n", initSendContextsNumber);
	CacheSendContexts();

	myLogger.Log(L"\tgenerating {} workers...\n", workersCount);

	for (size_t i = 0; i < workersCount; ++i)
	{
		serverWorkers.emplace_back(Worker, std::ref(*this), i);
	}

	workerAwakens.wait();

	UnlockPhase();
}
