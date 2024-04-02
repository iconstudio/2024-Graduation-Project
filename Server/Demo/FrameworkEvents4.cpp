module;
#include <string_view>
#include <print>

module Demo.Framework;
import Iconer.Application.NativeTimer;

struct RoomProcedure;

bool
demo::Framework::OnCreateGame(iconer::app::User& user)
{
	const auto room_id = user.myRoomId.Load();
	if (-1 == room_id)
	{
		// rollback
		user.TryChangeState(iconer::app::UserStates::InRoom, iconer::app::UserStates::Idle);
		user.TryChangeState(iconer::app::UserStates::MakingGame, iconer::app::UserStates::InRoom);

		return false;
	}

	auto room = FindRoom(room_id);
	if (nullptr == room)
	{
		// rollback
		user.TryChangeState(iconer::app::UserStates::InRoom, iconer::app::UserStates::Idle);
		user.TryChangeState(iconer::app::UserStates::MakingGame, iconer::app::UserStates::InRoom);

		return false;
	}
	else if (room->GetMembersCount() == 0)
	{
		// rollback
		user.TryChangeState(iconer::app::UserStates::InRoom, iconer::app::UserStates::Idle);
		user.TryChangeState(iconer::app::UserStates::MakingGame, iconer::app::UserStates::InRoom);
		user.myRoomId = -1;

		return false;
	}
	else if (not room->HasMember(user.GetID()))
	{
		// rollback
		user.TryChangeState(iconer::app::UserStates::InRoom, iconer::app::UserStates::Idle);
		user.TryChangeState(iconer::app::UserStates::MakingGame, iconer::app::UserStates::InRoom);
		user.myRoomId = -1;

		return false;
	}
	else if (not room->TryGettingReady())
	{
		// rollback
		user.TryChangeState(iconer::app::UserStates::InRoom, iconer::app::UserStates::Idle);
		user.TryChangeState(iconer::app::UserStates::MakingGame, iconer::app::UserStates::InRoom);
		user.myRoomId = -1;

		return false;
	}
	else if (room->GetState() != iconer::app::RoomStates::Ready)
	{
		// rollback
		user.TryChangeState(iconer::app::UserStates::InRoom, iconer::app::UserStates::Idle);
		user.TryChangeState(iconer::app::UserStates::MakingGame, iconer::app::UserStates::InRoom);
		user.myRoomId = -1;
		room->TryCancelReady();

		return false;
	}
	else
	{
		room->SetTimer(iconer::app::StartTimer(room_id, RoomProcedure{ room, 10 }));

		room->ForEach([&user, &room_id](iconer::app::User& member)
			{
				if (int(iconer::app::UserStates::Idle) <= int(user.GetState()))
				{
					// just send the packet
					auto [io, ctx] = member.SendMakeGameReadyPacket();
					if (not io)
					{
						ctx.Complete();
					}
				}
			}
		);
	}

	return true;
}

void
demo::Framework::OnFailedToCreateGame(iconer::app::User& user)
noexcept
{
	if (const auto room_id = user.myRoomId.Load(); -1 != room_id)
	{
		auto room = FindRoom(room_id);
		if (nullptr != room)
		{
			room->TryCancelReady();
		}
	}
}

bool
demo::Framework::OnGameIsLoaded(iconer::app::User& user)
{
	const auto room_id = user.myRoomId.Load();
	if (room_id != -1)
	{
		if (auto room = FindRoom(room_id); room != nullptr)
		{
			if (room->ReadyMember(user))
			{
				return true;
			}
		}
		else
		{
			// rollback
			user.TryChangeState(iconer::app::UserStates::InRoom, iconer::app::UserStates::Idle);
			user.TryChangeState(iconer::app::UserStates::MakingGame, iconer::app::UserStates::InRoom);
			user.myRoomId.CompareAndSet(room_id, -1);
		}
	}

	return false;
}

struct RoomProcedure : public iconer::app::TimerProcedure
{
	using Super = iconer::app::TimerProcedure;

	RoomProcedure(iconer::app::Room* room, std::uint32_t milliseconds)
		: Super(room->myTimer, milliseconds, true)
		, myRoom(room)
	{}

	virtual bool operator()() override
	{
		std::println("Update room {}...", myRoom->GetID());

		return true;
	}

	iconer::app::Room* myRoom;
};
