#pragma comment(lib, "Ws2_32.lib")
#include "NativeSocket.h"
#include "IconerBlueprinter.h"
#include <WinSock2.h>
#include <MSWSock.h>
#include <utility>
#include <mutex>

constinit static inline std::once_flag internalInitFlag{};
constinit static inline ::WSAOVERLAPPED rioContext{};
constinit static inline ::RIO_EXTENSION_FUNCTION_TABLE rioFunctions{};
constinit static inline ::LPFN_ACCEPTEX fnAcceptEx = nullptr;
constinit static inline ::LPFN_TRANSMITFILE fnTransmitFile = nullptr;

static inline constexpr unsigned long DEFAULT_ACCEPT_SIZE = sizeof(SOCKADDR_IN) + 16UL;

Expected<std::monostate, EErrorCode> RawSetOption(const ::FNativeSocket& sock, int option, const void* buffer, int buff_size) noexcept;
Expected<std::monostate, ::DWORD> RawGetOption(const ::FNativeSocket& sock, int option) noexcept;
void CALLBACK rioRoutine(const ::DWORD err, const ::DWORD bytes, LPWSAOVERLAPPED ctx, const ::DWORD flags);
void InitializeSocketSystemImpl(const ::FNativeSocket& fsocket) noexcept;

FNativeSocket::FNativeSocket()
noexcept
	: FHandleObject(INVALID_SOCKET)
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

FNativeSocket::SocketResult
FNativeSocket::Open()
const noexcept
{
	const int open = ::listen(GetHandle(), SOMAXCONN);
	if (SOCKET_ERROR == open)
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}

	return 0U;
}

bool
FNativeSocket::Close()
const noexcept
{
	if (IsAvailable())
	{
		if (ReusableAddress())
		{
			return (1 == ::fnTransmitFile(GetHandle(), nullptr, 0, 0, nullptr, nullptr, TF_DISCONNECT | TF_REUSE_SOCKET));
		}
		else
		{
			return (0 == ::closesocket(GetHandle()));
		}
	}
	else
	{
		return false;
	}
}

bool
FNativeSocket::Close(EErrorCode& error_code)
const noexcept
{
	if (IsAvailable())
	{
		if (ReusableAddress())
		{
			if (1 == ::fnTransmitFile(GetHandle(), nullptr, 0, 0, nullptr, nullptr, TF_DISCONNECT | TF_REUSE_SOCKET))
			{
				return true;
			}
			else
			{
				error_code = UNetworkUtility::AcquireNetworkError();
				return false;
			}
		}
		else
		{
			if (0 == ::closesocket(myHandle))
			{
				return true;
			}
			else
			{
				error_code = UNetworkUtility::AcquireNetworkError();
				return false;
			}
		}
	}
	else
	{
		error_code = EErrorCode::NotASocket;
		return false;
	}
}

bool
FNativeSocket::CloseAsync(FIoContext& context)
const noexcept
{
	return CloseAsync(std::addressof(context));
}

bool
FNativeSocket::CloseAsync(FIoContext& context, EErrorCode& error_code)
const noexcept
{
	return CloseAsync(std::addressof(context), error_code);
}

bool
FNativeSocket::CloseAsync(FIoContext* const context)
const noexcept
{
	if (IsAvailable())
	{
		auto* ctx = reinterpret_cast<LPWSAOVERLAPPED>(context);
		if (ReusableAddress())
		{
			return (1 == ::fnTransmitFile(myHandle, nullptr, 0, 0, ctx, nullptr, TF_DISCONNECT | TF_REUSE_SOCKET));
		}
		else
		{
			return (1 == ::fnTransmitFile(myHandle, nullptr, 0, 0, ctx, nullptr, TF_DISCONNECT));
		}
	}
	else
	{
		return false;
	}
}

bool
FNativeSocket::CloseAsync(FIoContext* const context, EErrorCode& error_code)
const noexcept
{
	if (IsAvailable())
	{
		if (CloseAsync(context))
		{
			return true;
		}
		else
		{
			error_code = UNetworkUtility::AcquireNetworkError();
			return false;
		}
	}
	else
	{
		error_code = EErrorCode::NotASocket;
		return false;
	}
}

FNativeSocket::SocketResult
FNativeSocket::ReserveAccept(FIoContext& context, FNativeSocket& client)
const
{
	return ReserveAccept(std::addressof(context), client);
}

FNativeSocket::SocketResult
FNativeSocket::ReserveAccept(FIoContext& context, FNativeSocket& client, std::span<uint8> accept_buffer)
const
{
	return ReserveAccept(std::addressof(context), client, std::move(accept_buffer));
}

