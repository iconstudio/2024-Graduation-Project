module;
module Demo.Framework;
import Iconer.Application.User;
import Iconer.Application.BorrowedSendContext;

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
		const auto& io_bytes = io_event.ioBytes;
		const auto& io_id = io_event.eventId;

		if (is_done or framework.IsWorkerCancelled()) [[unlikely]] {
			break;
		};

		logger.DebugLog(L"\tWorker {}: Event by id {}.\n", nth, io_id);

		auto ctx = static_cast<iconer::app::IContext*>(io_context);
		if (framework.RouteOperation(io_event.isSucceed, io_id, io_bytes, ctx)) [[likely]] {
			ctx->Clear();
		}
		else [[unlikely]] {
			break;
		};
	}

	logger.DebugLog(L"\tWorker {} is finished\n", nth);
}
