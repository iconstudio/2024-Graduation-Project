#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <MSWSock.h>
#include <utility>
#include <mutex>
#include "IconerBlueprinter.h"
#include "NativeSocket.h"

constinit static inline std::once_flag internalInitFlag{};
constinit static inline ::WSAOVERLAPPED rioContext{};
constinit static inline ::RIO_EXTENSION_FUNCTION_TABLE rioFunctions{};
constinit static inline ::LPFN_ACCEPTEX fnAcceptEx = nullptr;
constinit static inline ::LPFN_TRANSMITFILE fnTransmitFile = nullptr;

Expected<bool, ::DWORD> RawSetOption(const ::FNativeSocket& sock, int option, const void* buffer, int buff_size) noexcept;
Expected<int, ::DWORD> RawGetOption(const ::FNativeSocket& sock, int option) noexcept;
void CALLBACK rioRoutine(const ::DWORD err, const ::DWORD bytes, ::LPWSAOVERLAPPED ctx, const ::DWORD flags);
void InitializeSocketSystemImpl(const ::FNativeSocket& fsocket) noexcept;

FNativeSocket::FNativeSocket()
noexcept
	: FHandleObject()
	, myProtocol(), myFamily()
	//, IsAddressReusable(this, false, FNativeSocket::InternalSetAddressReusable)
{}

FNativeSocket::FNativeSocket(const uint64& handle, const EInternetProtocol& protocol, const EIpAddressFamily family)
noexcept
	: FHandleObject(static_cast<int64>(handle))
	, myProtocol(protocol), myFamily(family)
{
	InitializeSocketSystemImpl(*this);
}

FNativeSocket::FNativeSocket(const int64& handle, const EInternetProtocol& protocol, const EIpAddressFamily family)
noexcept
	: FHandleObject(handle)
	, myProtocol(protocol), myFamily(family)
{
	InitializeSocketSystemImpl(*this);
}

FNativeSocket::FNativeSocket(uint64&& handle, const EInternetProtocol& protocol, const EIpAddressFamily family)
noexcept
	: FHandleObject(static_cast<int64>(handle))
	, myProtocol(protocol), myFamily(family)
{
	InitializeSocketSystemImpl(*this);
}

FNativeSocket::FNativeSocket(int64&& handle, const EInternetProtocol& protocol, const EIpAddressFamily family)
noexcept
	: FHandleObject(static_cast<int64&&>(handle))
	, myProtocol(protocol), myFamily(family)
{
	InitializeSocketSystemImpl(*this);
}

bool
FNativeSocket::IsAvailable()
const noexcept
{
	return NULL != GetHandle();
}

FNativeSocket
FNativeSocket::Create(const EIoSynchronousType& type, const EInternetProtocol& protocol, const EIpAddressFamily& family)
noexcept
{
	const auto flags = static_cast<std::underlying_type_t<EIoSynchronousType>>(type);

	uint64 result;
	switch (protocol)
	{
		case EInternetProtocol::TCP:
		{
			result = ::WSASocket(static_cast<int>(family), SOCK_STREAM, ::IPPROTO::IPPROTO_TCP, nullptr, 0, flags);
		}
		break;

		case EInternetProtocol::UDP:
		{
			result = ::WSASocket(static_cast<int>(family), SOCK_DGRAM, ::IPPROTO::IPPROTO_UDP, nullptr, 0, flags);
		}
		break;

		case EInternetProtocol::Unknown:
		{
			return {};
		}
	}

	return FNativeSocket{ result, protocol, family };
}

FNativeSocket
FNativeSocket::Create(const EIoSynchronousType& type, const EInternetProtocol& protocol, const EIpAddressFamily& family, EErrorCode& error_code)
noexcept
{
	if (FNativeSocket result = Create(type, protocol, family); result.IsAvailable())
	{
		return result;
	}
	else
	{
		error_code = UNetworkUtility::AcquireNetworkError();
		return {};
	}
}

bool
FNativeSocket::TryCreate(const EIoSynchronousType& type, const EInternetProtocol& protocol, const EIpAddressFamily& family, FNativeSocket& out)
noexcept
{
	if (FNativeSocket result = Create(type, protocol, family); result.IsAvailable())
	{
		out = std::move(result);

		return true;
	}
	else
	{
		return false;
	}
}

bool
FNativeSocket::TryCreate(const EIoSynchronousType& type, const EInternetProtocol& protocol, const EIpAddressFamily& family, FNativeSocket& out, EErrorCode& error_code)
noexcept
{
	if (FNativeSocket result = Create(type, protocol, family); result.IsAvailable())
	{
		out = std::move(result);

		return true;
	}
	else
	{
		error_code = UNetworkUtility::AcquireNetworkError();

		return false;
	}
}