FNativeSocket::SocketResult
FNativeSocket::ReserveAccept(FIoContext* const context, FNativeSocket& client)
const
{
	char temp_buffer[::DEFAULT_ACCEPT_SIZE * 2];
	if (not IsAvailable())
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}

	::DWORD result_bytes{};

	if (1 == ::fnAcceptEx(myHandle, client.GetHandle()
		, temp_buffer, 0UL
		, ::DEFAULT_ACCEPT_SIZE
		, ::DEFAULT_ACCEPT_SIZE
		, std::addressof(result_bytes)
		, reinterpret_cast<::LPWSAOVERLAPPED>(context))
		)
	{
		return result_bytes;
	}
	else
	{
		if (auto error = UNetworkUtility::AcquireNetworkError(); error != EErrorCode::PendedIoOperation)
		{
			return Unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}

FNativeSocket::SocketResult
FNativeSocket::ReserveAccept(FIoContext* const context, FNativeSocket& client, std::span<uint8> accept_buffer)
const
{
	if (not IsAvailable())
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}

	::DWORD result_bytes{};

	if (1 == ::fnAcceptEx(myHandle, client.GetHandle()
		, accept_buffer.data(), static_cast<::DWORD>(accept_buffer.size_bytes())
		, ::DEFAULT_ACCEPT_SIZE
		, ::DEFAULT_ACCEPT_SIZE
		, std::addressof(result_bytes)
		, reinterpret_cast<::LPWSAOVERLAPPED>(context))
		)
	{
		return static_cast<uint32>(result_bytes);
	}
	else
	{
		if (auto error = UNetworkUtility::AcquireNetworkError(); error != EErrorCode::PendedIoOperation)
		{
			return Unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}

FNativeSocket::SocketResult
FNativeSocket::ReserveAccept(FIoContext& context, FNativeSocket& client, const TSharedPtr<uint8>& accept_buffer, size_t size)
const
{
	if (not IsAvailable())
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}

	::DWORD result_bytes{};

	if (1 == ::fnAcceptEx(myHandle, client.GetHandle()
		, accept_buffer.Get(), static_cast<::DWORD>(size)
		, ::DEFAULT_ACCEPT_SIZE
		, ::DEFAULT_ACCEPT_SIZE
		, std::addressof(result_bytes)
		, reinterpret_cast<::LPWSAOVERLAPPED>(std::addressof(context)))
		)
	{
		return static_cast<uint32>(result_bytes);
	}
	else
	{
		if (auto error = UNetworkUtility::AcquireNetworkError(); error != EErrorCode::PendedIoOperation)
		{
			return Unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}

FNativeSocket::SocketResult
FNativeSocket::ReserveAccept(FIoContext* const context, FNativeSocket& client, const TSharedPtr<uint8>& accept_buffer, size_t size)
const
{
	if (not IsAvailable())
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}

	::DWORD result_bytes{};

	if (1 == ::fnAcceptEx(myHandle, client.GetHandle()
		, accept_buffer.Get(), static_cast<::DWORD>(size)
		, ::DEFAULT_ACCEPT_SIZE
		, ::DEFAULT_ACCEPT_SIZE
		, std::addressof(result_bytes)
		, reinterpret_cast<::LPWSAOVERLAPPED>(context))
		)
	{
		return static_cast<uint32>(result_bytes);
	}
	else
	{
		if (auto error = UNetworkUtility::AcquireNetworkError(); error != EErrorCode::PendedIoOperation)
		{
			return Unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}

Expected<std::monostate, EErrorCode>
FNativeSocket::ReusableAddress(bool flag)
noexcept
{
	::BOOL iflag = static_cast<::BOOL>(flag);

	return RawSetOption(*this, SO_REUSEADDR, std::addressof(iflag), sizeof(iflag));
}

bool
FNativeSocket::ReusableAddress()
const noexcept
{
	return RawGetOption(*this, SO_REUSEADDR).Translate([](std::monostate&&) noexcept -> Expected<bool, ::DWORD> {
		return true;
	}).Else([](::DWORD&&) noexcept -> Expected<bool, int> {
		return false;
	}).Value();
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

Expected<std::monostate, EErrorCode>
FNativeSocket::InternalSetAddressReusable(FNativeSocket& target, bool& flag)
noexcept
{
	target.ReusableAddress(flag);
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

Expected<std::monostate, EErrorCode>
RawSetOption(const ::FNativeSocket& sock, int option, const void* buffer, int buff_size)
noexcept
{
	if (0 == ::setsockopt(sock.GetHandle()
		, SOL_SOCKET
		, option
		, reinterpret_cast<const char*>(buffer), buff_size))
	{
		return std::monostate{};
	}

	return Unexpected{ UNetworkUtility::AcquireNetworkError() };
}

Expected<std::monostate, ::DWORD>
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
		return std::monostate{};
	}

	return Unexpected{ static_cast<::DWORD>(UNetworkUtility::AcquireNetworkErrorByInteger()) };
}

void
CALLBACK rioRoutine(const ::DWORD err, const ::DWORD bytes, LPWSAOVERLAPPED ctx, const ::DWORD flags)
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
