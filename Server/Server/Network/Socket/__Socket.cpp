module;
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <MSWSock.h>

module Net.Socket;
import <type_traits>;
import <mutex>;
//import <print>;

net::Socket::SocketResult RawSetOption(const net::NativeSocket& sock, int option, const void* buffer, int buff_size) noexcept;
net::Socket::SocketResult RawGetOption(const net::NativeSocket& sock, int option) noexcept;

static inline constexpr unsigned long DEFAULT_ACCEPT_SIZE = sizeof(SOCKADDR_IN) + 16UL;

using namespace net;

const Socket::EmptySocketType Socket::EmptySocket = {};
::RIO_BUF buf;
static inline constexpr ::SOCKET InvalidSocket = INVALID_SOCKET;
constinit static inline ::SOCKET internalSocket = InvalidSocket;
constinit static inline std::once_flag internalInitFlag{};

constinit static inline ::WSAOVERLAPPED rioContext{};
constinit static inline ::RIO_EXTENSION_FUNCTION_TABLE rioFunctions{};

constinit static inline ::LPFN_ACCEPTEX fnAcceptEx = nullptr;
constinit static inline ::LPFN_TRANSMITFILE fnTransmitFile = nullptr;

static void CALLBACK rioRoutine(const ::DWORD err, const ::DWORD bytes, ::LPWSAOVERLAPPED ctx, const ::DWORD flags)
{
	if (0 != err)
	{
		//std::println("Socket error: {}", err);
	}
}
void SocketFunctionInitializer(const net::NativeSocket& sock);

net::Socket::Socket()
noexcept
	: Socket(EmptySocket)
{}

net::Socket::Socket(EmptySocketType)
noexcept
	: Handler(INVALID_SOCKET)
	, myProtocol(InternetProtocols::Unknown), myFamily(IpAddressFamily::Unknown)
	, IsAddressReusable(this, false, SetAddressReusable)
{}

net::Socket::Socket(net::NativeSocket sock, net::InternetProtocols protocol, net::IpAddressFamily family) noexcept
	: Handler(sock)
	, myProtocol(protocol), myFamily(family)
	, IsAddressReusable(this, false, SetAddressReusable)
{
	std::call_once(internalInitFlag, ::SocketFunctionInitializer, sock);
}

net::Socket&
net::Socket::operator=(EmptySocketType)
noexcept
{
	if (IsAvailable())
	{
		Close();
	}

	return *this = Socket{ EmptySocket };
}

net::Socket::SocketResult
net::Socket::Open()
const noexcept
{
	const int open = ::listen(myHandle, SOMAXCONN);
	if (SOCKET_ERROR == open)
	{
		return unexpected(AcquireNetworkError());
	}

	return 0;
}

bool
net::Socket::Close()
const noexcept
{
	if (IsAvailable())
	{
		if (IsAddressReusable)
		{
			return (1 == ::fnTransmitFile(myHandle, nullptr, 0, 0, nullptr, nullptr, TF_DISCONNECT | TF_REUSE_SOCKET));
		}
		else
		{
			return (0 == ::closesocket(myHandle));
		}
	}
	else
	{
		return false;
	}
}

bool
Socket::Close(net::SocketClosingErrorCodes& error_code)
const noexcept
{
	if (IsAvailable())
	{
		if (IsAddressReusable)
		{
			if (1 == ::fnTransmitFile(myHandle, nullptr, 0, 0, nullptr, nullptr, TF_DISCONNECT | TF_REUSE_SOCKET))
			{
				return true;
			}
			else
			{
				error_code = AcquireClosingError();
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
				error_code = AcquireClosingError();
				return false;
			}
		}
	}
	else
	{
		error_code = SocketClosingErrorCodes::NotASocket;
		return false;
	}
}

bool
net::Socket::CloseAsync(net::IoContext& context)
const noexcept
{
	return CloseAsync(std::addressof(context));
}

bool
net::Socket::CloseAsync(net::IoContext& context, net::SocketClosingErrorCodes& error_code)
const noexcept
{
	return CloseAsync(std::addressof(context), error_code);
}

bool
net::Socket::CloseAsync(net::IoContext* const context)
const noexcept
{
	if (IsAvailable())
	{
		auto* ctx = reinterpret_cast<::LPWSAOVERLAPPED>(context);
		if (IsAddressReusable)
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
net::Socket::CloseAsync(net::IoContext* const context, net::SocketClosingErrorCodes& error_code)
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
			error_code = AcquireClosingError();
			return false;
		}
	}
	else
	{
		error_code = SocketClosingErrorCodes::NotASocket;
		return false;
	}
}

net::SocketResult
net::Socket::ReserveAccept(net::IoContext& context, net::Socket& client)
const
{
	return ReserveAccept(std::addressof(context), client);
}

net::SocketResult
net::Socket::ReserveAccept(net::IoContext& context, Socket& client, std::span<std::byte> accept_buffer)
const
{
	return ReserveAccept(std::addressof(context), client, std::move(accept_buffer));
}

