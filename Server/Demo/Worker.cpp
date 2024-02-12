module;
module Demo.Framework;
import Iconer.Application.User;
import Iconer.Application.BorrowedSendContext;
import Iconer.Application.Resources.String;

void
demo::Worker(demo::Framework& framework, size_t nth)
{
	auto& logger = framework.myLogger;

	auto& beg_msg = iconer::app::StaticWideString<0>();
	logger.Log(beg_msg, nth);
	framework.workerAwakens.arrive_and_wait();

	while (true)
	{
		auto io_event = framework.WaitForIoResult();

		auto& io_context = io_event.ioContext;
		const auto& io_bytes = io_event.ioBytes;
		const auto& io_id = io_event.eventId;

		if (framework.IsWorkerCancelled()) [[unlikely]] {
			break;
		};

		auto& msg = iconer::app::StaticWideString<1>();
		logger.DebugLog(msg, nth, io_id);

		auto ctx = static_cast<iconer::app::IContext*>(io_context);
		if (framework.RouteOperation(io_event.isSucceed, io_id, io_bytes, ctx)) [[likely]] {
			ctx->Clear();
		}
		else [[unlikely]] {
			break;
		};
	}

	auto& end_msg = iconer::app::StaticWideString<2>();
	logger.DebugLog(end_msg, nth);
}
