module;
#include <vector>
#include <mutex>

export module Iconer.Application.Room;
import Iconer.Utility.Concurrency.SharedMutex;
import Iconer.Application.ISession;
import Iconer.Application.User;

export namespace iconer::app
{
	enum class [[nodiscard]] RoomStates
	{
		Idle
		, Reserved
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
			, myMembers()
		{
			myMembers.reserve(maxUsersNumberInRoom);
		}

		explicit constexpr Room(IdType&& id)
			noexcept(nothrow_constructible<Super, const IdType&>)
			: Super(std::move(id))
			, myLock()
			, myMembers()
		{
			myMembers.reserve(maxUsersNumberInRoom);
		}

		bool TryAddMember(iconer::app::User& user)
		{
			std::unique_lock lock{ myLock };

			if (myMembers.size() < maxUsersNumberInRoom)
			{
				return nullptr != myMembers.emplace_back(std::addressof(user));
			}
			else
			{
				return false;
			}
		}

		void RemoveMember(const IdType& id)
		{
			std::unique_lock lock{ myLock };

			for (auto it = myMembers.begin(); myMembers.end() != it; ++it)
			{
				// copy the pointer
				auto user = *it;

				if (nullptr != user and id == user->GetID())
				{
					myMembers.erase(it);
					break;
				}
			}
		}

		void ClearMembers() noexcept
		{
			std::unique_lock lock{ myLock };
			myMembers.clear();
		}

		[[nodiscard]]
		bool CanStartGame() const noexcept
		{
			std::unique_lock lock{ myLock };
			return minUsersNumberForGame <= myMembers.size();
		}

		[[nodiscard]]
		bool HasMember(const IdType& id) const
		{
			std::unique_lock lock{ myLock };

			for (size_t i = 0; i < maxUsersNumberInRoom; ++i)
			{
				if (myMembers.size() <= i) break;

				// copy the pointer
				auto user = *(myMembers.data() + i);
				if (nullptr != user and id == user->GetID())
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
			return myMembers.size();
		}

		[[nodiscard]]
		bool IsFull() const noexcept
		{
			std::shared_lock lock{ myLock };
			return maxUsersNumberInRoom <= myMembers.size();
		}

		[[nodiscard]]
		bool IsEmpty() const noexcept
		{
			std::shared_lock lock{ myLock };
			return myMembers.empty();
		}

	private:
		mutable iconer::util::SharedMutex myLock;
		std::vector<iconer::app::User*> myMembers;
	};
}
