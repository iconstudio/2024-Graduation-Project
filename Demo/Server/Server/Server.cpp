#pragma comment(lib, "Modern Network.lib")

import Iconer.Declarations;
import Iconer.Network.User;
import Iconer.Network.EntityManager;
import Iconer.Network.UserManager;
import Demo.Framework;
import <iostream>;

demo::Framework appFramework{ 50ULL, 40000U };

int
main()
{
	std::cout << "Hello World!\n";

	//iconer::NetworkEntityManager<iconer::user_id_t> entity_manager{ 20ULL };
	iconer::UserManager user_manager{ 20ULL };

	iconer::User u1{ 1 };
	u1.OnNetworkInitialized(true, {});
	iconer::User u2{ 2 };
	u2.OnNetworkInitialized(false, {});

	auto change_0 = u1.SetState<iconer::user_status::Connecting>();
	auto change_1 = u1.SetState<iconer::user_status::Idle>();
	auto change_2 = u1.SetState<iconer::user_status::None>();
	auto change_3 = u1.SetState<iconer::user_status::Closing>();
	auto change_4 = u1.SetState<iconer::user_status::Listening>();

	//entity_manager.Add(std::move(u1));
	//user_manager.Add(std::move(u2));

	//iconer::NetworkView* v = &u1;
	//v->OnNetworkInitialized(false, {});
}
