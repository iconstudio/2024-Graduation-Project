module;
#include <string_view>

module Demo.Framework;
import Iconer.Application.User;
import Iconer.Application.Packet;
import Iconer.Application.Resources.String;
import Demo.Framework.PacketProcessor;
import <stdexcept>;

demo::Framework::AcceptResult
demo::Framework::OnReserveAccept(iconer::app::User& user)
{
	if (user.TryChangeState(iconer::app::UserStates::None, iconer::app::UserStates::Reserved))
	{
		user.SetOperation(iconer::app::AsyncOperations::OpAccept);
		return serverListener.BeginAccept(user, user.mySocket);
	}
	else
	{
		return iconer::net::ErrorCode::OPERATION_ABORTED;
	}
}

void
demo::Framework::OnFailedReservingAccept()
{
	auto& msg = iconer::app::GetResourceString<6>();
	throw msg.data();
}

demo::Framework::IoResult
demo::Framework::OnUserConnected(iconer::app::User& user)
{
	if (auto fin = user.mySocket.EndAccept(serverListener); fin.has_value())
	{
		return std::unexpected{ fin.value() };
	}
	else if (user.TryChangeState(iconer::app::UserStates::Reserved, iconer::app::UserStates::Connected))
	{
		user.SetOperation(iconer::app::AsyncOperations::OpSignIn);

		return user.Receive(GetBuffer(user.GetID()));
	}
	else
	{
		return std::unexpected{ iconer::net::ErrorCode::OPERATION_ABORTED };
	}
}

void
demo::Framework::OnFailedUserConnect(iconer::app::User& user)
{
	if (not user.BeginClose(iconer::app::UserStates::Reserved))
	{
		// Make room out now
		if (auto room_id = user.myRoomId.Exchange(-1); -1 != room_id)
		{
			if (auto room = FindRoom(room_id); nullptr != room)
			{
				room->RemoveMember(user.GetID());
			}
		}

		user.Cleanup();
	}
}

demo::Framework::IoResult
demo::Framework::OnUserSignedIn(iconer::app::User& user, const ptrdiff_t& bytes)
{
	if (bytes <= 0)
	{
		return std::unexpected{ iconer::net::ErrorCode::OPERATION_ABORTED };
	}

	// Small receiving phase
	auto user_buffer = GetBuffer(user.GetID());
	auto& user_recv_offset = user.recvOffset;

	user_recv_offset += bytes;

	if (iconer::app::packets::CS_SignInPacket::SignedWannabeSize() <= user_recv_offset)
	{
		thread_local iconer::app::packets::CS_SignInPacket pk{};
		pk.Read(user_buffer.data(), user_recv_offset);

		if (pk.myProtocol != iconer::app::PacketProtocol::CS_SIGNIN or pk.mySize <= 0)
		{
			return std::unexpected{ iconer::net::ErrorCode::OPERATION_ABORTED };
		}

		if (true) [[likely]] { // The signing in is succeed
			// Don't necessary to pull back buffer of the receive buffer
			user_recv_offset -= iconer::app::packets::CS_SignInPacket::SignedWannabeSize();

			user.SetName(pk.userName);

			while (not user.TryChangeState(iconer::app::UserStates::Connected, iconer::app::UserStates::PendingID));

			user.SetOperation(iconer::app::AsyncOperations::OpAssignID);

			return user.SendSignInPacket();
		}
		else [[unlikely]] {
			// TODO: send sign in failed packet
			return std::unexpected{ iconer::net::ErrorCode::OPERATION_ABORTED };
		};
	}
	else
	{
		// Restart remain packet bytes
		// Still at OpSignIn
		return user.Receive(user_buffer);
	}
}

void
demo::Framework::OnFailedUserSignIn(iconer::app::User& user)
{
	if (not user.BeginClose())
	{
		// Make room out now
		if (auto room_id = user.myRoomId.Exchange(-1); -1 != room_id)
		{
			if (auto room = FindRoom(room_id); nullptr != room)
			{
				room->RemoveMember(user.GetID());
			}
		}

		user.Cleanup();
	}
}

demo::Framework::IoResult
demo::Framework::OnNotifyUserId(iconer::app::User& user)
{
	if (user.TryChangeState(iconer::app::UserStates::PendingID, iconer::app::UserStates::Idle))
	{
		user.SetOperation(iconer::app::AsyncOperations::OpRecv);

		return user.Receive(GetBuffer(user.GetID()));
	}
	else
	{
		return std::unexpected{ iconer::net::ErrorCode::OPERATION_ABORTED };
	}
}

void
demo::Framework::OnFailedNotifyId(iconer::app::User& user)
{
	if (not user.BeginClose(iconer::app::UserStates::PendingID))
	{
		// Make room out now
		if (auto room_id = user.myRoomId.Exchange(-1); -1 != room_id)
		{
			if (auto room = FindRoom(room_id); nullptr != room)
			{
				room->RemoveMember(user.GetID());
			}
		}

		user.Cleanup();
	}
}

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
			room->RemoveMember(user.GetID());
		}
	}

	user.Cleanup();
	user.BeginClose();
}

