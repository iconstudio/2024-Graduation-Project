#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <type_traits>
#include "Templates/UniquePtr.h"
#include "InternetProtocolAddress.h"

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

FIpAddress::FIpAddress(const EIpAddressFamily& family, const FString& address)
noexcept
	: addressFamily(family)
	, ipAddress(address)
{}

FIpAddress::FIpAddress(const EIpAddressFamily& family, FString&& address)
noexcept
	: addressFamily(family)
	, ipAddress(static_cast<FString&&>(address))
{}

FSerializedIpAddress
FIpAddress::Serialize()
const
{
	FSerializedIpAddress result{};

	TUniquePtr<FSerializedIpAddress> address_buffer = MakeUnique<FSerializedIpAddress>();

	auto ptr = reinterpret_cast<char*>(address_buffer.Get());
	::inet_pton((int)addressFamily, ptr, std::addressof(result));

	return result;
}

bool
FIpAddress::TrySerialize(FSerializedIpAddress& out)
const noexcept
{
	FSerializedIpAddress result{};

	TUniquePtr<FSerializedIpAddress> address_buffer = MakeUnique<FSerializedIpAddress>();

	auto ptr = reinterpret_cast<char*>(address_buffer.Get());
	if (1 != ::inet_pton((int)addressFamily, ptr, std::addressof(result)))
	{
		return false;
	}
	else
	{
		out = std::move(result);
		return true;
	}
}
