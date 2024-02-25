module Iconer.Application.Room;
import Iconer.Application.Packet;

void
iconer::app::Room::Awake()
noexcept
{
	preRespondMembersPacket = std::make_unique<std::byte[]>(packets::SC_RespondMembersPacket::MaxSize());
}
