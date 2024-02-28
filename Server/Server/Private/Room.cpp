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
noexcept
{
	std::unique_lock lock{ myLock };

	iconer::util::AtomicSwitcher<std::atomic<unsigned long long>> capture{ membersCount };
	unsigned long long& count = capture.GetValue();

	if (count < maxUsersNumberInRoom)
	{
		for (iconer::app::User*& member : myMembers)
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
noexcept
{
	std::unique_lock lock{ myLock };

	iconer::util::AtomicSwitcher<std::atomic<unsigned long long>> capture{ membersCount };
	unsigned long long& count = capture.GetValue();

	for (auto it = myMembers.begin(); it != myMembers.end(); ++it)
	{
		iconer::app::User*& member = *it;
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
iconer::app::Room::RemoveMember(const iconer::app::Room::IdType& id
	, const iconer::app::Room::MemberRemover& predicate)
{
	std::unique_lock lock{ myLock };

	iconer::util::AtomicSwitcher<std::atomic<unsigned long long>> capture{ membersCount };
	unsigned long long& count = capture.GetValue();

	if (0 < count)
	{
		for (iconer::app::User*& member : myMembers)
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
iconer::app::Room::RemoveMember(const iconer::app::Room::IdType& id
	, iconer::app::Room::MemberRemover&& predicate)
{
	std::unique_lock lock{ myLock };

	iconer::util::AtomicSwitcher<std::atomic<unsigned long long>> capture{ membersCount };
	unsigned long long& count = capture.GetValue();

	if (0 < count)
	{
		for (iconer::app::User*& member : myMembers)
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

bool
iconer::app::Room::RemoveMember(const IdType& id, LockerType& owned_lock) noexcept
{
	std::unique_lock lock{ myLock };

	iconer::util::AtomicSwitcher<std::atomic<unsigned long long>> capture{ membersCount };
	unsigned long long& count = capture.GetValue();

	if (0 < count)
	{
		for (iconer::app::User*& member : myMembers)
		{
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
	}
	owned_lock = std::move(lock);

	return false;
}

bool
iconer::app::Room::RemoveMember(const iconer::app::Room::IdType& id
	, const iconer::app::Room::MemberRemover& predicate
	, iconer::app::Room::LockerType& owned_lock)
{
	std::unique_lock lock{ myLock };

	iconer::util::AtomicSwitcher<std::atomic<unsigned long long>> capture{ membersCount };
	unsigned long long& count = capture.GetValue();

	if (0 < count)
	{
		for (iconer::app::User*& member : myMembers)
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
	owned_lock = std::move(lock);

	return false;
}

bool
iconer::app::Room::RemoveMember(const iconer::app::Room::IdType& id
	, iconer::app::Room::MemberRemover&& predicate
	, iconer::app::Room::LockerType& owned_lock)
{
	std::unique_lock lock{ myLock };

	iconer::util::AtomicSwitcher<std::atomic<unsigned long long>> capture{ membersCount };
	unsigned long long& count = capture.GetValue();

	if (0 < count)
	{
		for (iconer::app::User*& member : myMembers)
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
	owned_lock = std::move(lock);

	return false;
}

size_t
iconer::app::Room::ReadyMember(iconer::app::User& user)
noexcept
{
	std::unique_lock lock{ myLock };

	size_t result{};
	for (iconer::app::User*& member : myMembers)
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
noexcept
{
	std::unique_lock lock{ myLock };
	for (auto& member : myMembers)
	{
		member = nullptr;
	}

	membersCount = 0;
	isMemberUpdated = true;
}

std::vector<iconer::app::User*>
iconer::app::Room::AcquireMemberList()
const
{
	std::unique_lock lock{ myLock };

	return std::vector<User*>{ std::from_range, myMembers };
}

std::span<std::byte>
iconer::app::Room::SerializeMembers()
{
	std::unique_lock lock{ myLock };

	if (isMemberUpdated)
	{
		packets::SC_RespondMembersPacket pk{};

		for (auto& member : myMembers)
		{
			if (nullptr != member)
			{
				pk.AddMember(member->GetID(), member->GetName());
			}
		}

		pk.Write(preRespondMembersPacket.get());
		isMemberUpdated = false;

		return std::span<std::byte>{ preRespondMembersPacket.get(), pk.WannabeSize() };
	}
	else
	{
		return std::span<std::byte>{ preRespondMembersPacket.get(), packets::SC_RespondMembersPacket::MinSize() + sizeof(iconer::app::packets::datagrams::SerializedMember) * membersCount + sizeof(size_t) };
	}
}

bool
iconer::app::Room::CanStartGame() const noexcept
{
	std::shared_lock lock{ myLock };

	return minUsersNumberForGame <= membersCount;
}

bool
iconer::app::Room::HasMember(const iconer::app::Room::IdType& id)
const noexcept
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

size_t
iconer::app::Room::GetMembersCount()
const noexcept
{
	return membersCount.load(std::memory_order_relaxed);
}

bool
iconer::app::Room::IsFull()
const noexcept
{
	return maxUsersNumberInRoom <= membersCount.load(std::memory_order_relaxed);
}

bool
iconer::app::Room::IsEmpty()
const noexcept
{
	return 0 == membersCount.load(std::memory_order_relaxed);
}
