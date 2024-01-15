export module Iconer.Network.UserManager;
import Iconer.Declarations;
import Iconer.Network.EntityManager;
export import Iconer.Network.User;
import <memory>;

export namespace iconer
{
	class [[nodiscard]] UserManager final : public NetworkEntityManager<user_id_t>
	{
	public:
		using id_t = user_id_t;
		using super = NetworkEntityManager<user_id_t>;
		using object_t = super::object_t;
		using value_type = super::value_type;
		using data_t = super::data_t;

		using allocator_type = super::allocator_type;
		using pointer = super::pointer;
		using const_pointer = super::const_pointer;
		using reference = super::reference;
		using const_reference = super::const_reference;
		using vol_reference = super::vol_reference;
		using constvol_reference = super::constvol_reference;
		using size_type = super::size_type;
		using difference_type = super::difference_type;
		using iterator = super::iterator;
		using const_iterator = super::const_iterator;

		using super::begin;
		using super::end;
		using super::cbegin;
		using super::cend;

		constexpr UserManager() noexcept = default;
		constexpr ~UserManager() noexcept = default;

		constexpr UserManager(size_type clients_count) noexcept : super(clients_count) {}

		void Add(iconer::User&& object)
		{
			super::Add(std::move(object));
		}

		void Add(std::unique_ptr<iconer::User>&& ptr)
		{
			super::Add(std::move(ptr));
		}

		void Add(iconer::User* object_ptr)
		{
			super::Add(object_ptr);
		}

	private:
		UserManager(const UserManager&) = delete;
		UserManager(UserManager&&) = delete;
		void operator=(const UserManager&) = delete;
		void operator=(UserManager&&) = delete;
	};
}
