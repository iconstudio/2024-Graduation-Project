module;
#include <utility>
#include <vector>
#include <span>
#include <ranges>

module Iconer.Application.Room;
import :RoomMember;
import Iconer.Utility.Constraints;
import Iconer.Application.User;
import Iconer.Application.Packet;

namespace iconer::app
{
	template<typename Predicate>
	bool Remover(volatile Room& room, const iconer::app::User::IdType& user_id, Predicate&& predicate)
		noexcept(nothrow_invocables<Predicate, volatile Room&, size_t>)
	{
		auto capture = room.CaptureMemberCount();
		unsigned long long& count = capture.GetValue();

		auto it = room.begin();
		auto end = room.end();

		while (it != end)
		{
			auto& [member, is_ready] = *it;
			if (nullptr != member and user_id == member->GetID())
			{
				member = nullptr;

				if (0 < count)
				{
					--count;
				}

				std::invoke(std::forward<Predicate>(predicate), room, count);

				is_ready.CompareAndSet(true, false);
				room.Dirty(true);

				return true;
			}

			(void)++it;
		}

		return false;
	}
}

void
iconer::app::Room::Awake()
noexcept
{
	preRespondMembersPacket = std::make_unique_for_overwrite<std::byte[]>(packets::SC_RespondMembersPacket::MaxSize());
}

void
iconer::app::Room::Cleanup()
noexcept
{
	ClearMembers();
	Clear();
	Super::Cleanup();
}

void
iconer::app::Room::Cleanup()
volatile noexcept
{
	ClearMembers();
	Clear();
	Super::Cleanup();
}

size_t
iconer::app::Room::Broadcast(std::span<iconer::app::IContext*> ctxes, const std::byte* buffer, size_t size)
const
{
	std::vector<iconer::app::User*> list = AcquireMemberList();

	if (ctxes.size() < list.size() or size == 0)
	{
		return 0;
	}

	auto it = ctxes.begin();

	size_t result{};
	for (auto ptr : list)
	{
		if (nullptr != ptr)
		{
			iconer::app::User& user = *ptr;

			if (user.GetState() != iconer::app::UserStates::None)
			{
				iconer::app::IContext*& ctx = *it;

				if (not user.SendGeneralData(ctx, buffer, size))
				{
					delete std::exchange(ctx, nullptr);
				}
				else
				{
					(void)++result;
				}
			}
		}
	}

	return result;
}

size_t
iconer::app::Room::BroadcastExcept(std::span<iconer::app::IContext*> ctxes, const std::byte* buffer, size_t size, std::initializer_list<iconer::app::User::IdType> exceptions)
const
{
	std::vector<iconer::app::User*> list = AcquireMemberList();

	if (ctxes.size() < list.size() or size == 0)
	{
		return 0;
	}

	auto it = ctxes.begin();

	size_t result{};
	for (auto ptr : list)
	{
		if (nullptr != ptr)
		{
			iconer::app::User& user = *ptr;

			if (exceptions.end() != std::find_if(exceptions.begin(), exceptions.end()
				, [&user](const iconer::app::User::IdType& rhs) noexcept -> bool {
				return user.GetID() == rhs;
			}))
			{
				continue;
			}

			if (user.GetState() != iconer::app::UserStates::None)
			{
				iconer::app::IContext*& ctx = *it;

				if (not user.SendGeneralData(ctx, buffer, size))
				{
					delete std::exchange(ctx, nullptr);
				}
				else
				{
					(void)++result;
				}
			}
		}
	}

	return result;
}

bool
iconer::app::Room::TryAddMember(iconer::app::User& user)
volatile noexcept
{
	auto capture = CaptureMemberCount();
	unsigned long long& count = capture.GetValue();

	if (count < maxUsersNumberInRoom)
	{
		for (auto& [member, _] : myMembers)
		{
			if (nullptr == member)
			{
				member = std::addressof(user);

				++count;

				Dirty(true);
				return true;
			}
		}
	}

	return false;
}

bool
iconer::app::Room::RemoveMember(const iconer::app::Room::IdType& id)
volatile noexcept
{
	static constexpr auto temp_pred = [](volatile Room&, size_t) noexcept {};

	return Remover(*this, id, temp_pred);
}

bool
iconer::app::Room::RemoveMember(const IdType& id, function_t<void, volatile Room&, const size_t&> predicate) 
volatile
{
	return Remover(*this, id, predicate);
}

