module;
#include <WinSock2.h>
#include <ws2ipdef.h>

module Iconer.Net.Socket;
import Iconer.Net.IpAddress;
import Iconer.Net.EndPoint;
import <type_traits>;
import <mutex>;

using namespace iconer;

net::Socket::SocketResult
net::Socket::Bind(const net::IpAddress& address, std::uint16_t port)
const noexcept
{
	return this->Bind(EndPoint{ address, port });
}

net::Socket::SocketResult
net::Socket::Bind(net::IpAddress&& address, std::uint16_t port)
const noexcept
{
	return this->Bind(EndPoint{ std::move(address), port });
}

iconer::net::Socket::SocketResult
iconer::net::Socket::BindAny(std::uint16_t port)
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
				.sin_addr = ::in4addr_any,
				.sin_zero{}
			};

			if (0 == ::bind(myHandle, reinterpret_cast<const SOCKADDR*>(std::addressof(sockaddr)), sizeof(sockaddr)))
			{
				return std::nullopt;
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
				.sin6_addr = ::in6addr_any
			};

			if (0 == ::bind(myHandle, reinterpret_cast<const ::SOCKADDR*>(std::addressof(sockaddr)), sizeof(sockaddr)))
			{
				return std::nullopt;
			}
		}
		break;
	}

	return AcquireNetworkError();
}

net::Socket::SocketResult
net::Socket::BindHost(std::uint16_t port)
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
				.sin_addr = ::in4addr_loopback,
				.sin_zero{}
			};

			if (0 == ::bind(myHandle, reinterpret_cast<const SOCKADDR*>(std::addressof(sockaddr)), sizeof(sockaddr)))
			{
				return std::nullopt;
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
				.sin6_addr = ::in6addr_loopback
			};

			if (0 == ::bind(myHandle, reinterpret_cast<const ::SOCKADDR*>(std::addressof(sockaddr)), sizeof(sockaddr)))
			{
				return std::nullopt;
			}
		}
		break;
	}

	return AcquireNetworkError();
}

iconer::net::Socket::SocketResult
iconer::net::Socket::ConnectToAny(std::uint16_t port)
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
				.sin_addr = ::in4addr_any,
				.sin_zero{}
			};

			if (0 != ::WSAConnect(myHandle
				, reinterpret_cast<const SOCKADDR*>(std::addressof(sockaddr)), sizeof(sockaddr)
				, nullptr, nullptr
				, nullptr, nullptr))
			{
				if (auto error_code = AcquireNetworkError(); error_code != ErrorCode::NonBlockedOperation)
				{
					return error_code;
				}
				else
				{
					return std::nullopt;
				}
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
				.sin6_addr = ::in6addr_any
			};

			if (0 != ::WSAConnect(myHandle
				, reinterpret_cast<const SOCKADDR*>(std::addressof(sockaddr)), sizeof(sockaddr)
				, nullptr, nullptr
				, nullptr, nullptr))
			{
				if (auto error_code = AcquireNetworkError(); error_code != ErrorCode::NonBlockedOperation)
				{
					return error_code;
				}
				else
				{
					return std::nullopt;
				}
			}
		}
		break;
	}

	return std::nullopt;
}

iconer::net::Socket::SocketResult
iconer::net::Socket::ConnectToHost(std::uint16_t port)
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
				.sin_addr = ::in4addr_loopback,
				.sin_zero{}
			};

			if (0 != ::WSAConnect(myHandle
				, reinterpret_cast<const SOCKADDR*>(std::addressof(sockaddr)), sizeof(sockaddr)
				, nullptr, nullptr
				, nullptr, nullptr))
			{
				if (auto error_code = AcquireNetworkError(); error_code != ErrorCode::NonBlockedOperation)
				{
					return error_code;
				}
				else
				{
					return std::nullopt;
				}
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
				.sin6_addr = ::in6addr_loopback
			};

			if (0 != ::WSAConnect(myHandle
				, reinterpret_cast<const SOCKADDR*>(std::addressof(sockaddr)), sizeof(sockaddr)
				, nullptr, nullptr
				, nullptr, nullptr))
			{
				if (auto error_code = AcquireNetworkError(); error_code != ErrorCode::NonBlockedOperation)
				{
					return error_code;
				}
				else
				{
					return std::nullopt;
				}
			}
		}
		break;
	}

	return std::nullopt;
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
