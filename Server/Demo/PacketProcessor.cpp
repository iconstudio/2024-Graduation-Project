module;
module Demo.PacketProcessor;
import Iconer.Utility.Chronograph;
import Iconer.Application.RoomContract;
import Iconer.Application.User;
import Demo.Framework;

#define SEND(user_var, method, ...)\
auto sr = ((user_var).method)(__VA_ARGS__);\
if (not sr.first)\
{\
	delete sr.second;\
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
		SEND(user, SendRoomLeftPacket, user.GetID());
	}
}

void
demo::OnGameStartSignal(demo::Framework& framework, iconer::app::User& user)
{
	if (user.myRoomId == -1)
	{
		// cannot start a game: The client is not in a room
		SEND(user, SendCannotStartGamePacket, 0);
	}
	else if (auto room = framework.FindRoom(user.myRoomId); nullptr != room)
	{
		IGNORE_DISCARDED_BEGIN;
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
			if (not framework.Schedule(user.roomContext, user.GetID()))
			{
				// rollback
				user.TryChangeState(iconer::app::UserStates::MakingGame, iconer::app::UserStates::InRoom);
				user.roomContext.SetOperation(iconer::app::AsyncOperations::None);

				// cannot start a game: server error
				SEND(user, SendCannotStartGamePacket, 1000);
			}
		}
		IGNORE_DISCARDED_END;
	}
	else
	{
		// cannot start a game: The client has a invalid room
		SEND(user, SendCannotStartGamePacket, 1);
	}
}

void
demo::OnReceivePosition(iconer::app::User& user, float x, float y, float z)
{
	user.PositionX(x);
	user.PositionY(y);
	user.PositionZ(z);

	auto r = user.SendPositionPacket(user.GetID(), x, y, z);
	if (not r.first)
	{
		delete r.second;
	}
}

void
demo::OnReceiveRotation(iconer::app::User& user, float roll, float yaw, float pitch)
{
	user.RotationLook({ roll, 0, 0 });
	user.RotationRight({ 0, yaw, 0 });
	user.RotationUp({ 0, 0, pitch });
}
