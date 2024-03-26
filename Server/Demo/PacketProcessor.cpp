module;
module Demo.PacketProcessor;
import Iconer.Utility.Chronograph;
import Iconer.Application.RoomContract;
import Iconer.Application.User;
import Iconer.Application.Room;
import Demo.Framework;

#define SEND(user_var, method, ...)\
auto [io, ctx] = ((user_var).method)(__VA_ARGS__);\
if (not io)\
{\
	ctx.Complete(); \
}

#define IGNORE_DISCARDED_BEGIN \
__pragma (warning(push)) \
__pragma (warning(disable : 4834)) \

#define IGNORE_DISCARDED_END \
__pragma (warning(pop))

void
demo::OnSignOut(iconer::app::User& user)
{
	if (not user.BeginClose())
	{
		user.Cleanup();
	}
}

void
demo::OnRequestVersion(Framework& framework, iconer::app::User& user)
{
	if (user.GetState() != iconer::app::UserStates::None)
	{
		SEND(user, SendRespondVersionPacket);
	}
}

void
demo::OnRequestRoomList(Framework& framework, iconer::app::User& user)
{
	if (user.GetState() != iconer::app::UserStates::None)
	{
		(void)framework.Schedule(user.requestContext, user.GetID());
	}
}

void
demo::OnRequestMemberList(Framework& framework, iconer::app::User& user)
{
	if (user.GetState() != iconer::app::UserStates::None)
	{
		(void)framework.Schedule(user.requestMemberContext, user.GetID());
	}
}

