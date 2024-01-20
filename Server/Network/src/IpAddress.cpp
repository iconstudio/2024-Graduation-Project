module;
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>

module Net.IpAddress;
import <string>;

[[nodiscard]]
constexpr size_t GetSizeOfFamilyBuffer(const net::IpAddressFamily& family) noexcept;

net::IpAddress::IpAddress(const IpAddressFamily& family, std::string_view address)
	: addressFamily(family), addressBuffer()
{
	if (family != IpAddressFamily::Unknown)
	{
		addressBuffer = std::make_unique<char[]>(GetSizeOfFamilyBuffer(family));

		std::copy(address.cbegin(), address.cend(), addressBuffer.get());
	}
}

net::IpAddress::IpAddress(const IpAddress& other)
	: addressFamily(other.addressFamily), addressBuffer()
{
	if (other.addressFamily != IpAddressFamily::Unknown)
	{
		const size_t sz = GetSizeOfFamilyBuffer(other.addressFamily);
		addressBuffer = std::make_unique<char[]>(sz);

		std::copy_n(other.addressBuffer.get(), sz, addressBuffer.get());
	}
}

net::IpAddress&
net::IpAddress::operator=(const IpAddress& other)
{
	if (addressBuffer)
	{
		if (other.addressFamily != addressFamily)
		{
			throw std::exception("Cannot assign to the address with a unmatched address family!");
		}

		std::copy_n(other.addressBuffer.get(), GetSizeOfFamilyBuffer(addressFamily), addressBuffer.get());
		return *this;
	}
	else
	{
		return *this = IpAddress(other);
	}
}

net::SerializedIpAddress
net::IpAddress::Serialize()
const noexcept
{
	SerializedIpAddress result{};

	::inet_pton((int)addressFamily, addressBuffer.get(), std::addressof(result));

	return result;
}

bool
net::IpAddress::TrySerialize(net::SerializedIpAddress& out)
const noexcept
{
	SerializedIpAddress result{};

	if (1 != ::inet_pton((int)addressFamily, addressBuffer.get(), std::addressof(result)))
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
net::IpAddress::TrySerialize(void* const& out)
const noexcept
{
	if (1 != ::inet_pton((int)addressFamily, addressBuffer.get(), out))
	{
		return false;
	}
	else
	{
		return true;
	}
}

[[nodiscard]]
constexpr size_t
GetSizeOfFamilyBuffer(const net::IpAddressFamily& family)
noexcept
{
	if (net::IpAddressFamily::IPv4 == family)
	{
		return 16;
	}
	else if (net::IpAddressFamily::IPv6 == family)
	{
		return 48;
	}
	else
	{
		return 0;
	}
}

std::format_context::iterator
std::formatter<net::IpAddress>::format(const net::IpAddress& ip, std::format_context& context)
const noexcept
{
	return std::format_to(context.out(), "IP Address [{} / {}]", std::to_string(ip.GetFamily()), ip.GetAddressString());
}
