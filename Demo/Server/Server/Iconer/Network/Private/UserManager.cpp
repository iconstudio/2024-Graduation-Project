module Iconer.Network.UserManager;

void
iconer::UserManager::ConstructPool(id_t begin_id)
{
	Create([&](){
		auto ptr = std::make_unique<User>(begin_id++);
		if (not ptr)
		{
			throw badUserAllocation;
		}

		ptr->SetState<user_status::None>();

		return ptr;
	});
}
