module;
#include <vector>
#include <span>
#include <algorithm>
#include <mutex>

module Iconer.Application.Room;
import Iconer.Utility.AtomicSwitcher;
import Iconer.Application.User;
import Iconer.Application.Packet;

void
iconer::app::Room::Awake()
noexcept
{
	preRespondMembersPacket = std::make_unique_for_overwrite<std::byte[]>(packets::SC_RespondMembersPacket::MaxSize());
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
	iconer::util::AtomicSwitcher capture{ membersCount };
	unsigned long long& count = capture.GetValue();

	if (count < maxUsersNumberInRoom)
	{
		for (auto& member : myMembers)
		{
			if (nullptr == member)
			{
				member = std::addressof(user);

				++count;

				isMemberUpdated = true;
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
	iconer::util::AtomicSwitcher capture{ membersCount };
	unsigned long long& count = capture.GetValue();

	for (auto it = myMembers.begin(); it != myMembers.end(); ++it)
	{
		auto& member = *it;
		if (nullptr != member and id == member->GetID())
		{
			member = nullptr;

			if (0 < count)
			{
				--count;
			}

			isMemberUpdated = true;
			return true;
		}
	}

	return false;
}

bool
iconer::app::Room::RemoveMember(const iconer::app::Room::IdType& id, const iconer::app::Room::MemberRemover& predicate)
volatile
{
	iconer::util::AtomicSwitcher capture{ membersCount };
	unsigned long long& count = capture.GetValue();

	if (0 < count)
	{
		for (auto& member : myMembers)
		{
			if (nullptr != member and id == member->GetID())
			{
				member = nullptr;

				if (0 < count)
				{
					--count;
				}

				std::invoke(std::as_const(predicate), *this, count);

				isMemberUpdated = true;
				return true;
			}
		}
	}

	return false;
}

bool
iconer::app::Room::RemoveMember(const iconer::app::Room::IdType& id, iconer::app::Room::MemberRemover&& predicate)
volatile
{
	iconer::util::AtomicSwitcher capture{ membersCount };
	unsigned long long& count = capture.GetValue();

	if (0 < count)
	{
		for (auto& member : myMembers)
		{
			if (nullptr != member and id == member->GetID())
			{
				member = nullptr;

				if (0 < count)
				{
					--count;
				}

				std::invoke(std::move(predicate), *this, count);

				isMemberUpdated = true;
				return true;
			}
		}
	}

	return false;
}

size_t
iconer::app::Room::ReadyMember(iconer::app::User& user)
volatile noexcept
{
	size_t result{};
	for (auto& member : myMembers)
	{
		if (nullptr != member)
		{
			if (user.GetID() == member->GetID())
			{
				if (user.isReady.CompareAndSet(false, true))
				{
					++result;
				}
			}
			else if (user.isReady)
			{
				++result;
			}

			break;
		}
	}

	return result;
}

void
iconer::app::Room::ClearMembers()
volatile noexcept
{
	for (auto& member : myMembers)
	{
		member = nullptr;
	}

	membersCount = 0;
	isMemberUpdated = true;
}

std::vector<iconer::app::User*>
iconer::app::Room::AcquireMemberList()
const volatile
{
	return std::vector<User*>{ std::from_range, myMembers };
}

std::span<std::byte>
iconer::app::Room::SerializeMembers()
volatile
{
	thread_local static packets::SC_RespondMembersPacket pk{};
	auto ptr = preRespondMembersPacket.get();

	if (isMemberUpdated)
	{
		pk.serializedMembers.clear();
		for (auto& member : myMembers)
		{
			if (nullptr != member)
			{
				pk.AddMember(member->GetID(), member->GetName());
			}
		}

		pk.Write(ptr);
		isMemberUpdated = false;

		return std::span<std::byte>{ ptr, pk.WannabeSize() };
	}
	else
	{
		return std::span<std::byte>{ ptr, packets::SC_RespondMembersPacket::MinSize() + sizeof(iconer::app::packets::datagrams::SerializedMember) * membersCount + sizeof(size_t) };
	}
}

bool
iconer::app::Room::CanStartGame()
const volatile noexcept
{
	return minUsersNumberForGame <= membersCount;
}

bool
iconer::app::Room::HasMember(const iconer::app::Room::IdType& id)
const volatile noexcept
{
	for (auto& member : myMembers)
	{
		if (nullptr != member and id == member->GetID())
		{
			return true;
		}
	}

	return false;
}

size_t
iconer::app::Room::GetMembersCount()
const volatile noexcept
{
	return membersCount.load(std::memory_order_relaxed);
}

bool
iconer::app::Room::IsFull()
const volatile noexcept
{
	return maxUsersNumberInRoom <= membersCount.load(std::memory_order_relaxed);
}

bool
iconer::app::Room::IsEmpty()
const volatile noexcept
{
	return 0 == membersCount.load(std::memory_order_relaxed);
}
