module;
module Iconer.Application.User;
import Iconer.Application.Packet;

void
iconer::app::User::Awake()
{
	mySocket.IsAddressReusable = true;

	ContextType::Clear();
	recvOffset = 0;
	myName.reserve(nicknameLength);

	preSignInPacket = std::make_unique<std::byte[]>(packets::SC_SucceedSignInPacket::WannabeSize());
	preRoomCreationPacket = std::make_unique<std::byte[]>(packets::SC_RoomCreatedPacket::WannabeSize());

	const packets::SC_SucceedSignInPacket signin_pk{ myHandle };
	signin_pk.Write(preSignInPacket.get());
}

iconer::app::User::IoResult
iconer::app::User::SendSignInPacket()
{
	return mySocket.Send(*this, preSignInPacket.get(), packets::SC_SucceedSignInPacket::WannabeSize());
}

std::pair<iconer::app::User::IoResult, iconer::app::BlobSendContext*>
iconer::app::User::SendPositionPacket(iconer::app::User::IdType id, float x, float y, float z)
{
	const iconer::app::packets::SC_UpdatePositionPacket pk{ id, x, y, z };
	iconer::app::BlobSendContext* ctx = new iconer::app::BlobSendContext{ pk.Serialize(), pk.WannabeSize() };

	return { mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize()), ctx };
}

iconer::app::User::IoResult
iconer::app::User::SendRoomCreatedPacket(iconer::app::User::IdType room_id)
{
	const packets::SC_RoomCreatedPacket pk{ room_id };
	pk.Write(preSignInPacket.get());

	return mySocket.Send(roomContext, preSignInPacket.get(), pk.WannabeSize());
}

std::pair<iconer::app::User::IoResult, iconer::app::BlobSendContext*>
iconer::app::User::SendRoomCreationFailedPacket(int reason)
{
	const iconer::app::packets::SC_RoomCreationFailedPacket pk{ reason };
	iconer::app::BlobSendContext* ctx = new iconer::app::BlobSendContext{ pk.Serialize(), pk.WannabeSize() };

	return { mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize()), ctx };
}

std::pair<iconer::app::User::IoResult, iconer::app::BlobSendContext*>
iconer::app::User::SendRoomJoinedPacket(iconer::app::User::IdType who, iconer::app::User::IdType room_id)
{
	const iconer::app::packets::SC_RoomJoinedPacket pk{ who, room_id };
	iconer::app::BlobSendContext* ctx = new iconer::app::BlobSendContext{ pk.Serialize(), pk.WannabeSize() };

	return { mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize()), ctx };
}

std::pair<iconer::app::User::IoResult, iconer::app::BlobSendContext*>
iconer::app::User::SendRoomJoinFailedPacket(int reason)
{
	const iconer::app::packets::SC_RoomJoinFailedPacket pk{ reason };
	iconer::app::BlobSendContext* ctx = new iconer::app::BlobSendContext{ pk.Serialize(), pk.WannabeSize() };

	return { mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize()), ctx };
}
