module Demo.Framework;
import Net;
import <cstdio>;
import <memory>;
import <string>;
import <string_view>;
import <format>;
import <algorithm>;
import <iostream>;
// ReSharper disable CppMemberFunctionMayBeStatic

demo::Framework::Framework(size_t clients_count, std::uint16_t port)
	: serverWorkers(), workerCanceller()
	, listenSocket(), listenContext()
	, everyUsers(clients_count)
	, cancellationSource()
	, myLogger()
{}

void
demo::Framework::Awake()
{
	myLogger.Awake({ L"Log.txt" });

	myLogger.Log(L"# (1) Server system is initiating...\n");

	myLogger.Log(L"# Network system is initiating...\n");
	net::core::Initialize();
	myLogger.Log(L"# Constructing users pool...\n");
	everyUsers.ConstructPool(startUserID);
	myLogger.Log(L"# Constructing workers pool...\n");
	serverWorkers.reserve(workersCount);

	for (size_t i = 0; i < workersCount; ++i)
	{
		auto worker = new std::jthread{ Worker, std::ref(*this), workerCanceller.get_token() };

		serverWorkers.push_back(worker);
	}
}

void
demo::Framework::Start()
{
	myLogger.Log(L"# (2) Server is starting...\n");

	myLogger.Log(L"# Constructing user instances...\n");
	for (auto& user_ptr : everyUsers)
	{
		iconer::User& user = *user_ptr;

		if (not user.SetState<iconer::user_status::Listening>(std::ref(listenSocket)))
		{
			myLogger.LogError(L"Cannot initiate the user");
			//throw "Cannot initiate the user";
		}
	}
}

void
demo::Framework::Update()
{
	myLogger.Log(L"# (3) Server is started\n");

	char input_buffer[256]{};
	while (true)
	{
		const int inputs = ::scanf_s("%s", input_buffer, sizeof(input_buffer));
		if (EOF != inputs and 0 < inputs)
		{
			std::string_view input{ input_buffer };
			if (input == "exit" or input == "quit")
			{
				break;
			}

			std::ranges::fill(input_buffer, 0);
		}
	}

	workerCanceller.request_stop();
}

void
demo::Framework::Cleanup()
noexcept
{
	myLogger.Log(L"# (4) Server system is ended\n");

	myLogger.Log(L"# Network system is destructing...\n");
	net::core::Annihilate();
	myLogger.Cleanup();
}
