#include "IconerBlueprinter.h"

FNativeSocket
UIconerBlueprinter::CreateNativeSocket(EIoSynchronousType type
	, const EInternetProtocol& protocol, const EIpAddressFamily& family)
	noexcept
{
	return FNativeSocket();
}

bool
UIconerBlueprinter::TryCreateNativeSocket(EIoSynchronousType type
	, const EInternetProtocol& protocol, const EIpAddressFamily& family
	, FAttentSocket& out
	, EErrorCode& error_code)
	noexcept
{
	return false;
}
