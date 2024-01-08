#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#include "NativeSocket.h"
#include "IconerBlueprinter.h"
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <ws2ipdef.h>
#include <MSWSock.h>
#include <coroutine>

[[nodiscard]]
::SOCKADDR_STORAGE SerializeEndpoint(const FEndpoint& endpoint) noexcept;
[[nodiscard]]
::SOCKADDR_STORAGE SerializeEndpoint(FEndpoint&& endpoint) noexcept;

FNativeSocket::SocketResult
FNativeSocket::Bind(const FIpAddress& address, const uint16& port)
const noexcept
{
	return this->Bind(FEndpoint(address, port));
}

FNativeSocket::SocketResult
FNativeSocket::Bind(FIpAddress&& address, const uint16& port)
const noexcept
{
	return this->Bind(FEndpoint(std::move(address), port));
}

FNativeSocket::SocketResult
FNativeSocket::Bind(const FEndpoint& endpoint)
const noexcept
{
	SOCKADDR_STORAGE sockaddr = SerializeEndpoint(endpoint);
	SOCKADDR_STORAGE* ptr = std::addressof(sockaddr);

	if (0 != ::bind(myHandle, reinterpret_cast<const ::SOCKADDR*>(ptr), sizeof(sockaddr)))
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}

	return static_cast<unsigned int>(sizeof(sockaddr));
}

FNativeSocket::SocketResult
FNativeSocket::Bind(FEndpoint&& endpoint)
const noexcept
{
	SOCKADDR_STORAGE sockaddr = SerializeEndpoint(std::move(endpoint));
	SOCKADDR_STORAGE* ptr = std::addressof(sockaddr);

	if (0 != ::bind(myHandle, reinterpret_cast<const ::SOCKADDR*>(ptr), sizeof(sockaddr)))
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}

	return static_cast<unsigned int>(sizeof(sockaddr));
}

FNativeSocket::SocketResult
FNativeSocket::BindHost(const uint16& port)
const noexcept
{
	switch (myFamily)
	{
		case EIpAddressFamily::IPv4:
		{
			::SOCKADDR_IN sockaddr
			{
				.sin_family = AF_INET,
				.sin_port = ::htons(port),
				.sin_zero{}
			};
			sockaddr.sin_addr = ::in4addr_any;

			if (0 == ::bind(myHandle, reinterpret_cast<const ::SOCKADDR*>(std::addressof(sockaddr)), sizeof(sockaddr)))
			{
				return 1U;
			}
		}
		break;

		case EIpAddressFamily::IPv6:
		{
			::SOCKADDR_IN6 sockaddr
			{
				.sin6_family = AF_INET,
				.sin6_port = ::htons(port),
				.sin6_flowinfo = 0,
				.sin6_addr{}
			};
			sockaddr.sin6_addr = ::in6addr_any;

			if (0 == ::bind(myHandle, reinterpret_cast<const ::SOCKADDR*>(std::addressof(sockaddr)), sizeof(sockaddr)))
			{
				return 1U;
			}
		}
		break;

		default:
		{}
		break;
	}

	return Unexpected(UNetworkUtility::AcquireNetworkError());
}

FNativeSocket::SocketResult
FNativeSocket::Connect(const FIpAddress& address, const uint16& port)
const noexcept
{
	return this->Connect(FEndpoint(address, port));
}

FNativeSocket::SocketResult
FNativeSocket::Connect(FIpAddress&& address, const uint16& port)
const noexcept
{
	return this->Connect(FEndpoint(std::move(address), port));
}

FNativeSocket::SocketResult
FNativeSocket::Connect(const FEndpoint& endpoint)
const noexcept
{
	::SOCKADDR_STORAGE sockaddr = SerializeEndpoint(endpoint);
	::SOCKADDR_STORAGE* ptr = std::addressof(sockaddr);

	if (0 != ::WSAConnect(myHandle
		, reinterpret_cast<const ::SOCKADDR*>(ptr), sizeof(sockaddr)
		, nullptr, nullptr
		, nullptr, nullptr))
	{
		auto error_code = UNetworkUtility::AcquireNetworkError();
		if (error_code == EErrorCode::NonBlockedOperation)
		{
			return 0U;
		}
		else
		{
			return Unexpected(error_code);
		}
	}

	return 1U;
}

