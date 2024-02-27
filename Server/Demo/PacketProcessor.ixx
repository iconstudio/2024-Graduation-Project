module;
#include <span>

export module Demo.PacketProcessor;
import Iconer.Utility.Serializer;
import Iconer.Application.BasicPacket;
import Iconer.Application.Resources.String;
import <cstdint>;

export namespace iconer::app
{
	class User;
	class Room;
}

export namespace demo
{
	class Framework;

	[[nodiscard]]
	ptrdiff_t PacketProcessor(Framework& framework, iconer::app::User& user, std::span<std::byte> packet_data, ptrdiff_t last_offset);

	void OnSignOut(iconer::app::User& user);
	void OnRequestRoomList(Framework& framework, iconer::app::User& user);
	void OnCreateRoom(Framework& framework, iconer::app::User& user, const wchar_t (&room_title)[16]);
	void OnJoinRoom(Framework& framework, iconer::app::User& user, const std::int32_t& room_id);
	void OnLeaveRoom(Framework& framework, iconer::app::User& user);
	void OnGameStartSignal(Framework& framework, iconer::app::User& user);
	void OnReceivePosition(iconer::app::User& user, float x, float y, float z);
	void OnReceiveRotation(iconer::app::User& user, float roll, float yaw, float pitch);
}

ptrdiff_t
demo::PacketProcessor(demo::Framework& framework
	, iconer::app::User& user
	, std::span<std::byte> packet_data
	, ptrdiff_t last_offset)
{
	if (nullptr == packet_data.data())
	{
		constexpr auto& msg = iconer::app::GetResourceString<3>();
		throw msg.data();
	}

	iconer::app::PacketProtocol protocol;
	std::int16_t pk_size = 0;
	const std::byte* last_buf = iconer::util::Deserialize(iconer::util::Deserialize(packet_data.data(), protocol), pk_size);

	if (pk_size <= 0)
	{
		constexpr auto& msg = iconer::app::GetResourceString<4>();
		throw msg.data();
	}

	constexpr auto& unknown_packet_errmsg = iconer::app::GetResourceString<5>();
	constexpr auto& notsupported_packet_errmsg = iconer::app::GetResourceString<11>();

	if (pk_size <= last_offset)
	{
		switch (protocol)
		{
			case iconer::app::PacketProtocol::UNKNOWN:
			{
				throw unknown_packet_errmsg.data();
			}

			case iconer::app::PacketProtocol::CS_SIGNIN:
			{
				throw notsupported_packet_errmsg.data();
			}
			break;

			case iconer::app::PacketProtocol::CS_SIGNOUT:
			{
				OnSignOut(user);
			}
			break;

			case iconer::app::PacketProtocol::CS_SIGNUP:
			{

			}
			break;

			case iconer::app::PacketProtocol::CS_REQUEST_VERSION:
			{
				// Empty packet
			}
			break;

			case iconer::app::PacketProtocol::CS_REQUEST_ROOMS:
			{
				// Empty packet
				OnRequestRoomList(framework, user);
			}
			break;

			case iconer::app::PacketProtocol::CS_REQUEST_USERS:
			{
				// Empty packet
			}
			break;

			case iconer::app::PacketProtocol::CS_ROOM_CREATE:
			{
				wchar_t room_title[16]{};
				iconer::util::Deserialize(last_buf, 16, room_title);

				OnCreateRoom(framework, user, room_title);
			}
			break;

			case iconer::app::PacketProtocol::CS_ROOM_DESTROY:
			{
				// Empty packet

			}
			break;

			case iconer::app::PacketProtocol::CS_ROOM_JOIN:
			{
				std::int32_t room_id{};
				iconer::util::Deserialize(last_buf, room_id);

				OnJoinRoom(framework, user, room_id);
			}
			break;

			case iconer::app::PacketProtocol::CS_ROOM_MATCH:
			{
				// Empty packet
			}
			break;

			case iconer::app::PacketProtocol::CS_ROOM_LEAVE:
			{
				// Empty packet
				OnLeaveRoom(framework, user);
			}
			break;

			case iconer::app::PacketProtocol::CS_GAME_START:
			{
				// Empty packet
				OnGameStartSignal(framework, user);
			}
			break;

			case iconer::app::PacketProtocol::CS_GAME_LOADED:
			{
				// Empty packet

				// now start game
			}
			break;

			case iconer::app::PacketProtocol::CS_GAME_EXIT:
			{
			}
			break;

			case iconer::app::PacketProtocol::CS_MY_POSITION:
			{
				float px{}, py{}, pz{};
				iconer::util::Deserialize(iconer::util::Deserialize(iconer::util::Deserialize(last_buf, px), py), pz);

				OnReceivePosition(user, px, py, pz);
			}
			break;

			case iconer::app::PacketProtocol::CS_MY_TRANSFORM:
			{
				float pl{}, pr{}, pu{};
				iconer::util::Deserialize(iconer::util::Deserialize(iconer::util::Deserialize(last_buf, pl), pr), pu);

				OnReceiveRotation(user, pl, pr, pu);
			}
			break;

			case iconer::app::PacketProtocol::CS_MY_INPUT_PRESS:
			{
			}
			break;

			case iconer::app::PacketProtocol::CS_MY_INPUT_RELEASE:
			{
			}
			break;

			case iconer::app::PacketProtocol::CS_MY_ANIMATION_START:
			{
			}
			break;

			case iconer::app::PacketProtocol::CS_MY_ANIMATION_END:
			{
			}
			break;

			case iconer::app::PacketProtocol::CS_CHAT:
			{
			}
			break;

			default:
			{
				throw unknown_packet_errmsg.data();
			}
		}

		return pk_size;
	}
	else
	{
		return 0;
	}
}
