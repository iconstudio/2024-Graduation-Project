#include "NativeSocket.h"

FNativeSocket::FNativeSocket()
noexcept
	: myProtocol(), myFamily()
	//, IsAddressReusable(this, false, FNativeSocket::InternalSetAddressReusable)
{}

bool
FNativeSocket::IsAvailable()
const noexcept
{
	return NULL != GetHandle();
}

FNativeSocket
FNativeSocket::Create(EIoSynchronousType type, const EInternetProtocol& protocol, const EIpAddressFamily& family)
noexcept
{
	return FNativeSocket();
}

FNativeSocket
FNativeSocket::Create(EIoSynchronousType type, const EInternetProtocol& protocol, const EIpAddressFamily& family, EErrorCode& error_code)
noexcept
{
	return FNativeSocket();
}

bool
FNativeSocket::TryCreate(EIoSynchronousType type, const EInternetProtocol& protocol, const EIpAddressFamily& family, FAttentSocket& out)
noexcept
{
	return false;
}

bool
FNativeSocket::TryCreate(EIoSynchronousType type, const EInternetProtocol& protocol, const EIpAddressFamily& family, FAttentSocket& out, EErrorCode& error_code)
noexcept
{
	return false;
}

Expected<FNativeSocket, EErrorCode>
FNativeSocket::TryCreate(EIoSynchronousType type, const EInternetProtocol& protocol, const EIpAddressFamily& family)
noexcept
{
	return Expected<FNativeSocket, EErrorCode>();
}

void
FNativeSocket::InternalSetAddressReusable(FNativeSocket& target, bool& flag)
noexcept
{
	target.SetAddressReusable(flag);
}

void
FNativeSocket::SetAddressReusable(const bool flag)
noexcept
{
}

bool
FNativeSocket::GetAddressReusable()
const noexcept
{
	return false;
}
