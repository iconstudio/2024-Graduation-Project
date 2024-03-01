module;
module Iconer.Application.User;
import Iconer.Application.Packet;
import Iconer.Application.SendContextPool;

void
iconer::app::User::Awake()
{
	mySocket.IsAddressReusable = true;

	ContextType::Clear();
	recvOffset = 0;
	myName.reserve(nicknameLength);

	preSignInPacket = std::make_unique_for_overwrite<std::byte[]>(packets::SC_SucceedSignInPacket::WannabeSize());
	preRoomCreationPacket = std::make_unique_for_overwrite<std::byte[]>(packets::SC_RoomCreatedPacket::WannabeSize());

	const packets::SC_SucceedSignInPacket signin_pk{ myHandle };
	signin_pk.Write(preSignInPacket.get());
}

std::pair<iconer::app::User::IoResult, iconer::app::BorrowedSendContext*>
iconer::app::User::SendGeneralData(std::unique_ptr<std::byte[]> buffer, size_t size)
const noexcept
{
	auto ctx = SendContextPool::Pop();

	return { mySocket.Send(*ctx, buffer.release(), size), ctx };
}

iconer::app::User::IoResult
iconer::app::User::SendGeneralData(iconer::app::IContext* ctx, const std::byte* static_buffer, size_t size)
const noexcept
{
	return mySocket.Send(*ctx, static_buffer, size);
}

iconer::app::User::IoResult
iconer::app::User::SendSignInPacket()
{
	return mySocket.Send(*this, preSignInPacket.get(), packets::SC_SucceedSignInPacket::WannabeSize());
}

std::pair<iconer::app::User::IoResult, iconer::app::BorrowedSendContext*>
iconer::app::User::SendRespondVersionPacket() const
{
	return std::pair<IoResult, BorrowedSendContext*>();
}

std::pair<iconer::app::User::IoResult, iconer::app::BorrowedSendContext*>
iconer::app::User::SendRespondRoomsPacket(std::span<const std::byte> buffer) const
{
	return std::pair<IoResult, BorrowedSendContext*>();
}

std::pair<iconer::app::User::IoResult, iconer::app::BorrowedSendContext*>
iconer::app::User::SendRespondMembersPacket(std::span<const std::byte> buffer) const
{
	return std::pair<IoResult, BorrowedSendContext*>();
}

std::pair<iconer::app::User::IoResult, iconer::app::BorrowedSendContext*>
iconer::app::User::SendPositionPacket(iconer::app::User::IdType id, float x, float y, float z)
{
	const iconer::app::packets::SC_UpdatePositionPacket pk{ id, x, y, z };

	auto ctx = SendContextPool::Pop();
	ctx->SetBlob(pk.Serialize());
	ctx->SetSize(pk.WannabeSize());

	return { mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize()), ctx };
}

iconer::app::User::IoResult
iconer::app::User::SendRoomCreatedPacket(iconer::app::IContext* room, iconer::app::User::IdType room_id)
const
{
	const packets::SC_RoomCreatedPacket pk{ room_id };
	pk.Write(preRoomCreationPacket.get());

	return mySocket.Send(*room, preRoomCreationPacket.get(), pk.WannabeSize());
}

std::pair<iconer::app::User::IoResult, iconer::app::BorrowedSendContext*>
iconer::app::User::SendRoomCreationFailedPacket(iconer::app::RoomContract reason)
{
	const iconer::app::packets::SC_RoomCreationFailedPacket pk{ reason };

	auto ctx = SendContextPool::Pop();
	ctx->SetBlob(pk.Serialize());
	ctx->SetSize(pk.WannabeSize());

	return { mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize()), ctx };
}

std::pair<iconer::app::User::IoResult, iconer::app::BorrowedSendContext*>
iconer::app::User::SendRoomJoinedPacket(iconer::app::User::IdType who, iconer::app::User::IdType room_id)
{
	const iconer::app::packets::SC_RoomJoinedPacket pk{ who, room_id };

	auto ctx = SendContextPool::Pop();
	ctx->SetBlob(pk.Serialize());
	ctx->SetSize(pk.WannabeSize());

	return { mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize()), ctx };
}

std::pair<iconer::app::User::IoResult, iconer::app::BorrowedSendContext*>
iconer::app::User::SendRoomJoinFailedPacket(iconer::app::RoomContract reason)
{
	const iconer::app::packets::SC_RoomJoinFailedPacket pk{ reason };

	auto ctx = SendContextPool::Pop();
	ctx->SetBlob(pk.Serialize());
	ctx->SetSize(pk.WannabeSize());

	return { mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize()), ctx };
}

std::pair<iconer::app::User::IoResult, iconer::app::BorrowedSendContext*>
iconer::app::User::SendRoomLeftPacket(IdType who, bool is_self)
{
	const iconer::app::packets::SC_RoomLeftPacket pk{ who };

	auto ctx = SendContextPool::Pop();
	ctx->SetBlob(pk.Serialize());
	ctx->SetSize(pk.WannabeSize());

	if (is_self)
	{
		ctx->SetOperation(AsyncOperations::OpLeaveRoom);
	}

	return { mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize()), ctx };
}

std::pair<iconer::app::User::IoResult, iconer::app::BorrowedSendContext*>
iconer::app::User::SendCannotStartGamePacket(int reason)
{
	const iconer::app::packets::SC_FailedGameStartingPacket pk{ reason };

	auto ctx = SendContextPool::Pop();
	ctx->SetBlob(pk.Serialize());
	ctx->SetSize(pk.WannabeSize());

	return { mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize()), ctx };
}

std::pair<iconer::app::User::IoResult, iconer::app::BorrowedSendContext*>
iconer::app::User::SendMakeGameReadyPacket()
{
	static constinit packets::SC_ReadyForGamePacket pk{};
	static const auto buffer = pk.Serialize();
	static constexpr auto size = packets::SC_ReadyForGamePacket::WannabeSize();

	auto ctx = SendContextPool::Pop();
	ctx->SetBlob(pk.Serialize());
	ctx->SetSize(pk.WannabeSize());

	return { mySocket.Send(*ctx, buffer.get(), size), ctx };
}

std::pair<iconer::app::User::IoResult, iconer::app::BorrowedSendContext*>
iconer::app::User::SendGameJustStartedPacket()
{
	const iconer::app::packets::SC_GameStartPacket pk{};

	auto ctx = SendContextPool::Pop();
	ctx->SetBlob(pk.Serialize());
	ctx->SetSize(pk.WannabeSize());

	return { mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize()), ctx };
}
