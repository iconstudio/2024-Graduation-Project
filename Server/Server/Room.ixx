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
		using iterator = MemberStorageType::iterator;
		using const_iterator = MemberStorageType::const_iterator;

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

		void Dirty(bool flag) volatile noexcept;
		[[nodiscard]] bool Dirty() volatile noexcept;

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

		[[nodiscard]]
		constexpr iterator begin() noexcept
		{
			return myMembers.begin();
		}
		
		[[nodiscard]]
		constexpr iterator end() noexcept
		{
			return myMembers.end();
		}
		
		[[nodiscard]]
		constexpr const_iterator begin() const noexcept
		{
			return myMembers.begin();
		}
		
		[[nodiscard]]
		constexpr const_iterator end() const noexcept
		{
			return myMembers.end();
		}
		
		[[nodiscard]]
		constexpr const_iterator cbegin() const noexcept
		{
			return myMembers.cbegin();
		}
		
		[[nodiscard]]
		constexpr const_iterator cend() const noexcept
		{
			return myMembers.cend();
		}
		
		[[nodiscard]]
		constexpr iterator begin() volatile noexcept
		{
			return myMembers.begin();
		}
		
		[[nodiscard]]
		constexpr iterator end() volatile noexcept
		{
			return myMembers.end();
		}
		
		[[nodiscard]]
		constexpr const_iterator begin() const volatile noexcept
		{
			return myMembers.begin();
		}
		
		[[nodiscard]]
		constexpr const_iterator end() const volatile noexcept
		{
			return myMembers.end();
		}
		
		[[nodiscard]]
		constexpr const_iterator cbegin() const volatile noexcept
		{
			return myMembers.cbegin();
		}
		
		[[nodiscard]]
		constexpr const_iterator cend() const volatile noexcept
		{
			return myMembers.cend();
		}

		[[nodiscard]]
		auto CaptureMemberCount() volatile noexcept
		{
			return iconer::util::AtomicSwitcher{ membersCount };
		}

		[[nodiscard]] std::vector<User*> AcquireMemberList() const;
		[[nodiscard]] std::vector<User*> AcquireMemberList() const volatile;
		[[nodiscard]] std::span<std::byte> SerializeMembers() volatile;

		[[nodiscard]] bool HasMember(const IdType& id) const volatile noexcept;
		[[nodiscard]] bool IsEveryMemberIsLoaded() const volatile noexcept;

	private:
		MemberStorageType myMembers;
	};
}
