module;
#include <string_view>

module Demo.Framework;
import Iconer.Application.Packet;
import Iconer.Application.Resources.String;
import Demo.PacketProcessor;

demo::Framework::IoResult
demo::Framework::OnReceived(iconer::app::User& user, const ptrdiff_t& bytes)
{
	const IdType& id = user.GetID();
	auto user_buffer = GetBuffer(id);
	auto& user_recv_offset = user.recvOffset;

	user_recv_offset += bytes;

	if (user_recv_offset < iconer::app::BasicPacket::SignedMinSize())
	{
		myLogger.DebugLogWarning(iconer::app::GetResourceString<10>());
	}

	while (iconer::app::BasicPacket::SignedMinSize() <= user_recv_offset)
	{
		auto proceed_bytes = PacketProcessor(*this, user, user_buffer, user_recv_offset);
		if (proceed_bytes < 0) [[unlikely]] {
			myLogger.LogWarning(iconer::app::GetResourceString<7>());

			return std::unexpected{ iconer::net::ErrorCode::NoBufferStorage };
		}
		else if (0 == proceed_bytes)
		{
			myLogger.DebugLogWarning(iconer::app::GetResourceString<8>());
			break;
		}
		else
		{
			myLogger.DebugLog(iconer::app::GetResourceString<9>());

			user_recv_offset -= proceed_bytes;
		};
	}

	return user.Receive(user_buffer);
}

void
demo::Framework::OnFailedReceive(iconer::app::User& user)
{
	// Make room out now
	if (auto room_id = user.myRoomId.Exchange(-1); -1 != room_id)
	{
		if (auto room = FindRoom(room_id); nullptr != room)
		{
			if (auto rr = room->RemoveMember(user.GetID()
				, [](volatile iconer::app::Room& room, const size_t& members_count) noexcept {
				if (0 == members_count)
				{
					if (room.TryBeginClose(iconer::app::RoomStates::Idle))
					{
						room.SetOperation(iconer::app::AsyncOperations::OpCloseRoom);
					}
				}
			}); rr)
			{
				if (not Schedule(room, room->GetID()))
				{
					room->Cleanup();
				}

				SetRoomModifiedFlag();
			}
		}
	}

	user.Cleanup();
	user.BeginClose();
}

demo::Framework::IoResult
demo::Framework::OnNotifyRoomsList(iconer::app::User& user)
{
	if (GetRoomModifiedFlag())
	{
		static iconer::app::packets::SC_RespondRoomsPacket pk{};

		pk.serializedRooms.clear();
		for (auto room : everyRoom)
		{
			if (nullptr != room and 0 < room->GetMembersCount())
			{
				pk.AddMember(room->GetID(), room->GetName(), room->GetMembersCount());
			}
		}
		pk.Write(serializedRoomsBuffer.get());
		serializedRoomsBufferSize = pk.WannabeSize();

		SetRoomModifiedFlag();
	}

	auto sender = AcquireSendContext();

	auto io = user.SendGeneralData(sender, serializedRoomsBuffer.get(), serializedRoomsBufferSize);
	if (not io)
	{
		sender->ReturnToBase();
	}

	return std::move(io);
}
