module;
#include <string_view>
module Demo.Framework;

struct RoomProcedure : public iconer::app::TimerProcedure
{
	using Super = iconer::app::TimerProcedure;

	RoomProcedure(iconer::app::Room* room, std::uint32_t milliseconds)
		: Super(room->myTimer, milliseconds, true)
		, myRoom(room)
	{}

	virtual bool operator()() override
	{
		std::println("Room {} update", myRoom->GetID());

		return true;
	}

	iconer::app::Room* myRoom;
};

bool
demo::Framework::OnCreateGame(iconer::app::User& user)
{
	const auto room_id = user.myRoomId.Load();
	if (-1 == room_id)
	{
		return false;
	}

	auto room = FindRoom(room_id);
	if (nullptr == room)
	{
		return false;
	}
	else if (room->GetMembersCount() == 0)
	{
		// rollback
		user.myRoomId = -1;

		return false;
	}
	else if (not room->HasMember(user.GetID()))
	{
		// rollback
		user.myRoomId = -1;

		return false;
	}
	else if (not room->TryGettingReady())
	{
		return false;
	}
	else if (room->GetState() != iconer::app::RoomStates::Ready)
	{
		return false;
	}
	else
	{
		room->SetTimer(iconer::app::StartTimer(room_id, RoomProcedure{ room, 100 });

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
	const auto room_id = user.myRoomId.Load();
	if (-1 == room_id)
	{
		return;
	}

	auto room = FindRoom(room_id);
	if (nullptr == room)
	{
		return;
	}

	room->TryCancelReady();
	//else if (not room->TryBeginGame())
	//{
	//	return false;
	//}
	//room->TryCancelBeginGame();
}

bool
demo::Framework::OnGameIsLoaded(iconer::app::User& user)
{
	return false;
}
