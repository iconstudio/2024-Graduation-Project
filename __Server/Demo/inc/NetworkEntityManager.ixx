module;
#include <shared_mutex>

export module Iconer.Network.EntityManager;
import Net.BorrowedPointer;
import Iconer.Constraints;
import Iconer.Network.Entity;
import <concepts>;
import <memory>;
import <vector>;
import <algorithm>;
import <iterator>;

export namespace iconer
{
	template<typename E, typename IdType, typename SharedLocker = std::shared_mutex>
	class [[nodiscard]] NetworkEntityManager
	{
		static_assert(std::derived_from<E, NetworkEntity<IdType>>);

	public:
		using id_t = IdType;
		using object_t = E;
		using data_t = std::vector<std::unique_ptr<E>>;
		using lock_t = SharedLocker;
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

		constexpr NetworkEntityManager(const size_type capacity)
			noexcept(std::is_nothrow_constructible_v<data_t, size_type> and std::is_nothrow_default_constructible_v<lock_t>)
			: objectPool(), myLock()
		{
			objectPool.reserve(capacity);
		}

		constexpr ~NetworkEntityManager() noexcept(std::is_nothrow_destructible_v<data_t> and std::is_nothrow_destructible_v<lock_t>) = default;

		template<net::invocable_results<object_t> Predicate>
			requires std::movable<object_t>
		void Create(Predicate&& generator)
			noexcept(noexcept(Sort()) and noexcept(std::declval<data_t>().push_back(std::make_unique<object_t>(Predicate()))) and noexcept(std::declval<lock_t>().lock()))
		{
			std::unique_lock lk{ myLock };

			const size_t cap = objectPool.capacity();
			auto&& gen = std::forward<Predicate>(generator);

			for (size_t i = 0; i < cap; ++i)
			{
				objectPool.push_back(std::make_unique<object_t>(gen()));
			}
			Sort();
		}
		template<net::invocable_results<object_t*> Predicate>
		void Create(Predicate&& generator)
			noexcept(noexcept(Sort()) and noexcept(std::declval<data_t>().push_back(Predicate())) and noexcept(std::declval<lock_t>().lock()))
		{
			std::unique_lock lk{ myLock };

			const size_t cap = objectPool.capacity();
			auto&& gen = std::forward<Predicate>(generator);

			for (size_t i = 0; i < cap; ++i)
			{
				objectPool.push_back(value_type{ gen() });
			}
			Sort();
		}
		template<net::invocable_results<value_type> Predicate>
		void Create(Predicate&& generator)
			noexcept(noexcept(Sort()) and noexcept(std::declval<data_t>().push_back(std::declval<Predicate>()())) and noexcept(std::declval<lock_t>().lock()))
		{
			std::unique_lock lk{ myLock };

			const size_t cap = objectPool.capacity();
			auto&& gen = std::forward<Predicate>(generator);

			for (size_t i = 0; i < cap; ++i)
			{
				objectPool.push_back(gen());
			}
			Sort();
		}
		void CreateAsDefault()
			noexcept(noexcept(Sort()) and noexcept(std::declval<data_t>().push_back(std::make_unique<object_t>())) and noexcept(std::declval<lock_t>().lock()))
			requires std::default_initializable<value_type>
		{
			std::unique_lock lk{ myLock };

			const size_t cap = objectPool.capacity();
			for (size_t i = 0; i < cap; ++i)
			{
				objectPool.push_back(object_t{});
			}
			Sort();
		}
		void Add(const object_t& object)
			noexcept(noexcept(Sort()) and noexcept(std::declval<data_t>().push_back(std::make_unique<object_t>(std::declval<const object_t&>()))) and noexcept(std::declval<lock_t>().
			lock()))
			requires std::copyable<object_t>
		{
			std::unique_lock lk{ myLock };
			objectPool.push_back(std::make_unique<object_t>(object));
			Sort();
		}
		void Add(object_t&& object)
			noexcept(noexcept(Sort()) and noexcept(std::declval<data_t>().push_back(std::make_unique<object_t>(std::declval<object_t&&>()))) and noexcept(std::declval<lock_t>().lock()))
			requires std::movable<object_t>
		{
			std::unique_lock lk{ myLock };
			objectPool.push_back(std::make_unique<object_t>(std::move(object)));
			Sort();
		}
		void Add(object_t* ptr)
			noexcept(noexcept(Sort()) and noexcept(std::declval<data_t>().push_back(value_type{ std::declval<object_t*>() })) and noexcept(std::declval<lock_t>().lock()))
		{
			std::unique_lock lk{ myLock };
			objectPool.push_back(value_type{ ptr });
			Sort();
		}
		void Add(value_type&& handle)
			noexcept(noexcept(Sort()) and noexcept(std::declval<data_t>().push_back(std::declval<value_type&&>())) and noexcept(std::declval<lock_t>().lock()))
		{
			std::unique_lock lk{ myLock };
			objectPool.push_back(std::move(handle));
			Sort();
		}
		template<typename... Args>
		void Emplace(Args&&... args)
		{
			std::unique_lock lk{ myLock };
			objectPool.emplace_back(std::forward<Args>(args)...);
			Sort();
		}
		template<typename It>
			requires requires(It it) { data_t::erase(it); }
		void Remove(It it) noexcept(noexcept(objectPool.erase(it)) and noexcept(std::declval<lock_t>().lock()))
		{
			std::unique_lock lk{ myLock };
			objectPool.erase(it);
			Sort();
		}

