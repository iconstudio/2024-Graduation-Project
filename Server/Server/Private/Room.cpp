module;
#include <mutex>

module Iconer.Application.Room;
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
	size_t result{};
	ForEach([&](User& user) noexcept {
		if (user.GetState() != UserStates::None)
		{
			user.SendGeneralData(nullptr, buffer, size);
		}
	});

	return result;
}

bool
iconer::app::Room::TryAddMember(iconer::app::User& user)
noexcept
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

std::unique_lock<iconer::util::SharedMutex>
iconer::app::Room::RemoveMember(const iconer::app::Room::IdType& id)
noexcept
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
	return std::move(lock);
}

std::unique_lock<iconer::util::SharedMutex>
iconer::app::Room::RemoveMember(const IdType& id, const iconer::app::Room::MemberRemover& predicate)
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
				std::invoke(predicate, *this, --result);
			}

			isMemberUpdated = true;
			break;
		}
	}

	membersCount.store(result, std::memory_order_release);
	return std::move(lock);
}

std::unique_lock<iconer::util::SharedMutex>
iconer::app::Room::RemoveMember(const IdType& id, iconer::app::Room::MemberRemover&& predicate)
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
				std::invoke(predicate, *this, --result);
			}

			isMemberUpdated = true;
			break;
		}
	}

	membersCount.store(result, std::memory_order_release);
	return std::move(lock);
}

size_t
iconer::app::Room::ReadyMember(iconer::app::User& user)
noexcept
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