FNativeSocket::SocketResult
FNativeSocket::Connect(FEndpoint&& endpoint)
const noexcept
{
	SOCKADDR_STORAGE sockaddr = SerializeEndpoint(std::move(endpoint));
	SOCKADDR_STORAGE* ptr = std::addressof(sockaddr);

	if (0 != ::WSAConnect(myHandle
		, reinterpret_cast<const ::SOCKADDR*>(ptr), sizeof(sockaddr)
		, nullptr, nullptr
		, nullptr, nullptr))
	{
		auto error_code = UNetworkUtility::AcquireNetworkError();
		if (error_code == EErrorCode::NonBlockedOperation)
		{
			return 0U;
		}
		else
		{
			return Unexpected(error_code);
		}
	}

	return 1U;
}

FSocketTask
FNativeSocket::ConnectAsync(const FEndpoint& endpoint)
const noexcept
{
	co_return this->Connect(endpoint);
}

FSocketTask
FNativeSocket::ConnectAsync(FEndpoint&& endpoint)
const noexcept
{
	co_return this->Connect(std::move(endpoint));
}

FSocketTask
FNativeSocket::ConnectAsync(const FIpAddress& address, const uint16& port)
const noexcept
{
	co_return this->Connect(FEndpoint(address, port));
}

FSocketTask
FNativeSocket::ConnectAsync(FIpAddress&& address, const uint16& port)
const noexcept
{
	co_return this->Connect(FEndpoint(std::move(address), port));
}

FNativeSocket::FactoryResult
FNativeSocket::Accept()
const noexcept
{
	::SOCKADDR_STORAGE address{};
	int address_blen = sizeof(::SOCKADDR_STORAGE);

	::SOCKADDR* rawaddr = reinterpret_cast<::SOCKADDR*>(std::addressof(address));

	uintptr_t client = ::accept(myHandle, rawaddr, std::addressof(address_blen));
	if (INVALID_SOCKET == client)
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}

	EIpAddressFamily family;
	switch (address.ss_family)
	{
		case AF_INET:
		{
			family = EIpAddressFamily::IPv4;
		}
		break;
		case AF_INET6:
		{
			family = EIpAddressFamily::IPv6;
		}
		break;
		default:
		{
			family = EIpAddressFamily::Unknown;
		}
		break;
	}
	return FNativeSocket{ client, myProtocol, family };
}

FNativeSocket::FactoryResult
FNativeSocket::Accept(FEndpoint& endpoint)
const noexcept
{
	::SOCKADDR_STORAGE address{};
	int address_blen = sizeof(SOCKADDR_STORAGE);

	SOCKADDR* rawaddr = reinterpret_cast<::SOCKADDR*>(std::addressof(address));

	uintptr_t client = ::WSAAccept(myHandle, rawaddr, std::addressof(address_blen), nullptr, 0);
	if (INVALID_SOCKET == client)
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}

	FString temp{};
	FIpAddress ip{ EIpAddressFamily::Unknown, temp };
	EIpAddressFamily family;
	uint16 port;

	switch (address.ss_family)
	{
		case AF_INET:
		{
			family = EIpAddressFamily::IPv4;

			::SOCKADDR_IN* addr = reinterpret_cast<::SOCKADDR_IN*>(std::addressof(address));
			port = ::ntohs(addr->sin_port);

			try
			{
				char ip_buffer[16]{};

				const char* ip_address = ::inet_ntop(AF_INET, std::addressof(addr->sin_addr), ip_buffer, sizeof(ip_buffer));

				auto str = FString{ ip_buffer };
				ip = FIpAddress{ EIpAddressFamily::IPv4, str };
			}
			catch (...)
			{
				return Unexpected(UNetworkUtility::AcquireNetworkError());
			}
		}
		break;

		case AF_INET6:
		{
			family = EIpAddressFamily::IPv6;

			::SOCKADDR_IN6* addr = reinterpret_cast<::SOCKADDR_IN6*>(std::addressof(address));
			port = ::ntohs(addr->sin6_port);

			wchar_t ip_wbuffer[32]{};
			::DWORD wblen = sizeof(ip_wbuffer);

			if (SOCKET_ERROR == WSAAddressToString(rawaddr, sizeof(address), nullptr, ip_wbuffer, std::addressof(wblen)))
			{
				return Unexpected(UNetworkUtility::AcquireNetworkError());
			}

			try
			{
				size_t mb_result = 0;
				char ip_buffer[32]{};

				::mbstowcs_s(std::addressof(mb_result), ip_wbuffer, ip_buffer, ::strlen(ip_buffer) + 1);

				auto str = FString{ ip_buffer };
				ip = FIpAddress{ EIpAddressFamily::IPv6, str };
			}
			catch (...)
			{
				return Unexpected(UNetworkUtility::AcquireNetworkError());
			}
		}
		break;

		default:
		{
			family = EIpAddressFamily::Unknown;
		}
		break;
	}
	endpoint = FEndpoint{ std::move(ip), port };

	return FNativeSocket{ client, myProtocol, family };
}

