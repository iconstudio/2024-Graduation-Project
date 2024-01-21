module;
#pragma comment(lib, "Ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
module Net.Socket;

bool
net::Socket::IsAvailable()
const noexcept
{
	return myHandle != INVALID_SOCKET;
}
