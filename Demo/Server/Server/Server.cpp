﻿#pragma comment(lib, "Modern Network.lib")

import Iconer.Declarations;
import Iconer.Network.User;
import Iconer.Network.EntityManager;
import Iconer.Network.UserManager;
import Demo.Framework;
import Iconer.Container.FlatMap;

demo::Framework appFramework{ 50ULL, 40000U };

int
main()
{
	appFramework.Awake();
	appFramework.Start();
	appFramework.Update();
	appFramework.Cleanup();
}
