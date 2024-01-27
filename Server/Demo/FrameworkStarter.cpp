module Demo.Framework;

void
demo::Framework::Start()
{
	LockPhase();

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

	UnlockPhase();
}
