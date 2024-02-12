module Demo.Framework.PacketProcessor;
import Iconer.Utility.Serializer;
import Iconer.Application.Packet;
import Iconer.Application.Resources.String;
import <memory>;
import <string>;
import <string_view>;

using namespace iconer;

ptrdiff_t
demo::PacketProcessor(Framework& framework
	, const app::User& user
	, std::span<std::byte, Framework::userRecvSize> packet_data
	, ptrdiff_t last_offset)
{
	if (nullptr == packet_data.data())
	{
		auto& msg = app::StaticString<3>();
		throw msg.data();
	}

	app::PacketProtocol protocol;
	std::int16_t size = 0;
	const std::byte* last_buf = util::Deserialize(util::Deserialize(packet_data.data(), protocol), size);

	if (0 <= size)
	{
		auto& msg = app::StaticString<4>();
		throw msg.data();
	}

	const auto& user_id = user.GetID();

	auto& unknown_packet_errmsg = app::StaticString<5>();
	auto& notsupported_packet_errmsg = app::StaticString<11>();

	if (size <= last_offset)
	{
		switch (protocol)
		{
			case app::PacketProtocol::UNKNOWN:
			{
				throw unknown_packet_errmsg.data();
			}

			case app::PacketProtocol::CS_SIGNIN:
			{
				throw notsupported_packet_errmsg.data();
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
				throw unknown_packet_errmsg.data();
			}
		}

		return size;
	}
	else
	{
		return 0;
	}
}