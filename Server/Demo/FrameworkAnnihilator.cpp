module;
module Demo.Framework;
import Iconer.Net;

void
demo::Framework::Destroy()
{
	LockPhase();
	Schedule(new FrameworkTaskContext{ .myCategory = FrameworkTaskCategory::EndTask }, serverID, 0);
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
