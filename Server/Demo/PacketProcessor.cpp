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
	, app::User& user
	, std::span<std::byte, Framework::userRecvSize> packet_data
	, ptrdiff_t last_offset)
{
	if (nullptr == packet_data.data())
	{
		constexpr auto& msg = app::GetResourceString<3>();
		throw msg.data();
	}

	app::PacketProtocol protocol;
	std::int16_t pk_size = 0;
	const std::byte* last_buf = util::Deserialize(util::Deserialize(packet_data.data(), protocol), pk_size);

	if (pk_size <= 0)
	{
		constexpr auto& msg = app::GetResourceString<4>();
		throw msg.data();
	}

	const auto& user_id = user.GetID();

	constexpr auto& unknown_packet_errmsg = app::GetResourceString<5>();
	constexpr auto& notsupported_packet_errmsg = app::GetResourceString<11>();

	if (pk_size <= last_offset)
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
				if (not user.BeginClose())
				{
					user.Cleanup();
				}
			}
			break;

			case app::PacketProtocol::CS_SIGNUP:
			{

			}
			break;

			case app::PacketProtocol::CS_REQUEST_VERSION:
			{
				// Empty packet
			}
			break;

			case app::PacketProtocol::CS_REQUEST_ROOMS:
			{
				// Empty packet
			}
			break;

			case app::PacketProtocol::CS_REQUEST_USERS:
			{
				// Empty packet
			}
			break;

			case app::PacketProtocol::CS_ROOM_CREATE:
			{
				wchar_t room_title[16]{};
				util::Deserialize(last_buf, 16, room_title);

				bool success = false;
				for (auto& room : framework.everyRoom)
				{
					if (room->TryChangeState(app::RoomStates::None, app::RoomStates::Reserved))
					{
						if (framework.Schedule(room, user_id))
						{
							room->SetOperation(app::AsyncOperations::OpReserveRoom);
							room->SetName(room_title);
							success = true;
							break;
						}
						else
						{
							room->TryChangeState(app::RoomStates::Reserved, app::RoomStates::None);
						}
					}
				}

				if (not success)
				{
					// 1: every room is busy
					auto r = user.SendRoomCreationFailedPacket(1);
					if (not r.first)
					{
						delete r.second;
					}
				}
			}
			break;

			case app::PacketProtocol::CS_ROOM_DESTROY:
			{
				// Empty packet

			}
			break;

			case app::PacketProtocol::CS_ROOM_JOIN:
			{
				std::int32_t room_id{};
				util::Deserialize(last_buf, room_id);

				auto room = framework.FindRoom(room_id);
				if (nullptr == room)
				{
					// 0: cannot find a room with the id
					auto r = user.SendRoomJoinFailedPacket(0);
					if (not r.first)
					{
						delete r.second;
					}
				}
				else if (not framework.Schedule(room, user_id))
				{
					// 1000: server error
					auto r = user.SendRoomJoinFailedPacket(2);
					if (not r.first)
					{
						delete r.second;
					}
				}
				else
				{
					room->SetOperation(app::AsyncOperations::OpEnterRoom);
				}
			}
			break;

			case app::PacketProtocol::CS_ROOM_MATCH:
			{
				// Empty packet

			}
			break;

			case app::PacketProtocol::CS_ROOM_LEAVE:
			{
				// Empty packet
				framework.OnLeavingRoom(user);
			}
			break;

			case app::PacketProtocol::CS_GAME_START:
			{
				// Empty packet
			}
			break;

			case app::PacketProtocol::CS_GAME_EXIT:
			{
			}
			break;

			case app::PacketProtocol::CS_MY_POSITION:
			{
				float px{}, py{}, pz{};
				util::Deserialize(util::Deserialize(util::Deserialize(last_buf, px), py), pz);

				user.PositionX(px);
				user.PositionY(py);
				user.PositionZ(pz);

				auto r = user.SendPositionPacket(user_id, px, py, pz);
				if (not r.first)
				{
					delete r.second;
				}
			}
			break;

			case app::PacketProtocol::CS_MY_TRANSFORM:
			{
				float pl{}, pr{}, pu{};
				util::Deserialize(util::Deserialize(util::Deserialize(last_buf, pl), pr), pu);

				user.RotationLook({ pl, 0, 0 });
				user.RotationRight({ 0, pr, 0 });
				user.RotationUp({ 0, 0, pu });
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

		return pk_size;
	}
	else
	{
		return 0;
	}
}