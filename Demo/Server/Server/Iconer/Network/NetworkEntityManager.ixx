export module Iconer.Network.EntityManager;
import Iconer.Network.Entity;
import <vector>;
import <algorithm>;
import <iterator>;
import <memory>;
import <shared_mutex>;

export namespace iconer
{
	template<typename E, typename IdType, template<typename... Ts> typename Container = std::vector, typename Locker = std::shared_mutex, typename... Cts>
	class [[nodiscard]] NetworkEntityManager
	{
		static_assert(std::derived_from<E, NetworkEntity<IdType>>);

	public:
		using id_t = IdType;
		using object_t = E;
		using data_t = Container<std::unique_ptr<E>, Cts...>;
		using lock_t = Locker;
		using allocator_type = typename data_t::allocator_type;
		using value_type = typename data_t::value_type;
		using pointer = typename data_t::pointer;
		using const_pointer = typename data_t::const_pointer;
		using reference = typename data_t::reference;
		using const_reference = typename data_t::const_reference;
		using size_type = typename data_t::size_type;
		using difference_type = typename data_t::difference_type;
		using iterator = typename data_t::iterator;
		using const_iterator = typename data_t::const_iterator;

		constexpr NetworkEntityManager()
			noexcept(std::is_nothrow_default_constructible_v<data_t> and std::is_nothrow_default_constructible_v<lock_t>) = default;
		constexpr ~NetworkEntityManager()
			noexcept(std::is_nothrow_destructible_v<data_t> and std::is_nothrow_destructible_v<lock_t>) = default;

		void Add(object_t&& object)
		{
			std::unique_lock lk{ myLock };
			auto it = std::back_inserter(myData);
			*it = std::make_unique<object_t>(std::move(object));
			Sort();
		}

		void Add(value_type&& ptr)
		{
			std::unique_lock lk{ myLock };
			auto it = std::back_inserter(myData);
			*it = std::move(ptr);
			Sort();
		}

		void Add(object_t* const object_ptr) noexcept(noexcept(std::declval<lock_t>().lock()) and noexcept(value_type{ object_ptr }))
		{
			std::unique_lock lk{ myLock };
			auto it = std::back_inserter(myData);
			*it = value_type{ object_ptr };
			Sort();
		}

		template<typename U, typename... Args>
		void Emplace(Args&&... args)
		{
			std::unique_lock lk{ myLock };
			auto it = std::back_inserter(myData);
			*it = std::make_unique<U>(std::forward<Args>(args)...);
			Sort();
		}

		template<typename It>
			requires requires(It it) { data_t::erase(it); }
		void Remove(It it) noexcept(noexcept(myData.erase(it)) and noexcept(myLock.lock()))
		{
			std::unique_lock lk{ myLock };
			myData.erase(it);
			Sort();
		}

		[[nodiscard]]
		reference At(const size_type pos) noexcept(noexcept(std::declval<data_t>().at(pos)))
		{
			std::shared_lock lk{ myLock };
			return myData.at(pos);
		}

		[[nodiscard]]
		const_reference At(const size_type pos) const noexcept(noexcept(std::declval<const data_t>().at(pos)))
		{
			std::shared_lock lk{ myLock };
			return myData.at(pos);
		}

		[[nodiscard]]
		constexpr reference operator[](const size_type pos) noexcept(noexcept(std::declval<data_t>().operator[](pos)))
		{
			std::shared_lock lk{ myLock };
			return myData.operator[](pos);
		}

		[[nodiscard]]
		constexpr const_reference operator[](const size_type pos) const noexcept(noexcept(std::declval<const data_t>().operator[](pos)))
		{
			std::shared_lock lk{ myLock };
			return myData.operator[](pos);
		}

		[[nodiscard]]
		auto FindEntity(const id_t id) noexcept
		{
			std::shared_lock lk{ myLock };
			return std::ranges::find_if(myData, id, [](const_reference element) noexcept -> id_t { return element->ID; });
		}

		[[nodiscard]]
		auto FindEntity(const id_t id) const noexcept
		{
			std::shared_lock lk{ myLock };
			return std::ranges::find_if(myData, id, [](const_reference element) noexcept -> id_t { return element->ID; });
		}

		template<typename Predicate>
			requires std::is_invocable_r_v<bool, reference>
		[[nodiscard]]
		auto FindEntity(Predicate&& fn) noexcept(std::is_nothrow_invocable_v<Predicate, reference>)
		{
			std::shared_lock lk{ myLock };
			return std::ranges::find_if(myData, std::forward<Predicate>(fn));
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

		void LockWriter() noexcept(noexcept(std::declval<lock_t>().lock()))
		{
			myLock.lock();
		}

		void UnlockWriter() noexcept(noexcept(std::declval<lock_t>().unlock()))
		{
			myLock.unlock();
		}

		void LockReader() noexcept(noexcept(std::declval<lock_t>().lock_shared()))
		{
			myLock.lock_shared();
		}

		void UnlockReader() noexcept(noexcept(std::declval<lock_t>().unlock_shared()))
		{
			myLock.unlock_shared();
		}

		bool TryLockWriter() noexcept(noexcept(std::declval<lock_t>().try_lock()))
		{
			return myLock.try_lock();
		}

		bool TryLockReader() noexcept(noexcept(std::declval<lock_t>().try_lock_shared()))
		{
			return myLock.try_lock_shared();
		}

		[[nodiscard]]
		constexpr size_type GetSize() const noexcept(noexcept(std::declval<const data_t>().size()))
		{
			return myData.size();
		}

		[[nodiscard]]
		constexpr size_type GetCapacity() const noexcept(noexcept(std::declval<const data_t>().capacity()))
		{
			return myData.capacity();
		}

		[[nodiscard]]
		constexpr bool IsEmpty() const noexcept(noexcept(std::declval<const data_t>().empty()))
		{
			return myData.empty();
		}

	protected:
		template<typename M>
		friend class std::unique_lock;
		template<typename M>
		friend class std::shared_lock;
		template<typename M>
		friend class std::lock_guard;

		constexpr void Reserve(size_type count) noexcept(noexcept(std::declval<data_t>().reserve(size_type{})))
			requires requires(const size_type cnt) { std::declval<data_t>().reserve(cnt); }
		{
			myData.reserve(count);
		}

		struct Comparator
		{
			[[nodiscard]]
			constexpr bool operator()(const value_type& lhs, const value_type& rhs) const noexcept
			{
				return lhs->ID < rhs->ID;
			}
		};

		constexpr void Sort() noexcept(noexcept(std::ranges::sort_heap(myData, std::declval<Comparator>())))
			requires std::ranges::random_access_range<data_t>
		{
			std::ranges::sort_heap(myData, Comparator{});
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
