module;
module Demo.Framework;
import Iconer.Net;
import <string>;
import <string_view>;

void
demo::Framework::Destroy()
{
	LockPhase();
	if (not Schedule(new FrameworkTaskContext{ .myCategory = FrameworkTaskCategory::EndTask }, serverID, 0))
	{
		myLogger.LogError(L"An error is occured when closing tasks");
	}
	UnlockPhase();
}

void
demo::Framework::Cleanup()
{
	LockPhase();

#if _DEBUG
	const auto cleanup_err =
#endif // _DEBUG
		iconer::net::Cleanup();

#if _DEBUG
	if (cleanup_err)
	{
		myLogger.LogError(L"An error {} is occured when cleaning up", cleanup_err.value());
	}
#endif // _DEBUG
	
	myLogger.Cleanup();

	UnlockPhase();
}

void
demo::Framework::CancelWorkers()
noexcept
{
	workerCanceller.request_stop();
}