Expected<FNativeSocket, EErrorCode>
FNativeSocket::TryCreate(const EIoSynchronousType& type, const EInternetProtocol& protocol, const EIpAddressFamily& family)
noexcept
{
	if (FNativeSocket result = Create(type, protocol, family); result.IsAvailable())
	{
		return std::move(result);
	}
	else
	{
		return Unexpected{ UNetworkUtility::AcquireNetworkError() };
	}
}

void
FNativeSocket::InternalSetAddressReusable(FNativeSocket& target, bool& flag)
noexcept
{
	target.SetAddressReusable(flag);
}

void
FNativeSocket::SetAddressReusable(const bool flag) const
noexcept
{
	::BOOL iflag = static_cast<::BOOL>(flag);

	RawSetOption(*this, SO_REUSEADDR, std::addressof(iflag), sizeof(iflag));
}

bool
FNativeSocket::GetAddressReusable()
const noexcept
{
	return RawGetOption(*this, SO_REUSEADDR).Translate([](int&&) noexcept -> Expected<bool, ::DWORD> {
		return true;
	}).Else([](::DWORD&&) noexcept -> Expected<bool, int> {
		return false;
	}).Value();
}

bool
USocketFactory::InitializeSocketSystem(const FNativeSocket& fsocket)
noexcept
{
	::GUID fntable_id = WSAID_MULTIPLE_RIO;
	::DWORD temp_bytes = 0;

	::GUID* fntable_addr = std::addressof(fntable_id);
	::DWORD* bytes_addr = std::addressof(temp_bytes);

	const auto handle = static_cast<uint64>(fsocket.GetHandle());

	int result =
		::WSAIoctl(handle, SIO_GET_MULTIPLE_EXTENSION_FUNCTION_POINTER
		, fntable_addr, sizeof(GUID)
		, reinterpret_cast<void**>(std::addressof(rioFunctions)), sizeof(rioFunctions)
		, bytes_addr
		, std::addressof(rioContext), ::rioRoutine);
	if (0 != result)
	{
		return false;
	}

	fntable_id = WSAID_ACCEPTEX;
	result =
		::WSAIoctl(handle, SIO_GET_EXTENSION_FUNCTION_POINTER
		, fntable_addr, sizeof(GUID)
		, std::addressof(fnAcceptEx), sizeof(fnAcceptEx)
		, bytes_addr
		, nullptr, nullptr);
	if (0 != result)
	{
		return false;
	}

	fntable_id = WSAID_TRANSMITFILE;
	result =
		::WSAIoctl(handle, SIO_GET_EXTENSION_FUNCTION_POINTER
		, fntable_addr, sizeof(GUID)
		, std::addressof(fnTransmitFile), sizeof(fnTransmitFile)
		, bytes_addr
		, nullptr, nullptr);
	if (0 != result)
	{
		return false;
	}

	return true;
}

FNativeSocket
USocketFactory::CreateNativeSocket(int32 type, int32 protocol, int32 family)
noexcept
{
	return FNativeSocket::Create(static_cast<EIoSynchronousType>(type), static_cast<EInternetProtocol>(protocol), static_cast<EIpAddressFamily>(family));
}

bool
USocketFactory::TryCreateNativeSocket(int32 type, int32 protocol, int32 family
	, FNativeSocket& out
	, int32& error_code)
noexcept
{
	EErrorCode err{};
	const bool result = FNativeSocket::TryCreate(static_cast<EIoSynchronousType>(type), static_cast<EInternetProtocol>(protocol), static_cast<EIpAddressFamily>(family), out, err);
	error_code = static_cast<int32>(err);

	return result;
}

Expected<bool, ::DWORD>
RawSetOption(const ::FNativeSocket& sock, int option, const void* buffer, int buff_size)
noexcept
{
	if (0 == ::setsockopt(sock.GetHandle()
		, SOL_SOCKET
		, option
		, reinterpret_cast<const char*>(buffer), buff_size))
	{
		return true;
	}

	return Unexpected{ UNetworkUtility::AcquireNetworkErrorByInteger() };
}

Expected<int, ::DWORD>
RawGetOption(const ::FNativeSocket& sock, int option)
noexcept
{
	int result = 0;
	int len = sizeof(int);

	if (0 == ::getsockopt(sock.GetHandle()
		, SOL_SOCKET
		, option
		, reinterpret_cast<char*>(std::addressof(result)), std::addressof(len)))
	{
		return result;
	}

	return Unexpected{ UNetworkUtility::AcquireNetworkErrorByInteger() };
}

void
CALLBACK rioRoutine(const ::DWORD err, const ::DWORD bytes, ::LPWSAOVERLAPPED ctx, const ::DWORD flags)
{
	if (0 != err)
	{
		//std::println("Socket error: {}", err);
	}
}

void
InitializeSocketSystemImpl(const::FNativeSocket& fsocket)
noexcept
{
	std::call_once(internalInitFlag, USocketFactory::InitializeSocketSystem, std::cref(fsocket));
}
