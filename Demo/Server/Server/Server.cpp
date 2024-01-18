#pragma comment(lib, "Modern Network.lib")

import Iconer.Declarations;
import Iconer.Network.User;
import Iconer.Network.EntityManager;
import Iconer.Network.UserManager;
import Demo.Framework;
import Iconer.Container.FlatMap;
import <iostream>;

demo::Framework appFramework{ 50ULL, 40000U };

int
main()
{
	std::cout << "Hello World!\n";

	iconer::FlatMap<std::string, int> my_dict{};
	my_dict.Capacity(40);

	appFramework.Awake();
	appFramework.Start();
	appFramework.Update();
	appFramework.Cleanup();
}
