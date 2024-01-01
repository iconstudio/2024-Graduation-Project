#include "NativeSocket.h"

FNativeSocket::FNativeSocket()
noexcept
	: myProtocol(), myFamily()
	//, IsAddressReusable(this, false, FNativeSocket::InternalSetAddressReusable)
{}

bool FNativeSocket::IsAvailable() const noexcept
{
	return NULL != GetHandle();
}
