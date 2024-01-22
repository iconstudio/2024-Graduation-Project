module;
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <ws2ipdef.h>
#include <MSWSock.h>

module Net.Socket;
import <coroutine>;

::SOCKADDR_STORAGE SerializeEndpoint(const net::EndPoint& endpoint) noexcept;
::SOCKADDR_STORAGE SerializeEndpoint(net::EndPoint&& endpoint) noexcept;

net::SocketResult
net::Socket::Bind(const net::IpAddress& address, const std::uint16_t& port)
const noexcept
{
	return this->Bind(EndPoint(address, port));
}

net::SocketResult
net::Socket::Bind(net::IpAddress&& address, const std::uint16_t& port)
const noexcept
{
	return this->Bind(EndPoint(std::move(address), port));
}

net::SocketResult
net::Socket::Bind(const net::EndPoint& endpoint)
const noexcept
{
	SOCKADDR_STORAGE sockaddr = SerializeEndpoint(endpoint);
	SOCKADDR_STORAGE* ptr = std::addressof(sockaddr);

	if (0 != ::bind(myHandle, reinterpret_cast<const SOCKADDR*>(ptr), sizeof(sockaddr)))
	{
		return unexpected(AcquireNetworkError());
	}

	return static_cast<unsigned int>(sizeof(sockaddr));
}

net::SocketResult
net::Socket::Bind(net::EndPoint&& endpoint)
const noexcept
{
	SOCKADDR_STORAGE sockaddr = SerializeEndpoint(std::move(endpoint));
	SOCKADDR_STORAGE* ptr = std::addressof(sockaddr);

	if (0 != ::bind(myHandle, reinterpret_cast<const SOCKADDR*>(ptr), sizeof(sockaddr)))
	{
		return unexpected(AcquireNetworkError());
	}

	return static_cast<unsigned int>(sizeof(sockaddr));
}

net::SocketResult
net::Socket::BindHost(const std::uint16_t& port)
const noexcept
{
	switch (myFamily)
	{
		case IpAddressFamily::IPv4:
		{
			::SOCKADDR_IN sockaddr
			{
				.sin_family = AF_INET,
				.sin_port = ::htons(port),
				.sin_zero{}
			};
			sockaddr.sin_addr = ::in4addr_any;

			if (0 == ::bind(myHandle, reinterpret_cast<const SOCKADDR*>(std::addressof(sockaddr)), sizeof(sockaddr)))
			{
				return 1;
			}
		}
		break;

		case IpAddressFamily::IPv6:
		{
			::SOCKADDR_IN6 sockaddr
			{
				.sin6_family = AF_INET,
				.sin6_port = ::htons(port),
				.sin6_flowinfo = 0,
				.sin6_addr{}
			};
			sockaddr.sin6_addr = ::in6addr_any;

			if (0 == ::bind(myHandle, reinterpret_cast<const SOCKADDR*>(std::addressof(sockaddr)), sizeof(sockaddr)))
			{
				return 1;
			}
		}
		break;
	}

	return unexpected(AcquireNetworkError());
}

net::SocketResult
net::Socket::Connect(const net::IpAddress& address, const std::uint16_t& port)
const noexcept
{
	return this->Connect(EndPoint(address, port));
}

net::SocketResult
net::Socket::Connect(net::IpAddress&& address, const std::uint16_t& port)
const noexcept
{
	return this->Connect(EndPoint(std::move(address), port));
}

net::SocketResult
net::Socket::Connect(const net::EndPoint& endpoint)
const noexcept
{
	SOCKADDR_STORAGE sockaddr = SerializeEndpoint(endpoint);
	SOCKADDR_STORAGE* ptr = std::addressof(sockaddr);

	if (0 != ::WSAConnect(myHandle
		, reinterpret_cast<const SOCKADDR*>(ptr), sizeof(sockaddr)
		, nullptr, nullptr
		, nullptr, nullptr))
	{
		auto error_code = AcquireNetworkError();
		if (error_code == ErrorCodes::NonBlockedOperation)
		{
			return 0;
		}
		else
		{
			return unexpected(error_code);
		}
	}

	return 1;
}

