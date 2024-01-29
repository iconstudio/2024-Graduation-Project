module;
module Demo.Framework;
import Iconer.Utility.Serializer;
import Iconer.Application.Packet;
import <memory>;
import <string>;
import <string_view>;

using namespace iconer;

ptrdiff_t
demo::PacketProcessor(demo::Framework& framework
	, app::User& user, const demo::Framework::IdType& user_id, app::UserStates& transit_state
	, std::span<std::byte, demo::Framework::userRecvSize> packet_data
	, ptrdiff_t last_offset)
{
	if (nullptr == packet_data.data())
	{
		throw "Null packet error.";
	}

	app::PacketProtocol protocol;
	std::int16_t size = 0;
	const std::byte* last_buf = util::Deserialize(util::Deserialize(packet_data.data(), protocol), size);

	if (0 == size)
	{
		throw "Packet size error.";
	}

	if (size <= last_offset)
	{
		switch (protocol)
		{
			case app::PacketProtocol::UNKNOWN:
			{
				throw "Unknown packet.";
			}

			case app::PacketProtocol::CS_SIGNIN:
			{

				switch (transit_state)
				{
					case app::UserStates::Idle:
					{

					}
					break;

					case app::UserStates::InLobby:
					{

					}
					break;

					case app::UserStates::InRoom:
					{

					}
					break;

					case app::UserStates::InGame:
					{

					}
					break;

					case app::UserStates::Dead:
					{

					}
					break;

					default:
					{
					}
				}
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

			default:
			{
				throw "Unknown packet.";
			}
		}

		return size;
	}
	else
	{
		return 0;
	}
}