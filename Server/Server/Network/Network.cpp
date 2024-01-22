module;
#include <WinSock2.h>

module Iconer.Net;
import Iconer.Net.ErrorCode;
import <utility>;

std::optional<iconer::net::ErrorCode>
iconer::net::Startup() noexcept
{
	::WSADATA version_data{};

	const int startup = ::WSAStartup(MAKEWORD(2, 2), std::addressof(version_data));
	if (0 != startup)
	{
		return AcquireNetworkError();
	}
	else
	{
		return std::nullopt;
	}
}

std::optional<iconer::net::ErrorCode> iconer::net::Cleanup() noexcept
{
	if (0 != ::WSACleanup())
	{
		return AcquireNetworkError();
	}
	else
	{
		return std::nullopt;
	}
}
