module;
#include <WinSock2.h>

module Iconer.Net;
import Iconer.Net.ErrorCode;
import <utility>;

bool
iconer::net::Startup()
noexcept
{
	::WSADATA version_data{};

	const int startup = ::WSAStartup(MAKEWORD(2, 2), std::addressof(version_data));
	if (0 != startup)
	{
		//return AcquireNetworkError();
		return false;
	}
	else
	{
		//return std::nullopt;
		return true;
	}
}

bool
iconer::net::Cleanup()
noexcept
{
	if (0 != ::WSACleanup())
	{
		//return AcquireNetworkError();
		return false;
	}
	else
	{
		//return std::nullopt;
		return true;
	}
}
