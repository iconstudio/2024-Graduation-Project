module;
#include <utility>
#include <atomic>
#include <array>

export module Iconer.Application.Room;
import Iconer.Utility.Constraints;
import Iconer.Utility.Concurrency.SharedMutex;
import Iconer.Application.ISession;
import Iconer.Application.User;

export namespace iconer::app
{
	enum class [[nodiscard]] RoomStates
	{
		None
		, Reserved, Creating // first phases: menu scene
		, Closing // menu scene
		, Idle // lobby scene
		, Ready // loading scene
		, InGame // game scene
		, GameDone // game scene
		, Cleanup // game scene, score scene
	};

	class [[nodiscard]] Room : public ISession<RoomStates>
	{
	public:
		static inline constexpr size_t maxUsersNumberInRoom = 6;
		static inline constexpr size_t minUsersNumberForGame = 4;

		using Super = ISession<RoomStates>;
		using Super::IdType;

		explicit constexpr Room(const IdType& id)
			noexcept(nothrow_constructible<Super, const IdType&>)
			: Super(id)
			, myLock()
			, myMembers(), membersCount(0)
		{
		}

		explicit constexpr Room(IdType&& id)
			noexcept(nothrow_constructible<Super, IdType&&>)
			: Super(std::move(id))
			, myLock()
			, myMembers(), membersCount(0)
		{
		}

		void Awake() noexcept
		{
		}

		[[nodiscard]]
		bool TryReserveContract() volatile noexcept
		{
			return TryChangeState(RoomStates::None, RoomStates::Reserved);
		}

		[[nodiscard]]
		bool TryCancelContract() volatile noexcept
		{
			return TryChangeState(RoomStates::Reserved, RoomStates::None);
		}

		[[nodiscard]]
		bool TryCreate() volatile noexcept
		{
			return TryChangeState(RoomStates::Reserved, RoomStates::Creating);
		}

		[[nodiscard]]
		bool TryCancelCreating() volatile noexcept
		{
			return TryChangeState(RoomStates::Creating, RoomStates::None);
		}

		bool TryAddMember(iconer::app::User& user) noexcept
		{
			std::unique_lock lock{ myLock };

			if (membersCount < maxUsersNumberInRoom)
			{
				return nullptr != (myMembers[membersCount.fetch_add(1, std::memory_order_acq_rel)] = std::addressof(user));
			}
			else
			{
				return false;
			}
		}

		size_t RemoveMember(const IdType& id) noexcept
		{
			std::unique_lock lock{ myLock };

			size_t result = membersCount.load(std::memory_order_acquire);
			for (auto& member : myMembers)
			{
				if (nullptr != member and id == member->GetID())
				{
					member = nullptr;
					result = membersCount.fetch_sub(1, std::memory_order_relaxed) - 1;

					break;
				}
			}

			membersCount.store(result, std::memory_order_release);
			return result;
		}

		template<invocables Predicate>
		size_t RemoveMember(const IdType& id, Predicate&& pred) noexcept
		{
			std::unique_lock lock{ myLock };

			size_t result = membersCount.load(std::memory_order_acquire);
			for (auto& member : myMembers)
			{
				if (nullptr != member and id == member->GetID())
				{
					member = nullptr;
					result = membersCount.fetch_sub(1, std::memory_order_relaxed) - 1;
					if (0 == result)
					{
						std::invoke(std::forward<Predicate>(pred));
					}

					break;
				}
			}

			membersCount.store(result, std::memory_order_release);
			return result;
		}

		void ClearMembers() noexcept
		{
			std::unique_lock lock{ myLock };
			for (auto& member : myMembers)
			{
				member = nullptr;
			}
		}

		[[nodiscard]]
		bool CanStartGame() const noexcept
		{
			std::unique_lock lock{ myLock };
			return minUsersNumberForGame <= membersCount;
		}

		[[nodiscard]]
		bool HasMember(const IdType& id) const noexcept
		{
			std::unique_lock lock{ myLock };

			for (auto& member : myMembers)
			{
				if (nullptr != member and id == member->GetID())
				{
					return true;
				}
			}

			return false;
		}

		[[nodiscard]]
		size_t GetMembersCount() const noexcept
		{
			std::shared_lock lock{ myLock };
			return membersCount.load(std::memory_order_relaxed);
		}

		[[nodiscard]]
		bool IsFull() const noexcept
		{
			std::shared_lock lock{ myLock };
			return maxUsersNumberInRoom <= membersCount.load(std::memory_order_relaxed);
		}

		[[nodiscard]]
		bool IsEmpty() const noexcept
		{
			std::shared_lock lock{ myLock };
			return 0 == membersCount.load(std::memory_order_relaxed);
		}

	private:
		mutable iconer::util::SharedMutex myLock;
		std::array<iconer::app::User*, maxUsersNumberInRoom> myMembers;
		std::atomic_size_t membersCount;
	};
}
