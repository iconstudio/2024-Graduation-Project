#pragma comment(lib, "Ws2_32.lib")
#include "IconerBlueprinter.h"
#include <WinSock2.h>

uint32
UNetworkUtility::AcquireNetworkErrorByInteger()
noexcept
{
	return ::GetLastError();
}

EErrorCode
UNetworkUtility::AcquireNetworkError()
noexcept
{
	return static_cast<EErrorCode>(::GetLastError());
}
