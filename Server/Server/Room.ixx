module;
#include <utility>
#include <atomic>
#include <vector>
#include <mutex>

export module Iconer.Application.Room;
import Iconer.Utility.Constraints;
import Iconer.Utility.Concurrency.SharedMutex;
import Iconer.Collection.Array;
import Iconer.Application.ISession;
import Iconer.Application.User;
import <memory>;
import <span>;

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
		//using MemberStorageType = std::array<iconer::app::User*, maxUsersNumberInRoom>;
		using MemberStorageType = iconer::collection::Array<User*, maxUsersNumberInRoom>;

		explicit constexpr Room(const IdType& id)
			noexcept(nothrow_constructible<Super, const IdType&>)
			: Super(id)
			, myLock()
			, myMembers(), membersCount(), readyCount()
			, preRespondMembersPacket()
		{
		}

		explicit constexpr Room(IdType&& id)
			noexcept(nothrow_constructible<Super, IdType&&>)
			: Super(std::move(id))
			, myLock()
			, myMembers(), membersCount(0), readyCount()
			, preRespondMembersPacket()
		{
		}

		void Awake() noexcept;

		void Cleanup() noexcept
		{
			Clear();
			SetState(RoomStates::None);
			SetOperation(AsyncOperations::None);
			ClearMembers();
			membersCount = 0;
		}

		template<invocables<User&> Predicate>
		void ForEach(Predicate&& predicate) const
		{
			auto list = AcquireMemberList();

			for (auto& member : list)
			{
				if (nullptr != member)
				{
					std::invoke(std::forwad<Predicate>(predicate), *member);
				}
			}
		}

		size_t Broadcast(const std::byte* buffer, size_t size) const
		{
			size_t result{};
			ForEach([&](User& user) noexcept {
				if (user.GetState() != UserStates::None)
				{
					user.SendGeneralData(nullptr, buffer, size);
				}
			});

			return result;
		}

		bool TryReserveContract() volatile noexcept
		{
			return TryChangeState(RoomStates::None, RoomStates::Reserved);
		}

		bool TryCancelContract() volatile noexcept
		{
			return TryChangeState(RoomStates::Reserved, RoomStates::None);
		}

		bool TryBeginCreate() volatile noexcept
		{
			return TryChangeState(RoomStates::Reserved, RoomStates::Creating);
		}

		bool TryCancelCreating() volatile noexcept
		{
			return TryChangeState(RoomStates::Creating, RoomStates::None);
		}

		bool TryEstablish() volatile noexcept
		{
			return TryChangeState(RoomStates::Creating, RoomStates::Idle);
		}

		bool TryCancelEstablishing() volatile noexcept
		{
			return TryChangeState(RoomStates::Idle, RoomStates::None);
		}

		void BeginClose() volatile noexcept
		{
			SetState(RoomStates::Closing);
		}

		bool TryBeginClose(RoomStates prev_state) volatile noexcept
		{
			return TryChangeState(prev_state, RoomStates::Closing);
		}

		bool TryEndClose(RoomStates next_state = RoomStates::None) volatile noexcept
		{
			return TryChangeState(RoomStates::Closing, next_state);
		}

		bool TryAddMember(iconer::app::User& user) noexcept
		{
			std::unique_lock lock{ myLock };

			bool result = false;
			auto count = membersCount.load(std::memory_order_acquire);

			if (count < maxUsersNumberInRoom)
			{
				for (auto& member : myMembers)
				{
					if (nullptr == member)
					{
						member = std::addressof(user);
						++count;

						result = true;

						isMemberUpdated = true;
						break;
					}
				}
			}

			membersCount.store(count, std::memory_order_release);
			return result;
		}

		size_t ReadyMember(iconer::app::User& user) noexcept
		{
			std::unique_lock lock{ myLock };

			for (auto& member : myMembers)
			{
				if (nullptr != member and user.GetID() == member->GetID())
				{

					break;
				}
			}
		}

		size_t RemoveMember(const IdType& id) noexcept
		{
			std::unique_lock lock{ myLock };

			size_t result = membersCount.load(std::memory_order_acquire);
			for (auto it = myMembers.begin(); it != myMembers.end(); ++it)
			{
				auto& member = *it;
				if (nullptr != member and id == member->GetID())
				{
					member = nullptr;

					if (0 < result)
					{
						--result;
					}

					isMemberUpdated = true;
					break;
				}
			}

			membersCount.store(result, std::memory_order_release);
			return result;
		}

		template<typename Predicate, typename... Args>
			requires invocables<Predicate, size_t, Args...>
		size_t RemoveMember(const IdType& id, Predicate&& pred, Args&&... args) noexcept(nothrow_invocables<Predicate, size_t, Args...>)
		{
			std::unique_lock lock{ myLock };

			size_t result = membersCount.load(std::memory_order_acquire);
			for (auto& member : myMembers)
			{
				if (nullptr != member and id == member->GetID())
				{
					member = nullptr;

					if (0 < result)
					{
						std::invoke(std::forward<Predicate>(pred), --result, std::forward<Args>(args)...);
					}

					isMemberUpdated = true;
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

			membersCount = 0;
			isMemberUpdated = true;
		}

		[[nodiscard]]
		std::vector<User*> AcquireMemberList() const
		{
			std::unique_lock lock{ myLock };

			return std::vector<User*>{ std::from_range, myMembers };
		}

		[[nodiscard]]
		std::span<std::byte> SerializeMembers();

		[[nodiscard]]
		bool CanStartGame() const noexcept
		{
			std::shared_lock lock{ myLock };

			return minUsersNumberForGame <= membersCount;
		}

		[[nodiscard]]
		bool HasMember(const IdType& id) const noexcept
		{
			std::shared_lock lock{ myLock };

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
			return membersCount.load(std::memory_order_relaxed);
		}

		[[nodiscard]]
		bool IsFull() const noexcept
		{
			return maxUsersNumberInRoom <= membersCount.load(std::memory_order_relaxed);
		}

		[[nodiscard]]
		bool IsEmpty() const noexcept
		{
			return 0 == membersCount.load(std::memory_order_relaxed);
		}

	private:
		mutable iconer::util::SharedMutex myLock;

		MemberStorageType myMembers;
		std::atomic_size_t membersCount;
		std::atomic_size_t readyCount;
		std::atomic_bool isMemberUpdated;

		std::unique_ptr<std::byte[]> preRespondMembersPacket;
	};
}

