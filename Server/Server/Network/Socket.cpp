module;
#include <WinSock2.h>
#include <MSWSock.h>
module Iconer.Net.Socket;

using namespace iconer;

net::Socket::Socket()
noexcept
	: Socket(INVALID_SOCKET, InternetProtocol::Unknown, IpAddressFamily::Unknown)
{
}

net::Socket::Socket(net::Socket::HandleType sock, net::InternetProtocol protocol, net::IpAddressFamily family)
noexcept
	: Super(sock)
	, myProtocol(protocol), myFamily(family)
	, IsAddressReusable(this, false, SetAddressReusable)
{
}

void
net::Socket::SetAddressReusable(net::Socket& target, bool flag)
noexcept
{

}