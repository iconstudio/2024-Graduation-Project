module;
#include <initializer_list>
#include <memory>
#include <vector>
#include <span>

export module Iconer.Application.Room;
import Iconer.Utility.Constraints;
import Iconer.Collection.Array;
import Iconer.Application.ISession;

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

	class User;

	class [[nodiscard]] Room : public ISession<RoomStates>
	{
	public:
		static inline constexpr size_t maxUsersNumberInRoom = 6;
		static inline constexpr size_t minUsersNumberForGame = 4;

		struct [[nodiscard]] MemberRemover
		{
			constexpr MemberRemover() noexcept = default;
			virtual constexpr ~MemberRemover() noexcept = default;

			virtual void operator()(volatile Room& room, const size_t& member_count) const = 0;
		};

		using Super = ISession<RoomStates>;
		using Super::IdType;
		using MemberStorageType = iconer::collection::Array<User*, maxUsersNumberInRoom>;

		explicit constexpr Room(const IdType& id)
			noexcept(nothrow_constructible<Super, const IdType&>)
			: Super(id)
			, myMembers(), membersCount(), readyCount()
			, preRespondMembersPacket()
		{
		}

		explicit constexpr Room(IdType&& id)
			noexcept(nothrow_constructible<Super, IdType&&>)
			: Super(std::move(id))
			, myMembers(), membersCount(), readyCount()
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

		void Cleanup() volatile noexcept
		{
			Clear();
			SetState(RoomStates::None);
			SetOperation(AsyncOperations::None);
			ClearMembers();
			membersCount = 0;
		}

		bool TryAddMember(iconer::app::User& user) volatile noexcept;
		bool RemoveMember(const IdType& id) volatile noexcept;
		bool RemoveMember(const IdType& id, const MemberRemover& predicate) volatile;
		bool RemoveMember(const IdType& id, MemberRemover&& predicate) volatile;
		void ClearMembers() volatile noexcept;

		template<invocables<User&> Predicate>
		void ForEach(Predicate&& predicate) const
		{
			auto list = AcquireMemberList();

			for (auto& member : list)
			{
				if (nullptr != member)
				{
					std::invoke(std::move(predicate), *member);
				}
			}
		}
		size_t Broadcast(std::span<IContext*> ctxes, const std::byte* buffer, size_t size) const;
		size_t BroadcastExcept(std::span<IContext*> ctxes, const std::byte* buffer, size_t size, std::initializer_list<IdType> exceptions) const;

		size_t ReadyMember(iconer::app::User& user) volatile noexcept;

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

		[[nodiscard]] std::vector<User*> AcquireMemberList() const volatile;
		[[nodiscard]] std::span<std::byte> SerializeMembers() volatile;

		[[nodiscard]] size_t GetMembersCount() const volatile noexcept;

		[[nodiscard]] bool HasMember(const IdType& id) const volatile noexcept;
		[[nodiscard]] bool IsEmpty() const volatile noexcept;
		[[nodiscard]] bool IsFull() const volatile noexcept;
		[[nodiscard]] bool CanStartGame() const volatile noexcept;

	private:
		MemberStorageType myMembers;
		std::atomic_size_t membersCount;
		std::atomic_size_t readyCount;
		std::atomic_bool isMemberUpdated;

		std::unique_ptr<std::byte[]> preRespondMembersPacket;
	};
}
