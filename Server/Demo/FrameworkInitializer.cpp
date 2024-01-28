module Demo.Framework;
import Iconer.Net;
import <format>;

using namespace iconer;

namespace
{
	const demo::DemoInitializerError network_init_error{ "Error when starting network system." };
	const demo::DemoInitializerError listener_create_error{ "Error when creating the listener socket." };
	const demo::DemoInitializerError listener_bind_error{ "Error when binding a address to the listener socket." };
	const demo::DemoInitializerError completion_port_init_error{ "Error when creating the io completion port." };
	const demo::DemoInitializerError listener_register_error{ "Error when registering the listener." };
	const demo::DemoInitializerError socket_register_error{ "Error when registering a socket." };
	const demo::DemoInitializerError socket_create_error{ "Error when creating a socket." };
	const demo::DemoInitializerError user_awake_error{ "Error when awakening a user." };
}

void
demo::Framework::Awake()
{
	LockPhase();

	myLogger.Awake(L"server.log");
	
	if (const auto startup_err = net::Startup())
	{
		myLogger.LogError(L"Error when starting network system.");

		throw network_init_error;
	}

	myLogger.Log(L"\tcreating the listener...\n");

	if (not CreateListenerSocket())
	{
		throw listener_create_error;
	}

	myLogger.Log(L"\tbinding the listener to port {}...\n", serverPort);

	if (not InitializeListener())
	{
		throw listener_bind_error;
	}

	net::ErrorCode completion_port_error;
	if (not InitializeCompletionPort(completion_port_error))
	{
		throw completion_port_init_error;
	}

	myLogger.Log(L"\tregistering the listener with id {}...\n", serverID);
	if (ioCompletionPort.Register(serverListener, serverID))
	{
		throw listener_register_error;
	}

	myLogger.Log(L"\tallocating memory of buffers...\n");

	userManager.Reserve(maxUsersNumber);
	serverWorkers.reserve(workersCount);

	myLogger.Log(L"\tcreating {} users...\n", maxUsersNumber);
	if (not InitializeUsers())
	{
		throw user_awake_error;
	}

	myLogger.Log(L"\tgenerating {} workers...\n", workersCount);

	for (size_t i = 0; i < workersCount; ++i)
	{
		serverWorkers.emplace_back(Worker, std::ref(*this), i);
	}

	workerAwakens.wait();

	UnlockPhase();
}
