#pragma comment(lib, "Ws2_32.lib")
#include "NativeSocket.h"
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

bool
FNativeSocket::IsAvailable()
const noexcept
{
	return GetHandke() != INVALID_SOCKET;
}
