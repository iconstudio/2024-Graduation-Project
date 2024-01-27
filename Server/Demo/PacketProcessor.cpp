module;

module Demo.Framework;
import Iconer.Application.Packet;
import <memory>;

using namespace iconer;

void
demo::PacketProcessor(demo::Framework& framework
	, std::uintptr_t session_raw_id
	, void* packet_handle, size_t handle_size)
{
	auto packet_ptr = std::launder(reinterpret_cast<app::BasicPacket*>(packet_handle));
	if (nullptr == packet_ptr)
	{
		throw "Null packet error.";
	}

	const auto protocol = packet_ptr->GetProtocol();
	const auto size = packet_ptr->GetByteSize();

	if (0 == size or 0 == handle_size or size == handle_size)
	{
		throw "Packet size error.";
	}

	switch (protocol)
	{
		case app::PacketProtocol::UNKNOWN:
		{
			throw "Unknown packet.";
		}

		case app::PacketProtocol::CS_SIGNIN:
		{

		}
		break;

		case app::PacketProtocol::CS_SIGNOUT:
		{

		}
		break;

		case app::PacketProtocol::CS_SIGNUP:
		{

		}
		break;

		case app::PacketProtocol::CS_REQUEST_VERSION:
		{
		}
		break;

		case app::PacketProtocol::CS_REQUEST_ROOMS:
		{
		}
		break;

		case app::PacketProtocol::CS_REQUEST_USERS:
		{
		}
		break;

		case app::PacketProtocol::CS_ROOM_CREATE:
		{

		}
		break;

		case app::PacketProtocol::CS_ROOM_DESTROY:
		{

		}
		break;

		case app::PacketProtocol::CS_ROOM_JOIN:
		{

		}
		break;

		case app::PacketProtocol::CS_ROOM_MATCH:
		{

		}
		break;

		case app::PacketProtocol::CS_ROOM_LEAVE:
		{

		} break;

		case app::PacketProtocol::CS_GAME_START:
		{
		}
		break;

		case app::PacketProtocol::CS_GAME_EXIT:
		{
		}
		break;

		case app::PacketProtocol::CS_MY_POSITION:
		{
		}
		break;

		case app::PacketProtocol::CS_MY_TRANSFORM:
		{
		}
		break;

		case app::PacketProtocol::CS_MY_INPUT_PRESS:
		{
		}
		break;

		case app::PacketProtocol::CS_MY_INPUT_RELEASE:
		{
		}
		break;

		case app::PacketProtocol::CS_MY_ANIMATION_START:
		{
		}
		break;

		case app::PacketProtocol::CS_MY_ANIMATION_END:
		{
		}
		break;

		case app::PacketProtocol::CS_CHAT:
		{
		}
		break;
	}
}