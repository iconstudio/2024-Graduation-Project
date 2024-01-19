module Demo.Framework;
import Net;
import Iconer.Utility.Logger;
import <cstdio>;
import <memory>;
import <string>;
import <string_view>;
import <format>;
import <algorithm>;
import <iostream>;
// ReSharper disable CppMemberFunctionMayBeStatic

iconer::util::Logger logger{};

demo::Framework::Framework(size_t clients_count, std::uint16_t port)
	: serverWorkers(), workerCanceller()
	, listenSocket(), listenContext()
	, everyUsers(clients_count)
	, cancellationSource()
{}

void
demo::Framework::Awake()
{
	logger.Awake({L"Log.txt"});

	logger.Log(L"# (1) Server system is initiating...\n");

	std::cout << "# Network system is initiating...\n";
	net::core::Initialize();
	std::cout << "# Constructing users pool...\n";
	everyUsers.ConstructPool(startUserID);
	std::cout << "# Constructing workers pool...\n";
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
	std::cout << "# (2) Server is starting...\n";

	std::cout << "# Constructing user instances...\n";
	for (auto& user_ptr : everyUsers)
	{
		iconer::User& user = *user_ptr;

		if (not user.SetState<iconer::user_status::Listening>(std::ref(listenSocket)))
		{
			throw "Cannot initiate the user";
		}
	}
}

void
demo::Framework::Update()
{
	std::cout << "# (3) Server is started\n";

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
	std::cout << "# (4) Server system is ended\n";

	std::cout << "# Network system is destructing...\n";
	net::core::Annihilate();
	logger.Cleanup();
}
