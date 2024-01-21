module;
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <MSWSock.h>
#include <minwindef.h>
#include <type_traits>
#include <utility>
module Net;

std::optional<net::ErrorCodes>
net::core::Initialize()
noexcept
{
	WSADATA version_data{};

	const int startup = ::WSAStartup(MAKEWORD(2, 2), std::addressof(version_data));
	if (0 != startup)
	{
		return static_cast<net::ErrorCodes>(startup);
	}
	else
	{
		return std::nullopt;
	}
}

void
net::core::Annihilate()
noexcept
{
	::WSACleanup();
}