net::SocketResult
net::Socket::Connect(net::EndPoint&& endpoint)
const noexcept
{
	SOCKADDR_STORAGE sockaddr = SerializeEndpoint(std::move(endpoint));
	SOCKADDR_STORAGE* ptr = std::addressof(sockaddr);

	if (0 != ::WSAConnect(myHandle
		, reinterpret_cast<const SOCKADDR*>(ptr), sizeof(sockaddr)
		, nullptr, nullptr
		, nullptr, nullptr))
	{
		auto error_code = AcquireNetworkError();
		if (error_code == ErrorCodes::NonBlockedOperation)
		{
			return 0;
		}
		else
		{
			return unexpected(error_code);
		}
	}

	return 1;
}

net::Task<net::SocketResult>
net::Socket::ConnectAsync(const net::EndPoint& endpoint)
const noexcept
{
	co_return this->Connect(endpoint);
}

net::Task<net::SocketResult>
net::Socket::ConnectAsync(net::EndPoint&& endpoint)
const noexcept
{
	co_return this->Connect(std::move(endpoint));
}

net::Task<net::SocketResult>
net::Socket::ConnectAsync(const net::IpAddress& address, const std::uint16_t& port)
const noexcept
{
	co_return this->Connect(EndPoint(address, port));
}

net::Task<net::SocketResult>
net::Socket::ConnectAsync(net::IpAddress&& address, const std::uint16_t& port)
const noexcept
{
	co_return this->Connect(EndPoint(std::move(address), port));
}

net::Socket::SocketResult
net::Socket::Accept()
const noexcept
{
	::SOCKADDR_STORAGE address{};
	int address_blen = sizeof(SOCKADDR_STORAGE);

	SOCKADDR* rawaddr = reinterpret_cast<::SOCKADDR*>(std::addressof(address));

	NativeSocket client = ::accept(myHandle, rawaddr, std::addressof(address_blen));
	if (INVALID_SOCKET == client)
	{
		return std::unexpected(AcquireNetworkError());
	}

	IpAddressFamily family;
	switch (address.ss_family)
	{
		case AF_INET:
		{
			family = IpAddressFamily::IPv4;
		}
		break;
		case AF_INET6:
		{
			family = IpAddressFamily::IPv6;
		}
		break;
		default:
		{
			family = IpAddressFamily::Unknown;
		}
		break;
	}
	return Socket{ client, myProtocol, family };
}

net::Socket::SocketResult
net::Socket::Accept(EndPoint& endpoint)
const noexcept
{
	::SOCKADDR_STORAGE address{};
	int address_blen = sizeof(SOCKADDR_STORAGE);

	SOCKADDR* rawaddr = reinterpret_cast<::SOCKADDR*>(std::addressof(address));

	NativeSocket client = ::WSAAccept(myHandle, rawaddr, std::addressof(address_blen), nullptr, 0);
	if (INVALID_SOCKET == client)
	{
		return std::unexpected(AcquireNetworkError());
	}

	IpAddress ip{ IpAddressFamily::Unknown, "" };
	IpAddressFamily family;
	std::uint16_t port;

	switch (address.ss_family)
	{
		case AF_INET:
		{
			family = IpAddressFamily::IPv4;

			::SOCKADDR_IN* addr = reinterpret_cast<::SOCKADDR_IN*>(std::addressof(address));
			port = ::ntohs(addr->sin_port);

			try
			{
				char ip_buffer[16]{};

				const char* ip_address = ::inet_ntop(AF_INET, std::addressof(addr->sin_addr), ip_buffer, sizeof(ip_buffer));
				ip = IpAddress{ IpAddressFamily::IPv4, std::move(ip_address) };
			}
			catch (...)
			{
				return std::unexpected(AcquireNetworkError());
			}
		}
		break;

		case AF_INET6:
		{
			family = IpAddressFamily::IPv6;

			::SOCKADDR_IN6* addr = reinterpret_cast<::SOCKADDR_IN6*>(std::addressof(address));
			port = ::ntohs(addr->sin6_port);

			wchar_t ip_wbuffer[32]{};
			::DWORD wblen = sizeof(ip_wbuffer);

			if (SOCKET_ERROR == WSAAddressToString(rawaddr, sizeof(address), nullptr, ip_wbuffer, std::addressof(wblen)))
			{
				return std::unexpected(AcquireNetworkError());
			}

			try
			{
				size_t mb_result = 0;
				char ip_buffer[32]{};
				::mbstowcs_s(std::addressof(mb_result), ip_wbuffer, ip_buffer, ::strlen(ip_buffer) + 1);

				ip = IpAddress{ IpAddressFamily::IPv6, std::move(ip_buffer) };
			}
			catch (...)
			{
				return std::unexpected(AcquireNetworkError());
			}
		}
		break;

		default:
		{
			family = IpAddressFamily::Unknown;
		}
		break;
	}
	endpoint = EndPoint{ std::move(ip), port };

	return Socket{ client, myProtocol, family };
}

