module;
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

		auto& io_context = io_event.ioContext;
		auto& io_bytes = io_event.ioBytes;
		auto& io_id = io_event.eventId;
		logger.DebugLog(L"\tWorker {}: Event by session {} ({} bytes).\n", nth, io_id, io_bytes);

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
				logger.LogError(L"\tWorker {}: Event by user has null context.\n", nth);
				throw "Null user context";
			}

			// not const
			iconer::app::UserStates status = user->AcquireState();

			framework.RouteOperation(io_event.isSucceed, io_bytes, user->GetOperation(), *user, static_cast<demo::Framework::IdType>(io_id), status);

			user->ReleaseState(status);
		};

		if (io_context)
		{
			io_context->Clear();
		}
	}

	logger.DebugLog(L"\tWorker {} is finished\n", nth);
}
