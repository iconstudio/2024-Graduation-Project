module;
#include <initializer_list>
#include <memory>
#include <vector>

export module Iconer.Application.Room:RoomBase;
export import :RoomStates;
import Iconer.Utility.Constraints;
import Iconer.Application.ISession;

export namespace iconer::app::detail
{
	class [[nodiscard]] RoomBase : public ISession<RoomStates>
	{
	public:
		static inline constexpr size_t maxUsersNumberInRoom = 6;
		static inline constexpr size_t minUsersNumberForGame = 4;

		using Super = iconer::app::ISession<RoomStates>;
		using Super::IdType;

		constexpr RoomBase(const IdType& id)
			noexcept(nothrow_constructible<Super, const IdType&>)
			: Super(id)
			, membersCount(), loadCount()
			, preRespondMembersPacket()
		{
		}

		constexpr RoomBase(IdType&& id)
			noexcept(nothrow_constructible<Super, IdType&&>)
			: Super(std::move(id))
			, membersCount(), loadCount()
			, preRespondMembersPacket()
		{
		}

		void Awake() noexcept
		{}

		void Cleanup() noexcept
		{
			SetState(RoomStates::None);
			SetOperation(AsyncOperations::None);
			loadCount = 0;
		}

		void Cleanup() volatile noexcept
		{
			SetState(RoomStates::None);
			SetOperation(AsyncOperations::None);
			loadCount = 0;
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

		bool TryGettingReady() volatile noexcept
		{
			return TryChangeState(RoomStates::Idle, RoomStates::Ready);
		}

		bool TryCancelReady(RoomStates next_state = RoomStates::Idle) volatile noexcept
		{
			return TryChangeState(RoomStates::Ready, next_state);
		}
		
		bool TryBeginGame() volatile noexcept
		{
			return TryChangeState(RoomStates::Ready, RoomStates::InGame);
		}

		bool TryCancelBeginGame(RoomStates next_state = RoomStates::Idle) volatile noexcept
		{
			return TryChangeState(RoomStates::Ready, next_state);
		}
		
		bool TryCancelBeginGameInGame(RoomStates next_state = RoomStates::Idle) volatile noexcept
		{
			return TryChangeState(RoomStates::InGame, next_state);
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

		[[nodiscard]] size_t GetMembersCount() const volatile noexcept;

		[[nodiscard]] bool IsEmpty() const volatile noexcept;
		[[nodiscard]] bool IsFull() const volatile noexcept;
		[[nodiscard]] bool CanStartGame() const volatile noexcept;

	protected:
		size_t IncreaseReadies() volatile noexcept
		{
			return loadCount.fetch_add(1);
		}

		size_t DecreaseReadies() volatile noexcept
		{
			return loadCount.fetch_sub(1);
		}

		std::atomic_size_t membersCount;
		std::atomic_size_t loadCount;
		std::atomic_bool isMemberUpdated;

		std::unique_ptr<std::byte[]> preRespondMembersPacket;
	};
}