		[[nodiscard]]
		reference At(const size_type pos) noexcept(noexcept(std::declval<data_t>().at(pos)))
		{
			std::shared_lock lk{ myLock };
			return objectPool.at(pos);
		}
		[[nodiscard]]
		const_reference At(const size_type pos) const noexcept(noexcept(std::declval<const data_t>().at(pos)))
		{
			std::shared_lock lk{ myLock };
			return objectPool.at(pos);
		}
		[[nodiscard]]
		reference operator[](const size_type pos) noexcept(noexcept(std::declval<data_t>().operator[](pos)))
		{
			std::shared_lock lk{ myLock };
			return objectPool.operator[](pos);
		}
		[[nodiscard]]
		const_reference operator[](const size_type pos) const noexcept(noexcept(std::declval<const data_t>().operator[](pos)))
		{
			std::shared_lock lk{ myLock };
			return objectPool.operator[](pos);
		}

		[[nodiscard]]
		auto FindEntity(const id_t id) noexcept
		{
			std::shared_lock lk{ myLock };
			return std::ranges::lower_bound(objectPool.begin(), objectPool.end()
				, id
				, std::less<id_t>{}, [](const_reference handle) { return handle.get()->ID; });
		}
		[[nodiscard]]
		auto FindEntity(const id_t id) const noexcept
		{
			std::shared_lock lk{ myLock };
			return std::ranges::lower_bound(objectPool.begin(), objectPool.end()
				, id
				, std::less<id_t>{}, [](const_reference handle) { return handle.get()->ID; });
		}

