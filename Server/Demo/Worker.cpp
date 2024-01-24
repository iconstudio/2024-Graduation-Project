module;
#include <cstdio>
#include <cstdlib>

module Demo.Framework;

void Worker(Framework& framework, size_t nth)
{
	auto& logger = framework.myLogger;

	logger.Log(L"\tWorker {} is started.\n", nth);

	while (true)
	{
		auto io_event = framework.WaitForIoResult();
		auto& io_context = io_event.ioContext;
		auto& io_id = io_event.eventId;

		if (framework.IsWorkerCancelled())
		{
			break;
		}

		//if (not io_event.isSucceed)
		{

		}

		if (io_context)
		{
			io_context->Clear();
		}
	}
}

void Framework::Start()
{
	myLogger.Log(L"\topening the listener...\n");

	if (serverListener.Open().has_value())
	{
		myLogger.Log(L"\tThe listener is opened.\n");
	}

	myLogger.Log(L"\treserving acceptance of users...\n");

	for (auto& [id, user] : userManager)
	{
		auto acceptance = user.ReserveAccept(serverListener);
		if (acceptance)
		{
			throw std::exception{ "Error when reserving acceptance of a socket." };
		}
	}
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
