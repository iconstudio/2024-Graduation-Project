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

iconer::app::User::IoResult
iconer::app::User::SendGeneralData(IContext* ctx, const std::byte* static_buffer, size_t size)
noexcept
{
	return mySocket.Send(*ctx, static_buffer, size);
}

iconer::app::User::IoResult
iconer::app::User::SendGeneralData(iconer::app::IContext* ctx, const std::byte* static_buffer, size_t size)
const noexcept
{
	return mySocket.Send(*ctx, static_buffer, size);
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendGeneralData(const std::byte* static_buffer, size_t size) const
{
	auto ctx = SendContextPool::Pop();

	return { SendGeneralData(ctx, static_buffer, size), std::move(ctx) };
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendGeneralData(std::unique_ptr<std::byte[]>&& buffer, size_t size)
const
{
	auto ctx = SendContextPool::Pop();
	ctx->SetBlob(std::move(buffer));
	ctx->SetSize(size);

	return { SendGeneralData(ctx, ctx->GetBlob().get(), size), std::move(ctx) };
}

iconer::app::User::IoResult
iconer::app::User::SendSignInPacket()
noexcept
{
	return mySocket.Send(*this, preSignInPacket.get(), packets::SC_SucceedSignInPacket::WannabeSize());
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendRespondVersionPacket() const
{
	static constinit packets::SC_RespondVersionPacket pk{};
	static const auto buffer = pk.Serialize();
	static constexpr auto size = packets::SC_ReadyForGamePacket::WannabeSize();

	// Preserve the serialized packet
	return SendGeneralData(buffer.get(), size);
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendRespondRoomsPacket(std::span<const std::byte> buffer) const
{
	// Preserve the serialized packet
	return SendGeneralData(buffer.data(), buffer.size_bytes());
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendRespondMembersPacket(std::span<const std::byte> buffer) const
{
	// Preserve the serialized packet
	return SendGeneralData(buffer.data(), buffer.size_bytes());
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendPositionPacket(iconer::app::User::IdType id, float x, float y, float z) const
{
	const iconer::app::packets::SC_UpdatePositionPacket pk{ id, x, y, z };

	return SendGeneralData(pk.Serialize(), pk.WannabeSize());
}

iconer::app::User::IoResult
iconer::app::User::SendRoomCreatedPacket(iconer::app::IContext* room, iconer::app::User::IdType room_id)
const
{
	const packets::SC_RoomCreatedPacket pk{ room_id };
	pk.Write(preRoomCreationPacket.get());

	return mySocket.Send(*room, preRoomCreationPacket.get(), pk.WannabeSize());
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendRoomCreationFailedPacket(iconer::app::RoomContract reason)
const
{
	const iconer::app::packets::SC_RoomCreationFailedPacket pk{ reason };

	return SendGeneralData(pk.Serialize(), pk.WannabeSize());
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendRoomJoinedPacket(iconer::app::User::IdType who, iconer::app::User::IdType room_id)
const
{
	const iconer::app::packets::SC_RoomJoinedPacket pk{ who, room_id };

	return SendGeneralData(pk.Serialize(), pk.WannabeSize());
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendRoomJoinFailedPacket(iconer::app::RoomContract reason)
const
{
	const iconer::app::packets::SC_RoomJoinFailedPacket pk{ reason };

	return SendGeneralData(pk.Serialize(), pk.WannabeSize());
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendRoomLeftPacket(IdType who, bool is_self)
const
{
	const iconer::app::packets::SC_RoomLeftPacket pk{ who };

	auto ctx = SendContextPool::Pop();
	ctx->SetBlob(pk.Serialize());
	ctx->SetSize(pk.WannabeSize());

	if (is_self)
	{
		ctx->SetOperation(AsyncOperations::OpLeaveRoom);
	}

	return { mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize()), std::move(ctx) };
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendCannotStartGamePacket(int reason)
const
{
	const iconer::app::packets::SC_FailedGameStartingPacket pk{ reason };

	return SendGeneralData(pk.Serialize(), pk.WannabeSize());
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendChangeTeamPacket(IdType user_id, bool is_red_team)
const
{
	const packets::SC_SetTeamPacket pk{ user_id, is_red_team ? 0 : 1 };

	return SendGeneralData(pk.Serialize(), pk.WannabeSize());
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendMakeGameReadyPacket()
const
{
	static constinit packets::SC_ReadyForGamePacket pk{};
	static const auto buffer = pk.Serialize();
	static constexpr auto size = packets::SC_ReadyForGamePacket::WannabeSize();

	auto ctx = SendContextPool::Pop();

	ctx->SetOperation(AsyncOperations::OpReadyGame);

	return { mySocket.Send(*ctx, buffer.get(), size), std::move(ctx) };
}

iconer::app::User::BorrowedIoResult
iconer::app::User::SendGameJustStartedPacket()
const
{
	static constinit packets::SC_ReadyForGamePacket pk{};
	static const auto buffer = pk.Serialize();
	static constexpr auto size = packets::SC_ReadyForGamePacket::WannabeSize();

	auto ctx = SendContextPool::Pop();

	return { mySocket.Send(*ctx, buffer.get(), size), std::move(ctx) };
}
