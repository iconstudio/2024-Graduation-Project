export module Iconer.Network.UserManager;
import Iconer.Declarations;
import Iconer.Network.EntityManager;
export import Iconer.Network.User;
import <stdexcept>;
import <memory>;

export namespace iconer
{
	struct [[nodiscard]] UserID final
	{
		constexpr UserID() noexcept = default;
		constexpr ~UserID() noexcept = default;

		explicit constexpr UserID(const user_id_t& id) noexcept
			: myId(id)
		{}
		explicit constexpr UserID(user_id_t&& id) noexcept
			: myId(std::move(id))
		{}

		user_id_t myId;
	};

	class [[nodiscard]] UserManager final : private NetworkEntityManager<User, user_id_t>
	{
	public:
		using id_t = user_id_t;
		using super = NetworkEntityManager;
		using super::data_t;
		using super::value_type;
		using super::allocator_type;
		using super::pointer;
		using super::const_pointer;
		using super::reference;
		using super::const_reference;
		using super::size_type;
		using super::difference_type;
		using super::iterator;
		using super::const_iterator;

		using super::FindEntity;
		using super::begin;
		using super::end;
		using super::cbegin;
		using super::cend;
		using super::GetCapacity;
		using super::GetSize;
		using super::IsEmpty;

		constexpr ~UserManager() noexcept = default;

		explicit constexpr UserManager(size_type clients_count) noexcept
			: super()
		{
			Reserve(clients_count);
		}

		void Add(std::unique_ptr<User>&& ptr)
		{
			super::Add(std::move(ptr));
		}

		void Add(User* object_ptr)
		{
			super::Add(object_ptr);
		}

	private:
		static inline std::bad_alloc badUserAllocation{};

		UserManager(const UserManager&) = delete;
		UserManager(UserManager&&) = delete;
		void operator=(const UserManager&) = delete;
		void operator=(UserManager&&) = delete;
	};
}
