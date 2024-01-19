module Demo.Framework;
import Net;
import <cstdlib>;
import <cstdio>;
import <memory>;
import <string>;
import <string_view>;
import <format>;
import <algorithm>;
import <iostream>;
// ReSharper disable CppMemberFunctionMayBeStatic

iconer::util::Logger demo::Framework::serverLogger{};

demo::Framework::Framework(size_t clients_count, std::uint16_t port)
	: serverWorkers(), workerCanceller()
	, listenSocket(), listenContext()
	, everyUsers(clients_count)
	, cancellationSource()
{}

void
demo::Framework::Awake()
{
	serverLogger.Awake({ L"Log.txt" });
	std::set_terminate([]()
	{
		demo::Framework::serverLogger.Cleanup();
		std::abort();
	});

	serverLogger.Log(L"# (1) Server system is initiating...\n");

	serverLogger.Log(L"# Network system is initiating...\n");
	net::core::Initialize();
	serverLogger.Log(L"# Constructing users pool...\n");
	everyUsers.ConstructPool(startUserID);
	serverLogger.Log(L"# Constructing workers pool...\n");
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
	serverLogger.Log(L"# (2) Server is starting...\n");

	serverLogger.Log(L"# Starting open user instances...\n");
	for (auto& user_ptr : everyUsers)
	{
		iconer::User& user = *user_ptr;

		if (not user.SetState<iconer::user_status::Listening>(std::ref(listenSocket)))
		{
			serverLogger.LogError(L"Cannot initiate the user");
			//throw "Cannot initiate the user";
		}
	}
}

void
demo::Framework::Update()
{
	serverLogger.Log(L"# (3) Server is started\n");

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
	serverLogger.Log(L"# (4) Server system is ended\n");

	serverLogger.Log(L"# Network system is destructing...\n");
	net::core::Annihilate();

	serverLogger.Cleanup();
}
