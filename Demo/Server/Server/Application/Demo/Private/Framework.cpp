module;
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <MSWSock.h>

module Demo.Framework;
import <memory>;
// ReSharper disable CppMemberFunctionMayBeStatic

demo::Framework::Framework(size_t clients_count, std::uint16_t port)
	: serverWorkers(), workerCanceller()
	, listenSocket(), listenContext()
	, everyUsers(clients_count)
	, cancellationSource()
{}

void
demo::Framework::Awake()
{
	iconer::user_id_t id = startUserID;

	everyUsers.ConstructPool(startUserID);
	serverWorkers.reserve(workersCount);
}

bool
demo::Framework::Start() noexcept
{
	bool result = true;
	for (auto& user_ptr : everyUsers)
	{
		const auto user = user_ptr.get();

		if (not user->SetState<iconer::user_status::Listening>())
		{
			result = false;
		}
	}

	try
	{
		for (size_t i = 0; i < workersCount; ++i)
		{
			auto worker = new std::jthread{ Worker, workerCanceller.get_token() };
			
			serverWorkers.push_back(worker);
		}
	}
	catch (...)
	{
		return false;
	}

	return result;
}

void
demo::Framework::Update()
{
	while (true)
	{
		if (workerCanceller.stop_requested())
		{
			break;
		}

		std::this_thread::yield();
	}
}

void
demo::Framework::Cleanup() noexcept
{}

void demo::Worker(Framework& framework, std::stop_token&& token)
{
	while (true)
	{
		if (token.stop_requested())
		{
			break;
		}

		std::this_thread::yield();
	}
}

