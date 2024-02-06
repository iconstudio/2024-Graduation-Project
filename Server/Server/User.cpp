module;
module Iconer.Application.User;
import Iconer.Application.Packet;
import Iconer.Application.BorrowedSendContext;

void
iconer::app::User::Awake()
{
	ContextType::Clear();
	recvOffset = 0;
	myName.reserve(nicknameLength);

	preSignInPacket = std::make_unique<std::byte[]>(packets::SC_SucceedSignInPacket::WannabeSize());

	packets::SC_SucceedSignInPacket signin_pk{};
	signin_pk.Write(preSignInPacket.get());
}

iconer::app::User::IoResult
iconer::app::User::SendSignInPacket()
{
	return mySocket.Send(*this, preSignInPacket.get(), packets::SC_SucceedSignInPacket::WannabeSize());
}
