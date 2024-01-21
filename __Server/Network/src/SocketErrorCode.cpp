module;
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
module Net.ErrorCode;

net::ErrorCodes
net::AcquireNetworkError()
noexcept
{
	return static_cast<ErrorCodes>(::WSAGetLastError());
}

net::SocketOpenErrorCodes
net::AcquireListeningError()
noexcept
{
	return static_cast<net::SocketOpenErrorCodes>(::WSAGetLastError());
}

net::SocketClosingErrorCodes
net::AcquireClosingError()
noexcept
{
	return static_cast<net::SocketClosingErrorCodes>(::WSAGetLastError());
}

net::SendingErrorCodes
net::AcquireSendingError()
noexcept
{
	return static_cast<net::SendingErrorCodes>(::WSAGetLastError());
}

net::ReceivingErrorCodes
net::AcquireReceivingError()
noexcept
{
	return static_cast<net::ReceivingErrorCodes>(::WSAGetLastError());
}

net::SocketOptionErrorCodes
net::AcquireSocketOptionError()
noexcept
{
	return static_cast<net::SocketOptionErrorCodes>(::WSAGetLastError());
}
