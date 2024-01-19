module Demo.Framework;
import <memory>;
import <string>;
import <string_view>;
import <format>;
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
	everyUsers.ConstructPool(startUserID);
	serverWorkers.reserve(workersCount);
}

bool
demo::Framework::Start() noexcept
{
	bool result = true;
	try
	{
		for (auto& user_ptr : everyUsers)
		{
			iconer::User& user = *user_ptr;

			if (not user.SetState<iconer::user_status::Listening>(std::ref(listenSocket)))
			{
				result = false;
			}
		}
	}
	catch (...)
	{
		return false;
	}

	try
	{
		for (size_t i = 0; i < workersCount; ++i)
		{
			auto worker = new std::jthread{ Worker, std::ref(*this), workerCanceller.get_token() };

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
