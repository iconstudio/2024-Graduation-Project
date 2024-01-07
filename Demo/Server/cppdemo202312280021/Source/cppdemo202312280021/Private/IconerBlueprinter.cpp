#pragma comment(lib, "Ws2_32.lib")
#include "IconerBlueprinter.h"
#include <WinSock2.h>

int32
UNetworkUtility::AcquireNetworkErrorByInteger()
noexcept
{
	return static_cast<int32>(::GetLastError());
}

EErrorCode
UNetworkUtility::AcquireNetworkError()
noexcept
{
	return static_cast<EErrorCode>(::GetLastError());
}
