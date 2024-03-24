module;
#include <string_view>
module Demo.Framework;

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
	else if (not room->TryGettingReady())
	{
		return false;
	}
	else if (room->GetMembersCount() == 0)
	{
		// rollback
		room->TryCancelReady();
		user.myRoomId = -1;

		return false;
	}
	else if (not room->HasMember(user.GetID()))
	{
		// rollback
		room->TryCancelReady();
		user.myRoomId = -1;

		return false;
	}
	else if (room->GetState() != iconer::app::RoomStates::Ready)
	{
		// rollback
		room->TryCancelReady();
		user.myRoomId = -1;

		return false;
	}
	else
	{
		room->ForEach([&user, &room_id](iconer::app::User& member) {
			if (int(iconer::app::UserStates::Idle) <= int(user.GetState()))
			{
				if (member.GetID() != user.GetID()) // `user` already have sent a packet
				{
					// just send the packet
					auto [io, ctx] = member.SendMakeGameReadyPacket();
					if (not io)
					{
						ctx.Complete();
					}
				}
			}
		});
	}

	return false;
}

void
demo::Framework::OnFailedToCreateGame(iconer::app::User& user)
noexcept
{
}