		template<typename Predicate, typename Projection = std::identity>
			requires std::is_invocable_v<const_reference>
		void ForEach(Predicate&& fn)
			const noexcept(std::is_nothrow_invocable_v<Predicate, std::invoke_result_t<Projection, const_reference>>)
		{
			std::shared_lock lk{ myLock };

			std::ranges::for_each(objectPool, std::forward<Predicate>(fn), Projection{});
		}
		template<typename Predicate>
			requires std::is_invocable_v<reference>
		void Generate(Predicate&& fn) noexcept(std::is_nothrow_invocable_v<Predicate, reference>)
		{
			std::shared_lock lk{ myLock };

			std::ranges::generate(objectPool, std::forward<Predicate>(fn));
		}
		template<typename Predicate>
			requires std::is_invocable_v<const_reference>
		void Generate(Predicate&& fn) const noexcept(std::is_nothrow_invocable_v<Predicate, const_reference>)
		{
			std::shared_lock lk{ myLock };

			std::ranges::generate(objectPool, std::forward<Predicate>(fn));
		}
		template<typename Predicate>
			requires std::is_invocable_r_v<bool, reference> and std::copyable<value_type>
		[[nodiscard]]
		std::vector<value_type> Search(Predicate&& fn) noexcept(std::is_nothrow_invocable_v<Predicate, reference>)
		{
			std::shared_lock lk{ myLock };

			std::vector<value_type> result{};
			result.reserve(2 * GetSize() / 3);
			std::ranges::copy_if(objectPool, std::back_inserter(result), std::forward<Predicate>(fn));

			//return std::ranges::find_if(objectPool, std::forward<Predicate>(fn));
			return result;
		}
		template<typename Predicate>
			requires std::is_invocable_r_v<bool, const_reference> and std::copyable<const value_type>
		[[nodiscard]]
		std::vector<value_type> Search(Predicate&& fn) const noexcept(std::is_nothrow_invocable_v<Predicate, const_reference>)
		{
			std::shared_lock lk{ myLock };

			std::vector<value_type> result{};
			result.reserve(2 * GetSize() / 3);
			std::ranges::copy_if(objectPool, std::back_inserter(result), std::forward<Predicate>(fn));
			return result;
		}

		[[nodiscard]]
		constexpr iterator begin() noexcept
		{
			return objectPool.begin();
		}

		[[nodiscard]]
		constexpr iterator end() noexcept
		{
			return objectPool.end();
		}

		[[nodiscard]]
		constexpr const_iterator begin() const noexcept
		{
			return objectPool.begin();
		}

		[[nodiscard]]
		constexpr const_iterator end() const noexcept
		{
			return objectPool.end();
		}

		[[nodiscard]]
		constexpr const_iterator cbegin() const noexcept
		{
			return objectPool.cbegin();
		}

		[[nodiscard]]
		constexpr const_iterator cend() const noexcept
		{
			return objectPool.cend();
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
		constexpr const data_t& GetData() const noexcept
		{
			return objectPool;
		}
		[[nodiscard]]
		constexpr size_type GetSize() const noexcept(noexcept(std::declval<const data_t>().size()))
		{
			return objectPool.size();
		}
		[[nodiscard]]
		constexpr size_type GetCapacity() const noexcept(noexcept(std::declval<const data_t>().capacity()))
		{
			return objectPool.capacity();
		}

		[[nodiscard]]
		constexpr bool IsEmpty() const noexcept(noexcept(std::declval<const data_t>().empty()))
		{
			return objectPool.empty();
		}

	protected:
		template<typename M>
		friend class std::unique_lock;
		template<typename M>
		friend class std::shared_lock;
		template<typename M>
		friend class std::lock_guard;

		struct Comparator
		{
			[[nodiscard]]
			constexpr bool operator()(const object_t& lhs, const object_t& rhs) const noexcept
			{
				return lhs.ID < rhs.ID;
			}
		};

		struct HandleProjector
		{
			[[nodiscard]]
			constexpr auto&& operator()(const value_type& handle) const noexcept
			{
				return *handle;
			}
		};

		constexpr void Reserve(size_type count) noexcept(noexcept(std::declval<data_t>().reserve(size_type{})))
			requires requires(const size_type cnt) { std::declval<data_t>().reserve(cnt); }
		{
			objectPool.reserve(count);
		}

		constexpr void Sort() noexcept(noexcept(std::ranges::sort(objectPool, std::declval<Comparator>(), std::declval<HandleProjector>())))
			requires std::ranges::random_access_range<data_t>
		{
			std::ranges::sort(objectPool, Comparator{}, HandleProjector{});
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

		data_t objectPool;
		lock_t myLock;
	};
}