iconer::app::RoomContract
demo::Framework::OnReservingRoom(iconer::app::Room& room, iconer::app::User& user)
{
	if (not room.TryCreate())
	{
		// the room is busy
		return iconer::app::RoomContract::RoomIsBusy;
	}
	else
	{
		const auto& room_id = room.GetID();
		if (not user.myRoomId.CompareAndSet(-1, room_id))
		{
			// rollback
			room.TryCancelCreating();
			
			// room is already assigned to the client
			return iconer::app::RoomContract::AnotherRoomIsAlreadyAssigned;

		}
		else if (not room.TryAddMember(user))
		{
			// rollback
			room.TryCancelCreating();
			user.myRoomId.CompareAndSet(room_id, -1);

			// the room is full
			return iconer::app::RoomContract::RoomIsFull;
		}

		user.roomContext.SetOperation(iconer::app::AsyncOperations::OpCreateRoom);

		auto sent_r = user.SendRoomCreatedPacket(room_id);
		if (not sent_r)
		{
			// rollback
			room.TryCancelCreating();
			room.RemoveMember(user.GetID());
			user.myRoomId.CompareAndSet(room_id, -1);

			// failed to notify
			return iconer::app::RoomContract::ServerError;
		}
	}

	return iconer::app::RoomContract::Success;
}

void
demo::Framework::OnFailedToReserveRoom(iconer::app::Room& room, iconer::app::User& user, iconer::app::RoomContract reason)
{
	if (room.TryCancelContract())
	{
		room.SetOperation(iconer::app::AsyncOperations::None);
	}

	room.RemoveMember(user.GetID());
	user.myRoomId.CompareAndSet(room.GetID(), -1);

	auto sent_r = user.SendRoomCreationFailedPacket(reason);
	if (not sent_r.first)
	{
		delete sent_r.second;
	}
}

iconer::app::RoomContract
demo::Framework::OnCreatingRoom(iconer::app::Room& room, iconer::app::User& user)
{
	if (not room.TryChangeState(iconer::app::RoomStates::Creating, iconer::app::RoomStates::Idle))
	{
		// 998: room is unstable
		return iconer::app::RoomContract::UnstableRoom;
	}
	else
	{
		room.SetOperation(iconer::app::AsyncOperations::None);
	}

	return iconer::app::RoomContract::Success;
}

void
demo::Framework::OnFailedToCreateRoom(iconer::app::Room& room, iconer::app::User& user, iconer::app::RoomContract reason)
{
	if (room.TryCancelCreating())
	{
		room.SetOperation(iconer::app::AsyncOperations::None);
	}

	room.RemoveMember(user.GetID());
	user.myRoomId.CompareAndSet(room.GetID(), -1);

	auto sent_r = user.SendRoomCreationFailedPacket(reason);
	if (not sent_r.first)
	{
		delete sent_r.second;
	}
}

iconer::app::RoomContract
demo::Framework::OnJoiningRoom(iconer::app::Room& room, iconer::app::User& user)
{
	if (room.IsFull())
	{
		// room is full
		return iconer::app::RoomContract::RoomIsFull;
	}
	else if (room.GetState() != iconer::app::RoomStates::Idle)
	{
		// room is busy
		return iconer::app::RoomContract::RoomIsBusy;
	}
	else
	{
		const auto& room_id = room.GetID();
		if (not user.myRoomId.CompareAndSet(-1, room_id))
		{
			// another room is already assigned to the client
			return iconer::app::RoomContract::AnotherRoomIsAlreadyAssigned;
		}
		else if (not room.TryAddMember(user))
		{
			// rollback
			user.myRoomId.CompareAndSet(room_id, -1);

			// the room is full
			return iconer::app::RoomContract::RoomIsFull;
		}
	}

	return iconer::app::RoomContract::Success;
}

void
demo::Framework::OnFailedToJoinRoom(iconer::app::Room& room, iconer::app::User& user, iconer::app::RoomContract reason)
{
	auto r = user.SendRoomJoinFailedPacket(reason);
	if (not r.first)
	{
		delete r.second;
	}

	// Dont do it
	//room.RemoveMember(user.GetID());
	//user.myRoomId.CompareAndSet(room.GetID(), -1);
}

bool
demo::Framework::OnLeavingRoom(iconer::app::User& user)
{
	if (auto room_id = user.myRoomId.Exchange(-1); -1 != room_id)
	{
		if (auto room = FindRoom(room_id); nullptr != room)
		{
			room->RemoveMember(user.GetID());
			return true;
		}
	}

	return false;
}

demo::Framework::AcceptResult
demo::Framework::OnUserDisconnected(iconer::app::User& user)
{
	// Reserve the user again
	if (user.EndClose())
	{
		// Make room out now
		if (auto room_id = user.myRoomId.Exchange(-1); -1 != room_id)
		{
			if (auto room = FindRoom(room_id); nullptr != room)
			{
				room->RemoveMember(user.GetID());
			}
		}

		user.Cleanup();

		if (Schedule(user, user.GetID()))
		{
			user.SetOperation(iconer::app::AsyncOperations::OpReserveSession);
			return std::nullopt;
		}
	}

	return iconer::net::ErrorCode::OPERATION_ABORTED;
}
