#pragma comment(lib, "Ws2_32.lib")
#include "EndPoint.h"
#include <WinSock2.h>
#include <utility>

FEndpoint::FEndpoint(const FIpAddress& ip, const uint16& port)
noexcept
	: myAddress(ip), myPort(::htons(port))
{}

FEndpoint::FEndpoint(FIpAddress&& ip, const uint16& port)
noexcept
	: myAddress(static_cast<FIpAddress&&>(ip)), myPort(::htons(port))
{}

FEndpoint
UFEndpointFactory::CreateEndPoint(FString address, EIpAddressFamily family, int32 port)
noexcept
{
	return FEndpoint{ FIpAddress{ family, std::move(address) }, static_cast<uint16>(port) };
}

FEndpoint
UFEndpointFactory::CreateEndPointBy(const FIpAddress& ip_address, int32 port)
noexcept
{
	return FEndpoint{ ip_address, static_cast<uint16>(port) };
}
