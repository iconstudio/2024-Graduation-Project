#pragma comment(lib, "Modern Network.lib")

import Iconer.Declarations;
import Iconer.Network.User;
import Iconer.Network.EntityManager;
import Iconer.Network.UserManager;
#include <iostream>

int main()
{
	std::cout << "Hello World!\n";

	//iconer::NetworkEntityManager<iconer::user_id_t> entity_manager{ 20ULL };
	iconer::UserManager user_manager{ 20ULL };

	iconer::User u1;
	u1.OnNetworkIntialized(true, {});
	iconer::User u2;
	u2.OnNetworkIntialized(false, {});

	//entity_manager.Add(std::move(u1));
	user_manager.Add(std::move(u2));

	//iconer::NetworkView* v = &u1;
	//v->OnNetworkIntialized(false, {});
}
