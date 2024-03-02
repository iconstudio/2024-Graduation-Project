module;
#include <string_view>
#include <stdexcept>

module Demo.Framework;
import Iconer.Application.BasicPacket;
import Iconer.Application.Packet;
import Iconer.Application.BorrowedSendContext;
import Iconer.Application.Resources.String;
import Demo.PacketProcessor;

bool RemoveRoomMember(demo::Framework& framework, iconer::app::Room& room, const iconer::app::User::IdType& user_id) noexcept;

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
			::RemoveRoomMember(*this, *room, user.GetID());
		}
	}

	user.Cleanup();
	user.BeginClose();
}

iconer::app::RoomContract
demo::Framework::OnReservingRoom(iconer::app::Room& room, iconer::app::User& user)
{
	if (not room.TryBeginCreate())
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

		room.SetOperation(iconer::app::AsyncOperations::OpCreateRoom);

		auto sent_r = user.SendRoomCreatedPacket(std::addressof(room), room_id);
		if (not sent_r)
		{
			// rollback
			if (room.TryCancelCreating())
			{
				room.SetOperation(iconer::app::AsyncOperations::None);
			}
			::RemoveRoomMember(*this, room, user.GetID());

			user.myRoomId.CompareAndSet(room_id, -1);

			// failed to notify
			return iconer::app::RoomContract::ServerError;
		}
	}

	SetRoomModifiedFlag();
	return iconer::app::RoomContract::Success;
}

void
demo::Framework::OnFailedToReserveRoom(iconer::app::Room& room, iconer::app::User& user, iconer::app::RoomContract reason)
{
	if (room.TryCancelCreating())
	{
		room.SetOperation(iconer::app::AsyncOperations::None);
	}
	else
	{
		room.TryCancelContract();
	}

	::RemoveRoomMember(*this, room, user.GetID());
	user.myRoomId.CompareAndSet(room.GetID(), -1);
	SetRoomModifiedFlag();

	auto [io, ctx] = user.SendRoomCreationFailedPacket(reason);
	if (not io)
	{
		ctx.Complete();
	}
}

