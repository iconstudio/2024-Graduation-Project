module;
#include <array>

export module Iconer.Application.Room;
import Iconer.Utility.Concurrency.SharedMutex;
import Iconer.Application.ISession;
import Iconer.Application.User;

export namespace iconer::app
{
	enum class [[nodiscard]] RoomStates
	{
		None
		, Reserved, Creating // first phases
		, Idle
		, InGame
		, GameDone
		, Cleanup
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
		{}

		explicit constexpr Room(IdType&& id)
			noexcept(nothrow_constructible<Super, IdType&&>)
			: Super(std::move(id))
			, myLock()
			, myMembers(), membersCount(0)
		{}

		void Awake() noexcept
		{
		}

		bool TryAddMember(iconer::app::User& user) noexcept
		{
			std::unique_lock lock{ myLock };

			if (membersCount < maxUsersNumberInRoom)
			{
				return nullptr != (myMembers[membersCount++] = std::addressof(user));
			}
			else
			{
				return false;
			}
		}

		void RemoveMember(const IdType& id) noexcept
		{
			std::unique_lock lock{ myLock };

			for (auto& member : myMembers)
			{
				if (nullptr != member and id == member->GetID())
				{
					member = nullptr;
					break;
				}
			}
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
			return membersCount;
		}

		[[nodiscard]]
		bool IsFull() const noexcept
		{
			std::shared_lock lock{ myLock };
			return maxUsersNumberInRoom <= membersCount;
		}

		[[nodiscard]]
		bool IsEmpty() const noexcept
		{
			std::shared_lock lock{ myLock };
			return 0 == membersCount;
		}

	private:
		mutable iconer::util::SharedMutex myLock;
		std::array<iconer::app::User*, maxUsersNumberInRoom> myMembers;
		size_t membersCount;
	};
}
