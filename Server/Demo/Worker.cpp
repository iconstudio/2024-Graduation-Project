module Demo.Framework;
import Iconer.Application.User;

void
demo::Worker(demo::Framework& framework, size_t nth)
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

		if (0 == io_id) // by server framework
		{

		}
		else // by sessions
		{
			auto user = std::launder(reinterpret_cast<iconer::app::User*>(io_context));
			if (nullptr == user)
			{
				throw "Null user context";
			}

			// not const
			iconer::app::UserStates user_status = user->GetState();
			switch (user_status)
			{
				case iconer::app::UserStates::None:
				{

				}
				break;

				case iconer::app::UserStates::Listening:
				{

				}
				break;

				case iconer::app::UserStates::Connecting:
				{

				}
				break;

				case iconer::app::UserStates::Idle:
				{

				}
				break;

				case iconer::app::UserStates::Closing:
				{

				}
				break;

				case iconer::app::UserStates::Dead:
				{

				}
				break;

				default:
				{

				}
				break;
			}
		}

		if (io_context)
		{
			io_context->Clear();
		}
	}
}
