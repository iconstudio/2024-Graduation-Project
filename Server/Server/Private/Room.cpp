module;
#include <memory>
#include <mutex>

module Iconer.Application.Room;
import Iconer.Application.Packet;

void
iconer::app::Room::Awake()
noexcept
{
	preRespondMembersPacket = std::make_unique_for_overwrite<std::byte[]>(packets::SC_RespondMembersPacket::MaxSize());
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
	}

	return std::span<std::byte>{ preRespondMembersPacket.get(), pk.WannabeSize() };
}