net::SocketResult
net::Socket::ReserveAccept(net::IoContext* const context, net::Socket& client)
const
{
	char temp_buffer[::DEFAULT_ACCEPT_SIZE * 2];
	if (not IsAvailable())
	{
		return unexpected(AcquireNetworkError());
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
		if (auto error = AcquireNetworkError(); error != ErrorCodes::PendedIoOperation)
		{
			return unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}

net::SocketResult
net::Socket::ReserveAccept(net::IoContext* const context, net::Socket& client, std::span<std::byte> accept_buffer)
const
{
	if (not IsAvailable())
	{
		return unexpected(AcquireNetworkError());
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
		return result_bytes;
	}
	else
	{
		if (auto error = AcquireNetworkError(); error != ErrorCodes::PendedIoOperation)
		{
			return unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}

bool
net::Socket::ReusableAddress()
const noexcept
{
	return IsAddressReusable;
}

void
net::Socket::ReusableAddress(bool flag)
noexcept
{
	IsAddressReusable = flag;
}

net::Socket
net::Socket::Create(SocketType type
	, const InternetProtocols& protocol
	, const IpAddressFamily& family)
	noexcept
{
	const auto flags = std::to_underlying(type);

	NativeSocket result;
	switch (protocol)
	{
		case InternetProtocols::TCP:
		{
			result = ::WSASocket(static_cast<int>(family), SOCK_STREAM, ::IPPROTO::IPPROTO_TCP, nullptr, 0, flags);
		}
		break;

		case InternetProtocols::UDP:
		{
			result = ::WSASocket(static_cast<int>(family), SOCK_DGRAM, ::IPPROTO::IPPROTO_UDP, nullptr, 0, flags);
		}
		break;

		case InternetProtocols::Unknown:
		{
			return EmptySocket;
		}
	}

	return Socket(result, protocol, family);
}

Socket
Socket::Create(SocketType type
	, const InternetProtocols& protocol
	, const IpAddressFamily& family
	, ErrorCodes& error_code)
	noexcept
{
	if (Socket result = Create(type, protocol, family); result.IsAvailable())
	{
		return result;
	}
	else
	{
		error_code = AcquireNetworkError();
		return EmptySocket;
	}
}

bool
Socket::TryCreate(SocketType type
	, const InternetProtocols& protocol
	, const IpAddressFamily& family
	, AttentSocket& out)
	noexcept
{
	if (Socket result = Create(type, protocol, family); result.IsAvailable())
	{
		out = AttentSocket
		{
			.Socket = std::move(result)
		};

		return true;
	}
	else
	{
		return false;
	}
}

bool
Socket::TryCreate(SocketType type
	, const InternetProtocols& protocol
	, const IpAddressFamily& family
	, AttentSocket& out
	, ErrorCodes& error_code)
	noexcept
{
	if (Socket result = Create(type, protocol, family); result.IsAvailable())
	{
		out = AttentSocket
		{
			.Socket = std::move(result)
		};

		return true;
	}
	else
	{
		error_code = AcquireNetworkError();
		return false;
	}
}

Socket::FactoryResult
Socket::TryCreate(SocketType type
	, const InternetProtocols& protocol
	, const IpAddressFamily& family)
	noexcept
{
	if (Socket result = Create(type, protocol, family); result.IsAvailable())
	{
		return std::move(result);
	}
	else
	{
		return unexpected(AcquireNetworkError());
	}
}

void
Socket::SetAddressReusable(Socket& target, bool& flag)
noexcept
{
	::BOOL iflag = static_cast<::BOOL>(flag);

	RawSetOption(target.myHandle, SO_REUSEADDR, std::addressof(iflag), sizeof(iflag));
}

net::Socket::SocketResult
RawSetOption(const net::NativeSocket& sock, int option, const void* buffer, int buff_size)
noexcept
{
	if (0 == ::setsockopt(sock
		, SOL_SOCKET
		, option
		, reinterpret_cast<const char*>(buffer), buff_size))
	{
		return 1;
	}

	return unexpected(AcquireNetworkError());
}

net::Socket::SocketResult
RawGetOption(const net::NativeSocket& sock, int option)
noexcept
{
	int result = 0;
	int len = sizeof(int);

	if (0 == ::getsockopt(sock
		, SOL_SOCKET
		, option
		, reinterpret_cast<char*>(std::addressof(result)), std::addressof(len)))
	{
		return result;
	}

	return unexpected(AcquireNetworkError());
}

void
SocketFunctionInitializer(const net::NativeSocket& sock)
{
	::GUID fntable_id = WSAID_MULTIPLE_RIO;
	::DWORD temp_bytes = 0;

	::GUID* fntable_addr = std::addressof(fntable_id);
	::DWORD* bytes_addr = std::addressof(temp_bytes);

#if _DEBUG
	int result =
#endif // _DEBUG
		::WSAIoctl(sock, SIO_GET_MULTIPLE_EXTENSION_FUNCTION_POINTER
		, fntable_addr, sizeof(GUID)
		, reinterpret_cast<void**>(std::addressof(rioFunctions)), sizeof(rioFunctions)
		, bytes_addr
		, std::addressof(rioContext), ::rioRoutine);

	fntable_id = WSAID_ACCEPTEX;
#if _DEBUG
	result =
#endif // _DEBUG
		::WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER
			, fntable_addr, sizeof(GUID)
			, std::addressof(fnAcceptEx), sizeof(fnAcceptEx)
			, bytes_addr
			, nullptr, nullptr);

	fntable_id = WSAID_TRANSMITFILE;
#if _DEBUG
	result =
#endif // _DEBUG
		::WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER
			, fntable_addr, sizeof(GUID)
			, std::addressof(fnTransmitFile), sizeof(fnTransmitFile)
			, bytes_addr
			, nullptr, nullptr);
}
