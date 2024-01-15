export module Iconer.Network.EntityManager;
import Net.Constraints;
import Iconer.Network.Entity;
import <vector>;
import <algorithm>;
import <iterator>;
import <memory>;
import <shared_mutex>;

export namespace iconer
{
	template <typename IdType>
	struct NetworkEntityComparator
	{
		[[nodiscard]]
		constexpr bool operator()(const std::unique_ptr<NetworkEntity<IdType>>& lhs, const std::unique_ptr<NetworkEntity<IdType>>& rhs) const noexcept
		{
			return lhs->ID < rhs->ID;
		}
	};

	template <typename IdType, template<typename... Ts> typename Container = std::vector>
	class [[nodiscard]] NetworkEntityManager
	{
	public:
		using id_t = IdType;
		using object_t = NetworkEntity<IdType>;
		using data_t = Container<std::unique_ptr<object_t>>;
		using lock_t = std::shared_mutex;
		using allocator_type = data_t::allocator_type;
		using value_type = data_t::value_type;
		using pointer = data_t::pointer;
		using const_pointer = data_t::const_pointer;
		using reference = data_t::reference;
		using const_reference = data_t::const_reference;
		using vol_reference = volatile reference;
		using constvol_reference = volatile const_reference;
		using size_type = data_t::size_type;
		using difference_type = data_t::difference_type;
		using iterator = data_t::iterator;
		using const_iterator = data_t::const_iterator;

		constexpr NetworkEntityManager() noexcept(net::nothrow_default_constructibles<data_t, lock_t>) = default;
		constexpr ~NetworkEntityManager() noexcept(net::nothrow_destructibles<data_t, lock_t>) = default;

		void Add(object_t&& object)
		{
			std::unique_lock lk{myLock};
			auto it = std::back_inserter(myData);
			*it = std::make_unique<object_t>(std::move(object));
		}

		void Add(value_type&& ptr)
		{
			std::unique_lock lk{myLock};
			auto it = std::back_inserter(myData);
			*it = std::move(ptr);
		}

		void Add(object_t* object_ptr)
		{
			std::unique_lock lk{myLock};
			auto it = std::back_inserter(myData);
			*it = value_type{object_ptr};
		}

		template <typename U, typename... Args>
		void Emplace(Args&&... args)
		{
			std::unique_lock lk{myLock};
			auto it = std::back_inserter(myData);
			*it = std::make_unique<U>(std::forward<Args>(args)...);
		}

		template <typename It>
			requires requires(It it){ data_t::erase(it); }
		void Remove(It it) noexcept(noexcept(myData.erase(it)) and noexcept(myLock.lock()))
		{
			std::unique_lock lk{myLock};
			myData.erase(it);
		}

		[[nodiscard]]
		reference At(const size_type pos) noexcept
		{
			std::shared_lock lk{myLock};
			return myData.at(pos);
		}

		[[nodiscard]]
		const_reference At(const size_type pos) const noexcept
		{
			std::shared_lock lk{myLock};
			return myData.at(pos);
		}

		[[nodiscard]]
		constexpr reference operator[](const size_type pos) noexcept
		{
			std::shared_lock lk{myLock};
			return myData.operator[](pos);
		}

		[[nodiscard]]
		constexpr const_reference operator[](const size_type pos) const noexcept
		{
			std::shared_lock lk{myLock};
			return myData.operator[](pos);
		}

		[[nodiscard]]
		iterator FindEntity(const id_t id) noexcept
		{
			std::shared_lock lk{myLock};
			return std::find(begin(), end(), id, [&id](const_reference element) noexcept -> bool { return id == element->ID; });
		}

		[[nodiscard]]
		const_iterator FindEntity(const id_t id) const noexcept
		{
			std::shared_lock lk{myLock};
			return std::find(begin(), end(), id, [&id](const_reference element) noexcept -> bool { return id == element->ID; });
		}

		template <typename Pred>
		void Search(Pred&& fn) noexcept
		{
			std::shared_lock lk{myLock};
		}

		[[nodiscard]]
		constexpr iterator begin() noexcept
		{
			return myData.begin();
		}

		[[nodiscard]]
		constexpr iterator end() noexcept
		{
			return myData.end();
		}

		[[nodiscard]]
		constexpr const_iterator begin() const noexcept
		{
			return myData.begin();
		}

		[[nodiscard]]
		constexpr const_iterator end() const noexcept
		{
			return myData.end();
		}

		[[nodiscard]]
		constexpr const_iterator cbegin() const noexcept
		{
			return myData.cbegin();
		}

		[[nodiscard]]
		constexpr const_iterator cend() const noexcept
		{
			return myData.cend();
		}

		void LockWriter() noexcept
		{
			myLock.lock();
		}

		void UnlockWriter() noexcept
		{
			myLock.unlock();
		}

		void LockReader() noexcept
		{
			myLock.lock_shared();
		}

		void UnlockReader() noexcept
		{
			myLock.unlock_shared();
		}

		bool TryLockWriter() noexcept
		{
			return myLock.try_lock();
		}

		bool TryLockReader() noexcept
		{
			return myLock.try_lock_shared();
		}

		[[nodiscard]]
		constexpr size_type GetSize() const noexcept
		{
			return myData.size();
		}

		[[nodiscard]]
		constexpr size_type GetCapacity() const noexcept
		{
			return myData.capacity();
		}

		[[nodiscard]]
		constexpr bool IsEmpty() const noexcept
		{
			return myData.empty();
		}

	protected:
		template <typename M>
		friend class std::unique_lock;
		template <typename M>
		friend class std::shared_lock;
		template <typename M>
		friend class std::lock_guard;

		constexpr void _SortData() noexcept(noexcept(std::ranges::sort_heap(myData, NetworkEntityComparator<IdType>{})))
		{
			std::ranges::sort_heap(myData, NetworkEntityComparator<IdType>{});
		}

		void lock() noexcept
		{
			myLock.lock();
		}

		void unlock() noexcept
		{
			myLock.unlock();
		}

		void lock_shared() noexcept
		{
			myLock.lock_shared();
		}

		void unlock_shared() noexcept
		{
			myLock.unlock_shared();
		}

		bool try_lock() noexcept
		{
			return myLock.try_lock();
		}

		bool try_lock_shared() noexcept
		{
			return myLock.try_lock_shared();
		}

	private:
		NetworkEntityManager(const NetworkEntityManager&) = delete;
		NetworkEntityManager(NetworkEntityManager&&) = delete;
		void operator=(const NetworkEntityManager&) = delete;
		void operator=(NetworkEntityManager&&) = delete;

		data_t myData;
		lock_t myLock;
	};
}
