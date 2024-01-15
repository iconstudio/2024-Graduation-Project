module;
#include <mutex>
#include <shared_mutex>

export module Iconer.Network.EntityManager;
import Iconer.Utility.ObjectManager;
import Iconer.Network.Entity;
import <algorithm>;

export namespace iconer
{
	template<typename IdType>
	struct NetworkEntityComparator
	{
		using mgr_t = ObjectManager<iconer::NetworkEntity<IdType>>;
		using const_reference = mgr_t::const_reference;

		[[nodiscard]]
		constexpr bool operator()(const_reference lhs, const_reference rhs) const noexcept
		{
			return lhs->ID < rhs->ID;
		}
	};

	template<typename IdType>
	class [[nodiscard]] NetworkEntityManager : public ObjectManager<iconer::NetworkEntity<IdType>, NetworkEntityComparator<IdType>>
	{
	public:
		using id_t = IdType;
		using super = ObjectManager<iconer::NetworkEntity<IdType>, NetworkEntityComparator<IdType>>;
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

		using super::super;
		using super::begin;
		using super::end;
		using super::cbegin;
		using super::cend;

		~NetworkEntityManager() = default;

		void Add(object_t&& object)
		{
			std::unique_lock lk{ myLock };
			super::Add(std::move(object));
		}

		void Add(value_type&& ptr)
		{
			std::unique_lock lk{ myLock };
			super::Add(std::move(ptr));
		}

		void Add(object_t* object_ptr)
		{
			std::unique_lock lk{ myLock };
			super::Add(std::move(object_ptr));
		}

		using super::Emplace;
		template<typename U, typename... Args>
		void Emplace(Args&&... args)
		{
			std::unique_lock lk{ myLock };
			Emplace<U>(std::forward<Args>(args)...);
		}

		void Remove(iterator it)
		{
			std::unique_lock lk{ myLock };
			super::Remove(it);
		}

		void Remove(const_iterator it)
		{
			std::unique_lock lk{ myLock };
			super::Remove(it);
		}

		[[nodiscard]]
		reference At(const size_type pos) noexcept
		{
			std::shared_lock lk{ myLock };
			return super::At(pos);
		}

		[[nodiscard]]
		const_reference At(const size_type pos) const noexcept
		{
			std::shared_lock lk{ myLock };
			return super::At(pos);
		}

		[[nodiscard]]
		iterator FindEntity(const id_t id) noexcept
		{
			std::shared_lock lk{ myLock };
			return std::find(begin(), end(), id, [&id](const_reference element) noexcept -> bool { return id == element->ID; });
		}

		[[nodiscard]]
		const_iterator FindEntity(const id_t id) const noexcept
		{
			std::shared_lock lk{ myLock };
			return std::find(begin(), end(), id, [&id](const_reference element) noexcept -> bool { return id == element->ID; });
		}

		template<typename Pred>
		[[nodiscard]]
		void Search(Pred&& fn) noexcept
		{
			std::shared_lock lk{ myLock };

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

		void TryLockReader() noexcept
		{
			return myLock.try_lock_shared();
		}

	protected:
		template<typename M>
		friend class std::unique_lock;
		template<typename M>
		friend class std::shared_lock;
		template<typename M>
		friend class std::lock_guard;

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

		void try_lock_shared() noexcept
		{
			return myLock.try_lock_shared();
		}

	private:
		NetworkEntityManager(const NetworkEntityManager&) = delete;
		NetworkEntityManager(NetworkEntityManager&&) = delete;
		void operator=(const NetworkEntityManager&) = delete;
		void operator=(NetworkEntityManager&&) = delete;

		std::shared_mutex myLock;
	};
}