[[nodiscard]]
::SOCKADDR_STORAGE
SerializeEndpoint(const net::EndPoint& endpoint)
noexcept
{
	const auto& ip = endpoint.IpAddress();
	const auto& port = endpoint.Port();

	SOCKADDR_STORAGE result{};
	SOCKADDR_STORAGE* sockaddr_ptr = std::addressof(result);

	switch (endpoint.AddressFamily())
	{
		case net::IpAddressFamily::IPv4:
		{
			IN_ADDR sk_addr{};
			if (not ip.TrySerialize(std::addressof(sk_addr.s_addr)))
			{
				break;
			}

			SOCKADDR_IN ipv4_addr
			{
				.sin_family = (std::uint16_t)net::IpAddressFamily::IPv4,
				.sin_port = port,
				.sin_addr = std::move(sk_addr),
			};

			result = *reinterpret_cast<const SOCKADDR_STORAGE*>(std::addressof(ipv4_addr));
		}
		break;

		case net::IpAddressFamily::IPv6:
		{
			IN6_ADDR sk_addr{};
			if (not ip.TrySerialize(std::addressof(sk_addr.s6_addr)))
			{
				break;
			}

			SOCKADDR_IN6 ipv6_addr
			{
				.sin6_family = (std::uint16_t)net::IpAddressFamily::IPv6,
				.sin6_port = port,
				.sin6_flowinfo = 0,
				.sin6_addr = std::move(sk_addr),
				.sin6_scope_id = 0,
			};

			result = *reinterpret_cast<const SOCKADDR_STORAGE*>(std::addressof(ipv6_addr));
		}
		break;

		case net::IpAddressFamily::Unknown:
		{}
		break;
	}

	return result;
}

[[nodiscard]]
::SOCKADDR_STORAGE
SerializeEndpoint(net::EndPoint&& endpoint)
noexcept
{
	SOCKADDR_STORAGE result{};
	SOCKADDR_STORAGE* sockaddr_ptr = std::addressof(result);

	switch (std::move(endpoint).AddressFamily())
	{
		case net::IpAddressFamily::IPv4:
		{
			IN_ADDR sk_addr{};
			if (not std::move(endpoint).IpAddress().TrySerialize(std::addressof(sk_addr.s_addr)))
			{
				break;
			}

			SOCKADDR_IN ipv4_addr
			{
				.sin_family = (std::uint16_t)net::IpAddressFamily::IPv4,
				.sin_port = std::move(endpoint).Port(),
				.sin_addr = std::move(sk_addr),
			};

			result = *reinterpret_cast<const SOCKADDR_STORAGE*>(std::addressof(ipv4_addr));
		}
		break;

		case net::IpAddressFamily::IPv6:
		{
			IN6_ADDR sk_addr{};
			if (not std::move(endpoint).IpAddress().TrySerialize(std::addressof(sk_addr.s6_addr)))
			{
				break;
			}

			SOCKADDR_IN6 ipv6_addr
			{
				.sin6_family = (std::uint16_t)net::IpAddressFamily::IPv6,
				.sin6_port = std::move(endpoint).Port(),
				.sin6_flowinfo = 0,
				.sin6_addr = std::move(sk_addr),
				.sin6_scope_id = 0,
			};

			result = *reinterpret_cast<const SOCKADDR_STORAGE*>(std::addressof(ipv6_addr));
		}
		break;

		case net::IpAddressFamily::Unknown:
		{}
		break;
	}

	return result;
}