[[nodiscard]]
::SOCKADDR_STORAGE
SerializeEndpoint(const FEndpoint& endpoint)
noexcept
{
	const auto& ip = endpoint.GetIpAddress();
	const auto& port = endpoint.GetPort();

	SOCKADDR_STORAGE result{};
	SOCKADDR_STORAGE* sockaddr_ptr = std::addressof(result);

	switch (endpoint.GetAddressFamily())
	{
		case EIpAddressFamily::IPv4:
		{
			IN_ADDR sk_addr{};
			if (not ip.TrySerialize(std::addressof(sk_addr.s_addr)))
			{
				break;
			}

			SOCKADDR_IN ipv4_addr
			{
				.sin_family = (uint16)EIpAddressFamily::IPv4,
				.sin_port = port,
				.sin_addr = std::move(sk_addr),
			};

			result = *reinterpret_cast<const ::SOCKADDR_STORAGE*>(std::addressof(ipv4_addr));
		}
		break;

		case EIpAddressFamily::IPv6:
		{
			IN6_ADDR sk_addr{};
			if (not ip.TrySerialize(std::addressof(sk_addr.s6_addr)))
			{
				break;
			}

			SOCKADDR_IN6 ipv6_addr
			{
				.sin6_family = (uint16)EIpAddressFamily::IPv6,
				.sin6_port = port,
				.sin6_flowinfo = 0,
				.sin6_addr = std::move(sk_addr),
				.sin6_scope_id = 0,
			};

			result = *reinterpret_cast<const ::SOCKADDR_STORAGE*>(std::addressof(ipv6_addr));
		}
		break;

		case EIpAddressFamily::Unknown:
		{}
		break;
	}

	return result;
}

[[nodiscard]]
::SOCKADDR_STORAGE
SerializeEndpoint(FEndpoint&& endpoint)
noexcept
{
	::SOCKADDR_STORAGE result{};
	::SOCKADDR_STORAGE* sockaddr_ptr = std::addressof(result);

	switch (std::move(endpoint).GetAddressFamily())
	{
		case EIpAddressFamily::IPv4:
		{
			::IN_ADDR sk_addr{};
			if (not std::move(endpoint).GetIpAddress().TrySerialize(std::addressof(sk_addr.s_addr)))
			{
				break;
			}

			SOCKADDR_IN ipv4_addr
			{
				.sin_family = (uint16)EIpAddressFamily::IPv4,
				.sin_port = std::move(endpoint).GetPort(),
				.sin_addr = std::move(sk_addr),
			};

			result = *reinterpret_cast<const ::SOCKADDR_STORAGE*>(std::addressof(ipv4_addr));
		}
		break;

		case EIpAddressFamily::IPv6:
		{
			IN6_ADDR sk_addr{};
			if (not std::move(endpoint).GetIpAddress().TrySerialize(std::addressof(sk_addr.s6_addr)))
			{
				break;
			}

			::SOCKADDR_IN6 ipv6_addr
			{
				.sin6_family = (uint16)EIpAddressFamily::IPv6,
				.sin6_port = std::move(endpoint).GetPort(),
				.sin6_flowinfo = 0,
				.sin6_addr = std::move(sk_addr),
				.sin6_scope_id = 0,
			};

			result = *reinterpret_cast<const SOCKADDR_STORAGE*>(std::addressof(ipv6_addr));
		}
		break;

		case EIpAddressFamily::Unknown:
		{}
		break;
	}

	return result;
}
