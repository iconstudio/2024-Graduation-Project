module Demo.Framework;
import Iconer.Net;

void
demo::Framework::Destroy()
{
	LockPhase();
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

	myLogger.Cleanup();

	UnlockPhase();
}

void
demo::Framework::CancelWorkers()
noexcept
{
	workerCanceller.request_stop();
}
