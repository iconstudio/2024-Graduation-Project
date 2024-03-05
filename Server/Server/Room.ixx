module;
#include <initializer_list>
#include <memory>
#include <vector>
#include <span>

export module Iconer.Application.Room;
import :RoomMember;
import :RoomBase;
export import :RoomStates;
import Iconer.Utility.Constraints;
import Iconer.Collection.Array;

export namespace iconer::app
{
	class [[nodiscard]] Room : public detail::RoomBase
	{
	public:
		struct [[nodiscard]] MemberRemover
		{
			constexpr MemberRemover() noexcept = default;
			virtual constexpr ~MemberRemover() noexcept = default;

			virtual void operator()(volatile Room& room, const size_t& member_count) const = 0;
		};

		using Super = detail::RoomBase;
		using Super::IdType;
		using MemberStorageType = iconer::collection::Array<RoomMember, maxUsersNumberInRoom>;

		explicit constexpr Room(const IdType& id)
			noexcept(nothrow_constructible<Super, const IdType&>)
			: Super(id)
			, myMembers()
		{
		}

		explicit constexpr Room(IdType&& id)
			noexcept(nothrow_constructible<Super, IdType&&>)
			: Super(std::move(id))
			, myMembers()
		{
		}

		void Awake() noexcept;

		void Cleanup() noexcept
		{
			ClearMembers();
			Clear();
			Super::Cleanup();
		}

		void Cleanup() volatile noexcept
		{
			ClearMembers();
			Clear();
			Super::Cleanup();
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
		size_t UnreadyMember(iconer::app::User& user) volatile noexcept;

		[[nodiscard]] std::vector<User*> AcquireMemberList() const;
		[[nodiscard]] std::vector<User*> AcquireMemberList() const volatile;
		[[nodiscard]] std::span<std::byte> SerializeMembers() volatile;

		[[nodiscard]] bool HasMember(const IdType& id) const volatile noexcept;
		[[nodiscard]] bool IsEveryMemberIsLoaded() const volatile noexcept;

	private:
		MemberStorageType myMembers;
	};
}