bool
iconer::app::Room::RemoveMember(const IdType& id, nothrow_function_t<void, volatile Room&, const size_t&> predicate)
volatile noexcept
{
	return Remover(*this, id, predicate);
}

bool
iconer::app::Room::RemoveMember(const iconer::app::Room::IdType& id, const iconer::app::Room::MemberRemover& predicate)
volatile
{
	return Remover(*this, id, predicate);
}

bool
iconer::app::Room::RemoveMember(const iconer::app::Room::IdType& id, iconer::app::Room::MemberRemover&& predicate)
volatile
{
	return Remover(*this, id, std::move(predicate));
}

size_t
iconer::app::Room::ReadyMember(iconer::app::User& user)
volatile noexcept
{
	size_t result{};
	for (auto& [member, is_ready] : myMembers)
	{
		if (nullptr != member)
		{
			if (user.GetID() == member->GetID())
			{
				if (is_ready.CompareAndSet(false, true))
				{
					++result;
				}
				else if (is_ready)
				{
					++result;
				}
			}
		}
		else
		{
			is_ready.CompareAndSet(true, false);
		}
	}

	return result;
}

size_t
iconer::app::Room::UnreadyMember(iconer::app::User& user)
volatile noexcept
{
	size_t result{};
	for (auto& [member, is_ready] : myMembers)
	{
		if (nullptr != member)
		{
			if (user.GetID() == member->GetID())
			{
				if (is_ready.CompareAndSet(true, false))
				{
					++result;
				}
				else if (is_ready)
				{
					++result;
				}
			}
		}
	}

	return result;
}

void
iconer::app::Room::ClearMembers()
volatile noexcept
{
	for (auto& [member, is_ready] : myMembers)
	{
		member = nullptr;
		is_ready = false;
	}

	membersCount = 0;
	Dirty(true);
}

void
iconer::app::Room::Dirty(bool flag) 
volatile noexcept
{
	isMemberUpdated = flag;
}

bool
iconer::app::Room::Dirty()
const volatile noexcept
{
	return isMemberUpdated;
}

std::vector<iconer::app::User*>
iconer::app::Room::AcquireMemberList()
const
{
	return std::vector<User*>{ std::from_range
		, myMembers | std::views::transform([](auto& member) noexcept -> User* {
		return member.myHandle;
	})
	};
}

std::vector<iconer::app::User*>
iconer::app::Room::AcquireMemberList()
const volatile
{
	return std::vector<User*>{ std::from_range
		, myMembers | std::views::transform([](auto& member) noexcept -> User* {
		return member.myHandle;
	})
	};
}

std::span<std::byte>
iconer::app::Room::SerializeMembers()
volatile
{
	thread_local static packets::SC_RespondMembersPacket pk{};
	auto ptr = const_cast<Room*>(this)->preRespondMembersPacket.get();

	if (Dirty())
	{
		pk.serializedMembers.clear();
		for (auto& [member, _] : myMembers)
		{
			if (nullptr != member)
			{
				pk.AddMember(member->GetID(), member->GetName());
			}
		}

		pk.Write(ptr);
		Dirty(false);

		return std::span<std::byte>{ ptr, pk.WannabeSize() };
	}
	else
	{
		return std::span<std::byte>{ ptr, packets::SC_RespondMembersPacket::MinSize() + sizeof(iconer::app::packets::datagrams::SerializedMember) * membersCount + sizeof(size_t) };
	}
}

bool
iconer::app::Room::HasMember(const iconer::app::Room::IdType& id)
const volatile noexcept
{
	for (auto& [member, _] : myMembers)
	{
		if (nullptr != member and id == member->GetID())
		{
			return true;
		}
	}

	return false;
}

size_t
iconer::app::detail::RoomBase::GetMembersCount()
const volatile noexcept
{
	return membersCount.load(std::memory_order_relaxed);
}

bool
iconer::app::detail::RoomBase::CanStartGame()
const volatile noexcept
{
	return GetState() == iconer::app::RoomStates::Idle and minUsersNumberForGame <= membersCount;
}

bool
iconer::app::detail::RoomBase::IsFull()
const volatile noexcept
{
	return maxUsersNumberInRoom <= membersCount.load(std::memory_order_relaxed);
}

bool
iconer::app::detail::RoomBase::IsEmpty()
const volatile noexcept
{
	return 0 == membersCount.load(std::memory_order_relaxed);
}

bool
iconer::app::Room::IsEveryMemberIsLoaded()
const volatile noexcept
{
	return minUsersNumberForGame <= membersCount and minUsersNumberForGame <= loadCount;
}