iconer::app::RoomContract
demo::Framework::OnCreatingRoom(iconer::app::Room& room, iconer::app::User& user)
{
	if (not room.TryEstablish())
	{
		// room is unstable
		return iconer::app::RoomContract::UnstableRoom;
	}
	else if (not user.TryChangeState(iconer::app::UserStates::Idle, iconer::app::UserStates::InRoom))
	{
		return iconer::app::RoomContract::InvalidOperation;
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

	::RemoveRoomMember(*this, room, user.GetID());
	user.myRoomId.CompareAndSet(room.GetID(), -1);
	SetRoomModifiedFlag();

	auto [io, ctx] = user.SendRoomCreationFailedPacket(reason);
	if (not io)
	{
		ctx.Complete();
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
		// rollback
		user.TryChangeState(iconer::app::UserStates::EnteringRoom, iconer::app::UserStates::Idle);

		// room is busy
		return iconer::app::RoomContract::RoomIsBusy;
	}
	else if (not user.TryChangeState(iconer::app::UserStates::EnteringRoom, iconer::app::UserStates::EnteringRoom))
	{
		// rollback
		user.TryChangeState(iconer::app::UserStates::EnteringRoom, iconer::app::UserStates::Idle);

		return iconer::app::RoomContract::InvalidOperation;
	}
	else
	{
		const auto& room_id = room.GetID();
		if (not user.myRoomId.CompareAndSet(-1, room_id))
		{
			// rollback
			user.TryChangeState(iconer::app::UserStates::EnteringRoom, iconer::app::UserStates::Idle);

			// another room is already assigned to the client
			return iconer::app::RoomContract::AnotherRoomIsAlreadyAssigned;
		}
		else if (not room.TryAddMember(user))
		{
			// rollback
			user.TryChangeState(iconer::app::UserStates::EnteringRoom, iconer::app::UserStates::Idle);
			user.myRoomId.CompareAndSet(room_id, -1);

			// the room is full
			return iconer::app::RoomContract::RoomIsFull;
		}
		else if (not user.TryChangeState(iconer::app::UserStates::EnteringRoom, iconer::app::UserStates::InRoom))
		{
			// rollback
			user.TryChangeState(iconer::app::UserStates::EnteringRoom, iconer::app::UserStates::Idle);
			user.myRoomId.CompareAndSet(room_id, -1);
			::RemoveRoomMember(*this, room, user.GetID());
			SetRoomModifiedFlag();

			return iconer::app::RoomContract::InvalidOperation;
		}

		SetRoomModifiedFlag();

		user.roomContext.SetOperation(iconer::app::AsyncOperations::OpNotifyMember);
		std::span<std::byte> members = room.SerializeMembers();
		auto smr = user.SendGeneralData(std::addressof(user.roomContext), members.data(), members.size());
		if (not smr)
		{
			user.roomContext.SetOperation(iconer::app::AsyncOperations::None);
		}

		return iconer::app::RoomContract::Success;
	}
}

void
demo::Framework::OnFailedToJoinRoom(iconer::app::Room& room, iconer::app::User& user, iconer::app::RoomContract reason)
{
	// rollback
	user.TryChangeState(iconer::app::UserStates::EnteringRoom, iconer::app::UserStates::Idle);
	user.myRoomId.CompareAndSet(room.GetID(), -1);

	if (::RemoveRoomMember(*this, room, user.GetID()))
	{
		SetRoomModifiedFlag();
	}

	auto [io, ctx] = user.SendRoomJoinFailedPacket(reason);
	if (not io)
	{
		ctx.Complete();
	}
}

bool
demo::Framework::OnLeavingRoom(iconer::app::User& user)
{
	if (auto room_id = user.myRoomId.Exchange(-1); -1 != room_id)
	{
		user.TryChangeState(iconer::app::UserStates::InRoom, iconer::app::UserStates::Idle);

		if (auto room = FindRoom(room_id); nullptr != room)
		{
			if (::RemoveRoomMember(*this, *room, user.GetID()))
			{
				SetRoomModifiedFlag();

				room->ForEach([&user, &room_id](iconer::app::User& member) {
					if (int(iconer::app::UserStates::Idle) <= int(user.GetState()))
					{
						if (member.GetID() != user.GetID()) // `user` already have sent a packet
						{
							// just send the packet
							auto [io, ctx] = member.SendRoomLeftPacket(user.GetID(), false);
							if (not io)
							{
								ctx.Complete();
							}
						}
					}
				});

				return true;
			}
		}
	}

	return false;
}

void
demo::Framework::OnClosingRoom(iconer::app::Room& room)
{
	if (room.TryEndClose())
	{
		room.Cleanup();
	}
}

bool
demo::Framework::OnNotifyMemberOfRoom(iconer::app::User& user)
noexcept
{
	if (user.myRoomId == -1)
	{
		return false;
	}
	else if (user.GetState() != iconer::app::UserStates::InRoom)
	{
		return false;
	}

	return true;
}

void
demo::Framework::OnFailedNotifyRoomMember(iconer::app::User& user)
noexcept
{
	user.TryChangeState(iconer::app::UserStates::EnteringRoom, iconer::app::UserStates::Idle);
}

demo::Framework::IoResult
demo::Framework::OnRespondRoomsList(iconer::app::User& user)
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

struct EndToEndRemover final : public iconer::app::Room::MemberRemover
{
	using Super = iconer::app::Room::MemberRemover;

	constexpr EndToEndRemover(demo::Framework& framework) noexcept
		: Super(), myFramework(framework)
	{
	}

	void operator()(volatile iconer::app::Room& room, const size_t& members_count) const noexcept override
	{
		if (0 == members_count)
		{
			room.BeginClose();
			room.SetOperation(iconer::app::AsyncOperations::OpCloseRoom);

			if (not myFramework.Schedule(room, room.GetID()))
			{
				room.Cleanup();
			}
		}
	}

	demo::Framework& myFramework;
};

demo::Framework::AcceptResult
demo::Framework::OnUserDisconnected(iconer::app::User& user)
{
	static EndToEndRemover remover{ *this };

	// Reserve the user again
	if (user.EndClose())
	{
		// Make room out now
		if (auto room_id = user.myRoomId.Exchange(-1); -1 != room_id)
		{
			if (auto room = FindRoom(room_id); nullptr != room)
			{
				if (room->RemoveMember(user.GetID(), remover))
				{
					SetRoomModifiedFlag();
				}
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

bool
RemoveRoomMember(demo::Framework& framework, iconer::app::Room& room, const iconer::app::User::IdType& user_id)
noexcept
{
	struct Remover final : public iconer::app::Room::MemberRemover
	{
		using Super = iconer::app::Room::MemberRemover;

		constexpr Remover(demo::Framework& framework) noexcept
			: Super(), myFramework(framework)
		{
		}

		void operator()(volatile iconer::app::Room& room, const size_t& members_count) const noexcept override
		{
			if (0 == members_count)
			{
				if (room.TryBeginClose(iconer::app::RoomStates::Idle))
				{
					room.SetOperation(iconer::app::AsyncOperations::OpCloseRoom);

					if (not myFramework.Schedule(room, room.GetID()))
					{
						room.Cleanup();
					}
				}
			}
		}

		demo::Framework& myFramework;
	};

	if (auto r = room.RemoveMember(user_id, Remover{ framework }); r)
	{
		framework.SetRoomModifiedFlag();
		return true;
	}
	else
	{
		return false;
	}
}