module :private;

namespace iconer::app::test
{
	void testment()
	{
		Room room{ 0 };

		std::array<int, 3> test_arr{};

		using arr_t = decltype(test_arr);
		using method_arr_size_t = decltype(std::array<int, 3>::size);
		//using method_arr_begin_t = decltype(std::array<int, 3>::begin);
		//const_nothrow_method_t<arr_t, std::array<int, 3>::iterator(*)()> aaa_beg1 = static_cast<>(&test_arr.begin);
		using method_arr_begin_t = decltype(static_cast<std::array<int, 3>::iterator(arr_t::*)()>(&arr_t::begin));

		//auto&& aaa_beg2 = (test_arr.begin);

		constexpr bool aaa1 = methods<method_arr_size_t>;
		constexpr bool aaa2 = methods<method_arr_size_t>;
		constexpr bool bbb = methods<arr_t>;

		constexpr bool ccc = method_invocable<method_arr_size_t, arr_t>;
		constexpr bool ddd = method_invocable<method_arr_begin_t, arr_t>;

		constexpr bool eee = classes<arr_t>;
		constexpr bool fff = methods<method_arr_size_t>;

		std::invoke(&std::array<int, 3>::size, test_arr);
		//std::invoke(std::declval<method_arr_size_t>(), std::declval<arr_t>());

		//room.RemoveMember(0, test_arr, &(std::array<int, 3>::size));
		//room.RemoveMember(0, test_arr, &(std::array<int, 3>::begin));
		//room.RemoveMember(0, test_arr, &(std::array<int, 3>::at), 0ULL);
		//room.RemoveMember(0, room, &(Room::IsFull));
		//room.RemoveMember(0, room, static_cast<size_t(Room::*)()>(&Room::RemoveMember), 0);
	}
}
