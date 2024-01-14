#pragma comment(lib, "Ws2_32.lib")
#include "..\Public\IPAddress.h"
#include "Templates/UniquePtr.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <type_traits>

[[nodiscard]]
constexpr size_t
GetSizeOfFamilyBuffer(const EIpAddressFamily& family)
noexcept
{
	if (EIpAddressFamily::IPv4 == family)
	{
		return 16;
	}
	else if (EIpAddressFamily::IPv6 == family)
	{
		return 48;
	}
	else
	{
		return 0;
	}
}

FIpAddress::FIpAddress(const EIpAddressFamily& family, const FStringView& address)
noexcept
	: addressFamily(family)
	, ipAddress(address)
{}

FIpAddress::FIpAddress(const EIpAddressFamily& family, FStringView&& address)
noexcept
	: addressFamily(family)
	, ipAddress(static_cast<FStringView&&>(address))
{}

FSerializedIpAddress
FIpAddress::Serialize()
const
{
	FSerializedIpAddress result{};

	auto addr = reinterpret_cast<char*>(const_cast<TCHAR*>(*ipAddress));
	::inet_pton((int)addressFamily, addr, std::addressof(result));

	return result;
}

bool
FIpAddress::TrySerialize(FSerializedIpAddress& out)
const noexcept
{
	FSerializedIpAddress result{};

	auto addr = reinterpret_cast<char*>(const_cast<TCHAR*>(*ipAddress));
	if (1 != ::inet_pton((int)addressFamily, addr, std::addressof(result)))
	{
		return false;
	}
	else
	{
		out = std::move(result);
		return true;
	}
}

bool
FIpAddress::TrySerialize(void* out)
const noexcept
{
	auto addr = reinterpret_cast<char*>(const_cast<TCHAR*>(*ipAddress));
	if (1 != ::inet_pton((int)addressFamily, addr, out))
	{
		return false;
	}
	else
	{
		return true;
	}
}
