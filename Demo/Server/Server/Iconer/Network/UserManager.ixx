export module Iconer.Network.UserManager;
import Iconer.Declarations;
import Iconer.Network.EntityManager;
export import Iconer.Network.User;
import <memory>;

export namespace iconer
{
	class [[nodiscard]] UserManager final : private NetworkEntityManager<User, user_id_t>
	{
	public:
		using id_t = user_id_t;
		using super = NetworkEntityManager;
		using super::value_type;
		using super::data_t;

		using super::allocator_type;
		using super::pointer;
		using super::const_pointer;
		using super::reference;
		using super::const_reference;
		using super::size_type;
		using super::difference_type;
		using super::iterator;
		using super::const_iterator;

		using super::begin;
		using super::end;
		using super::cbegin;
		using super::cend;

		constexpr ~UserManager() noexcept = default;

		explicit constexpr UserManager(size_type clients_count) noexcept
			: UserManager()
		{
			Reserve(clients_count);
		}

	private:
		void Add(std::unique_ptr<iconer::User>&& ptr)
		{
			super::Add(std::move(ptr));
		}

		void Add(iconer::User* object_ptr)
		{
			super::Add(object_ptr);
		}

		UserManager(const UserManager&) = delete;
		UserManager(UserManager&&) = delete;
		void operator=(const UserManager&) = delete;
		void operator=(UserManager&&) = delete;
	};
}
