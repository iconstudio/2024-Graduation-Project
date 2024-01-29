module;
#include <string>
#include <string_view>

module Demo.Framework;
import Iconer.Application.User;

void
demo::Worker(demo::Framework& framework, size_t nth)
{
	auto& logger = framework.myLogger;

	logger.Log(L"\tWorker {} is started.\n", nth);
	framework.workerAwakens.arrive_and_wait();

	volatile bool is_done = false;
	while (true)
	{
		auto io_event = framework.WaitForIoResult();

		const bool& succeed = io_event.isSucceed;
		auto& io_context = io_event.ioContext;
		auto& io_bytes = io_event.ioBytes;
		auto& io_id = io_event.eventId;

		if (is_done or framework.IsWorkerCancelled()) [[unlikely]] {
			break;
		};

		if (0 == io_id) [[unlikely]] // by server framework
		{
			auto task = static_cast<demo::FrameworkTaskContext*>(io_context);
			if (nullptr == task)
			{
				throw "Null framework context";
			}

			switch (task->myCategory)
			{
				case demo::FrameworkTaskCategory::EndTask:
				{
					is_done = true;
					delete task;
				}
				break;

				default:
				{
					delete task;
				}
				break;
			}
		}
		else [[likely]] // by sessions
		{
			auto user = static_cast<iconer::app::User*>(io_context);
			if (nullptr == user)
			{
				throw "Null user context";
			}

			// not const
			iconer::app::UserStates status = user->AcquireState();
			const auto user_id = static_cast<demo::Framework::IdType>(io_id);
			const iconer::app::UserOperations operation = user->GetOperation();

			switch (operation)
			{
				case iconer::app::UserOperations::Recv:
				{
					if (not succeed)
					{
						logger.LogError(L"\tReceving has failed on user {}\n", user_id);
					}
					else if (auto error = framework.OnReceived(*user, user_id, status, io_bytes))
					{
						logger.LogError(L"\ttReceving has failed on user {} due to {}\n", user_id, error.value());
					}
					else
					{
						logger.Log(L"\tAcceptance is reserved on user {}\n", user_id);
					}
				}
				break;

				case iconer::app::UserOperations::Accept:
				{
					if (not succeed)
					{
						logger.LogError(L"\tReserving an acceptance has failed on user {}\n", user_id);
					}
					else if (auto error = framework.OnReserveAccept(*user, status))
					{
						logger.LogError(L"\tReserving an acceptance has failed on user {} due to {}\n", user_id, error.value());
					}
					else
					{
						logger.Log(L"\tAcceptance is reserved on user {}\n", user_id);
					}
				}
				break;

				case iconer::app::UserOperations::Connect:
				{
					if (not succeed)
					{
						logger.LogError(L"\tConnection has failed on user {}\n", user_id);
					}
					else if (auto error = framework.OnUserConnected(*user, user_id, status))
					{
						logger.LogError(L"\tConnection has failed on user {} due to {}\n", user_id, error.value());
					}
					else
					{
						logger.Log(L"\tUser {} is connected\n", user_id);
					}
				}
				break;

				case iconer::app::UserOperations::Disconnect:
				{
					if (not succeed)
					{
						logger.LogError(L"\tUser {} has failed to disconnect\n", user_id);
					}
					else if (auto error = framework.OnUserDisconnected(*user, user_id, status))
					{
						logger.LogError(L"\tUser {} would not be disconnected due to {}\n", user_id, error.value());
					}
					else
					{
						logger.Log(L"\tUser {} has been disconnected\n", user_id);
					}
				}
				break;

				case iconer::app::UserOperations::CreateRoom:
				{
					if (not succeed)
					{
						logger.LogError(L"\tUser {} could not create a room\n", user_id);
					}
					else
					{
						logger.Log(L"\tUser {} created a room {}\n", user_id, 0);
					}
				}
				break;

				case iconer::app::UserOperations::EnterRoom:
				{
					if (not succeed)
					{
						logger.LogError(L"\tUser {} could not enter to room {}\n", user_id, 0);
					}
					else
					{
						logger.Log(L"\tUser {} entered to room {}\n", user_id, 0);
					}
				}
				break;

				case iconer::app::UserOperations::LeaveRoom:
				{

				}
				break;

				case iconer::app::UserOperations::ReadyGame:
				{

				}
				break;

				case iconer::app::UserOperations::EnterGame:
				{

				}
				break;

				case iconer::app::UserOperations::StartGame:
				{

				}
				break;

				case iconer::app::UserOperations::LeaveGame:
				{

				}
				break;

				default:
				{
					if (not succeed)
					{
						logger.LogError(L"\tUnknown operation '{}' has failed on user {}\n", static_cast<int>(operation), user_id);
					}
					else
					{
						logger.Log(L"\tAn unknown operation '{}' has been executed on user {}\n", static_cast<int>(operation), user_id);
					}
				}
				break;
			}

			user->ReleaseState(status);
		};

		if (io_context)
		{
			io_context->Clear();
		}
	}

	logger.Log(L"\tWorker {} is finished\n", nth);
}
