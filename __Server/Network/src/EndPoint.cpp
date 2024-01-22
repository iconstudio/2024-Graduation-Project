module;
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>

module Net.EndPoint;

net::EndPoint::EndPoint(EmptyEndPointType)
noexcept
	: myAddress(IpAddressFamily::Unknown, ""), myPort(-1)
{}

net::EndPoint::EndPoint(const net::IpAddress& ip, const std::uint16_t& port)
noexcept
	: myAddress(ip), myPort(::htons(port))
{}

net::EndPoint::EndPoint(net::IpAddress&& ip, const std::uint16_t& port)
noexcept
	: myAddress(static_cast<IpAddress&&>(ip)), myPort(::htons(port))
{}

const net::EndPoint::EmptyEndPointType net::EndPoint::EmptyEndPoint = {};
