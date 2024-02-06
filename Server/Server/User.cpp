module;

module Iconer.Application.User;

void
iconer::app::User::Awake()
{
	ContextType::Clear();
	recvOffset = 0;
	myName.reserve(nicknameLength);
}

iconer::app::User::IoResult
iconer::app::User::SendSignInPacket()
{
	return IoResult();
}
