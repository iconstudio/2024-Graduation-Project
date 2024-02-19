module;
module Iconer.Application.User;
import Iconer.Application.Packet;
import Iconer.Application.BorrowedSendContext;
import Iconer.Application.BlobSendContext;

void
iconer::app::User::Awake()
{
	mySocket.IsAddressReusable = true;

	ContextType::Clear();
	recvOffset = 0;
	myName.reserve(nicknameLength);

	preSignInPacket = std::make_unique<std::byte[]>(packets::SC_SucceedSignInPacket::WannabeSize());

	const packets::SC_SucceedSignInPacket signin_pk{ myHandle };
	signin_pk.Write(preSignInPacket.get());
}

iconer::app::User::IoResult
iconer::app::User::SendSignInPacket()
{
	return mySocket.Send(*this, preSignInPacket.get(), packets::SC_SucceedSignInPacket::WannabeSize());
}

iconer::app::User::IoResult
iconer::app::User::SendPositionPacket(IdType id, float x, float y, float z)
{
	const iconer::app::packets::SC_UpdatePositionPacket pk{ id, x, y, z };
	iconer::app::BlobSendContext* ctx = new iconer::app::BlobSendContext{ pk.Serialize(), pk.WannabeSize() };

	return mySocket.Send(*ctx, ctx->GetBlob().get(), pk.WannabeSize());
}