void
demo::OnCreateRoom(demo::Framework& framework, iconer::app::User& user, const wchar_t(&room_title)[16])
{
	bool success = false;
	for (auto& room : framework.everyRoom)
	{
		if (room->TryReserveContract())
		{
			room->SetOperation(iconer::app::AsyncOperations::OpReserveRoom);

			if (framework.Schedule(room, user.GetID()))
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

void
demo::OnJoinRoom(demo::Framework& framework, iconer::app::User& user, const std::int32_t& room_id)
{
	if (auto room = framework.FindRoom(room_id); nullptr != room)
	{
		IGNORE_DISCARDED_BEGIN;
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

						if (not framework.Schedule(user.roomContext, user.GetID(), static_cast<unsigned long>(room_id)))
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
		IGNORE_DISCARDED_END;
	}
	else
	{
		// cannot find a room with the id
		SEND(user, SendRoomJoinFailedPacket, iconer::app::RoomContract::NoRoomFoundWithId);
	}
}

void
demo::OnLeaveRoom(demo::Framework& framework, iconer::app::User& user)
{
	if (user.myRoomId != -1)
	{
		// Send the packet and produce a event
		SEND(user, SendRoomLeftPacket, user.GetID(), true);
	}
}

namespace ESagaGameContract
{
	enum [[nodiscard]] Type : std::uint8_t
	{
		Unknown = 0
		, NotInRoom
		, ClientIsBusy // The client's state is unmatched
		, LackOfMember
		, InvalidRoom
		, InvalidOperation // Room task is invalid
		, UnstableRoom // Room's state is changed at time
		, ServerError // Unknown internal error
	};
}

void
demo::OnGameStartSignal(demo::Framework& framework, iconer::app::User& user)
{
	if (user.myRoomId == -1)
	{
		// cannot prepare the game: The client is not in a room
		SEND(user, SendCannotStartGamePacket, ESagaGameContract::NotInRoom);
	}
	else if (auto room = framework.FindRoom(user.myRoomId); nullptr != room)
	{
		IGNORE_DISCARDED_BEGIN;
		if (not user.TryChangeState(iconer::app::UserStates::InRoom, iconer::app::UserStates::MakingGame))
		{
			// cannot prepare the game: The client is busy
			SEND(user, SendCannotStartGamePacket, ESagaGameContract::ClientIsBusy);
		}
		else if (not room->CanStartGame())
		{
			// cannot prepare the game: The room is lack of members
			SEND(user, SendCannotStartGamePacket, ESagaGameContract::LackOfMember);
		}
		else
		{
			// make clients getting ready for game
			if (not framework.Schedule(user.gameContext, user.GetID()))
			{
				// rollback
				user.TryChangeState(iconer::app::UserStates::MakingGame, iconer::app::UserStates::InRoom);

				// cannot prepare the game: server error
				SEND(user, SendCannotStartGamePacket, ESagaGameContract::ServerError);
			}
		}
		IGNORE_DISCARDED_END;
	}
	else
	{
		// cannot prepare the game: The client has a invalid room
		SEND(user, SendCannotStartGamePacket, ESagaGameContract::InvalidRoom);
	}
}

void
demo::OnGameLoadedSignal(demo::Framework& framework, iconer::app::User& user)
{
	if (user.myRoomId == -1)
	{
		// cannot start a game: The client is not in a room
		SEND(user, SendCannotStartGamePacket, ESagaGameContract::NotInRoom);
	}
	else if (auto room = framework.FindRoom(user.myRoomId); room != nullptr)
	{
		if (not room->CanStartGame())
		{
			// cannot prepare the game: not qualified conditions
			SEND(user, SendCannotStartGamePacket, ESagaGameContract::LackOfMember);
		}
		else if (not user.TryChangeState(iconer::app::UserStates::InRoom, iconer::app::UserStates::MakingGame))
		{
			// this client is ready for game, mark actually ready
			if (not framework.Schedule(user.loadingContext, user.GetID()))
			{
				// rollback
				user.TryChangeState(iconer::app::UserStates::MakingGame, iconer::app::UserStates::InRoom);

				// cannot prepare the game: server error
				SEND(user, SendCannotStartGamePacket, ESagaGameContract::ServerError);
			}
		}
		else
		{
			// cannot prepare the game: The client is busy
			SEND(user, SendCannotStartGamePacket, ESagaGameContract::ClientIsBusy);
		}
		//room->ReadyMember(user);
	}
	else
	{
		// cannot start a game: The client has a invalid room
		SEND(user, SendCannotStartGamePacket, ESagaGameContract::InvalidRoom);
	}
}

void
demo::OnTeamChanged(demo::Framework& framework, iconer::app::User& user, bool is_red_team)
{
	if (user.myRoomId != -1)
	{
		const auto& user_id = user.GetID();

		if (auto room = framework.FindRoom(user.myRoomId); room != nullptr)
		{
			if (room->GetState() != iconer::app::RoomStates::Idle)
			{
				return;
			}

			if (room->HasMember(user.GetID()))
			{
				user.myTeamId = is_red_team ? iconer::app::Team::Red : iconer::app::Team::Blue;
				room->ForEach([user_id, is_red_team](iconer::app::User& user)
					{
						SEND(user, SendChangeTeamPacket, user_id, is_red_team);
					}
				);
			}
		}
	}
}

void
demo::OnReceivePosition(demo::Framework& framework, iconer::app::User& user, float x, float y, float z)
{
	user.PositionX(x);
	user.PositionY(y);
	user.PositionZ(z);

	auto room_id = user.myRoomId.Load();
	auto room = framework.FindRoom(room_id);

	room->ForEach([&user, x, y, z](iconer::app::User& member)
		{
			auto [io, ctx] = member.SendPositionPacket(user.GetID(), x, y, z);
			if (not io)
			{
				ctx.Complete();
			}
		}
	);
}

void
demo::OnReceiveRotation(Framework& framework, iconer::app::User& user, float roll, float yaw, float pitch)
{
	user.RotationLook({ roll, 0, 0 });
	user.RotationRight({ 0, yaw, 0 });
	user.RotationUp({ 0, 0, pitch });

	auto room_id = user.myRoomId.Load();
	auto room = framework.FindRoom(room_id);

	room->ForEach([&user, roll, yaw, pitch](iconer::app::User& member) {
		auto [io, ctx] = member.SendPositionPacket(user.GetID(), roll, yaw, pitch);
		if (not io)
		{
			ctx.Complete();
		}
		});
}

#define ICONER_UNLIKELY [[unlikely]]
#define ICONER_LIKELY [[likely]]

ptrdiff_t
demo::PacketProcessor(demo::Framework& framework
	, iconer::app::User& user
	, std::span<std::byte> packet_data
	, ptrdiff_t last_offset)
{
	if (nullptr == packet_data.data()) ICONER_UNLIKELY
	{
		constexpr auto & msg = iconer::app::GetResourceString<3>();
		throw msg.data();
	};

	iconer::app::PacketProtocol protocol;
	std::int16_t pk_size = 0;
	const std::byte* last_buf = iconer::util::Deserialize(iconer::util::Deserialize(packet_data.data(), protocol), pk_size);

	if (pk_size <= 0) ICONER_UNLIKELY
	{
		constexpr auto & msg = iconer::app::GetResourceString<4>();
		throw msg.data();
	};

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
			OnRequestVersion(framework, user);
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
			OnRequestMemberList(framework, user);
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
			OnGameLoadedSignal(framework, user);
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

			OnReceivePosition(framework, user, px, py, pz);
		}
		break;

		case iconer::app::PacketProtocol::CS_MY_TRANSFORM:
		{
			float pl{}, pr{}, pu{};
			iconer::util::Deserialize(iconer::util::Deserialize(iconer::util::Deserialize(last_buf, pl), pr), pu);

			OnReceiveRotation(framework, user, pl, pr, pu);
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

		case iconer::app::PacketProtocol::CS_SET_TEAM:
		{
			std::int8_t team_id{};
			iconer::util::Deserialize(last_buf, team_id);

			// 0 :  red team
			// 1 : blue team
			OnTeamChanged(framework, user, team_id == 0);
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
