module;
#include <span>

export module Demo.PacketProcessor;
import Iconer.Utility.Chronograph;
import Iconer.Utility.Serializer;
import Iconer.Application.User;
import Iconer.Application.BasicPacket;
import Iconer.Application.Resources.String;
import Iconer.Application.RoomContract;
import Demo.Framework;

export namespace demo
{
	[[nodiscard]]
	ptrdiff_t PacketProcessor(Framework& framework, iconer::app::User& user, std::span<std::byte, Framework::userRecvSize> packet_data, ptrdiff_t last_offset);
}

#define SEND(user_var, method, ...)\
auto sr = ((user_var).method)(__VA_ARGS__);\
if (not sr.first)\
{\
	delete sr.second;\
}

ptrdiff_t
demo::PacketProcessor(demo::Framework& framework
	, iconer::app::User& user
	, std::span<std::byte, demo::Framework::userRecvSize> packet_data
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

	const auto& user_id = user.GetID();

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
				if (not user.BeginClose())
				{
					user.Cleanup();
				}
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

				bool success = false;
				for (auto& room : framework.everyRoom)
				{
					if (room->TryReserveContract())
					{
						room->SetOperation(iconer::app::AsyncOperations::OpReserveRoom);

						if (framework.Schedule(room, user_id))
						{
							room->SetName(room_title);
							success = true;
							break;
						}
						else
						{
							if (room->TryCancelContract())
							{
								room->SetOperation(iconer::app::AsyncOperations::None);
							}
						}
					}
				}

				if (not success)
				{
					// every room is busy
					SEND(user, SendRoomCreationFailedPacket, iconer::app::RoomContract::CannotLocateEmptyRoom);
				}
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

				if (auto room = framework.FindRoom(room_id); nullptr != room)
				{
					if (user.TryChangeState(iconer::app::UserStates::Idle, iconer::app::UserStates::EnteringRoom))
					{
						iconer::util::Chronograph chronograph{};
						static constexpr auto time_limit = iconer::util::Chronograph::Seconds(3);

						while (true)
						{
							if (iconer::app::RoomStates rstate = room->GetState(); rstate == iconer::app::RoomStates::Idle)
							{
								if (user.myRoomId.CompareAndSet(-1, -1))
								{
									user.roomContext.SetOperation(iconer::app::AsyncOperations::OpEnterRoom);

									if (not framework.Schedule(user.roomContext, user_id, static_cast<unsigned long>(room_id)))
									{
										// rollback
										user.TryChangeState(iconer::app::UserStates::EnteringRoom, iconer::app::UserStates::Idle);
										user.roomContext.SetOperation(iconer::app::AsyncOperations::None);

										// server error
										SEND(user, SendRoomJoinFailedPacket, iconer::app::RoomContract::ServerError);
									}

									break; // while (true)
								}
								else
								{
									// rollback
									user.TryChangeState(iconer::app::UserStates::EnteringRoom, iconer::app::UserStates::Idle);

									SEND(user, SendRoomJoinFailedPacket, iconer::app::RoomContract::AnotherRoomIsAlreadyAssigned);

									break; // while (true)
								}
							}

							if (chronograph.HasTimePassed(time_limit))
							{
								// rollback
								user.TryChangeState(iconer::app::UserStates::EnteringRoom, iconer::app::UserStates::Idle);

								SEND(user, SendRoomJoinFailedPacket, iconer::app::RoomContract::RoomIsBusy);

								break; // while (true)
							}
						}
					}
					else
					{
						SEND(user, SendRoomJoinFailedPacket, iconer::app::RoomContract::InvalidOperation);
					}
				}
				else
				{
					// cannot find a room with the id
					SEND(user, SendRoomJoinFailedPacket, iconer::app::RoomContract::NoRoomFoundWithId);
				}
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
				if (user.myRoomId == -1)
				{
					break;
				}
				else
				{
					SEND(user, SendRoomLeftPacket, user_id);
				}
			}
			break;

			case iconer::app::PacketProtocol::CS_GAME_START:
			{
				// Empty packet
				if (user.myRoomId == -1)
				{
					// cannot start a game: The client is not in a room
					SEND(user, SendCannotStartGamePacket, 0);
				}
				else if (auto room = framework.FindRoom(user.myRoomId); nullptr != room)
				{
					if (not user.TryChangeState(iconer::app::UserStates::InRoom, iconer::app::UserStates::MakingGame))
					{
						// cannot start a game: The client is busy
						SEND(user, SendCannotStartGamePacket, 2);
					}
					else if (not room->CanStartGame())
					{
						// cannot start a game: The room is lack of members
						SEND(user, SendCannotStartGamePacket, 3);
					}
					else
					{
						user.roomContext.SetOperation(iconer::app::AsyncOperations::OpCreateGame);

						// make clients getting ready for game
						if (not framework.Schedule(user.roomContext, user_id))
						{
							// rollback
							user.TryChangeState(iconer::app::UserStates::MakingGame, iconer::app::UserStates::InRoom);
							user.roomContext.SetOperation(iconer::app::AsyncOperations::None);

							// cannot start a game: server error
							SEND(user, SendCannotStartGamePacket, 1000);
						}
					}
				}
				else
				{
					// cannot start a game: The client has a invalid room
					SEND(user, SendCannotStartGamePacket, 1);
				}
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

			case iconer::app::PacketProtocol::CS_MY_TRANSFORM:
			{
				float pl{}, pr{}, pu{};
				iconer::util::Deserialize(iconer::util::Deserialize(iconer::util::Deserialize(last_buf, pl), pr), pu);

				user.RotationLook({ pl, 0, 0 });
				user.RotationRight({ 0, pr, 0 });
				user.RotationUp({ 0, 0, pu });
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
