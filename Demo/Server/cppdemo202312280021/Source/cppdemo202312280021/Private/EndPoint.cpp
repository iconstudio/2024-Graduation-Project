#pragma comment(lib, "Ws2_32.lib")
#include "EndPoint.h"
#include <WinSock2.h>

FEndpoint::FEndpoint(const FIpAddress& ip, const uint16& port)
noexcept
	: myAddress(ip), myPort(::htons(port))
{}

FEndpoint::FEndpoint(FIpAddress&& ip, const uint16& port)
noexcept
	: myAddress(static_cast<FIpAddress&&>(ip)), myPort(::htons(port))
{}
