#include "Network/SagaNetworkUtility.h"
#include "SocketSubsystem.h"

FSocket*
USagaNetworkUtility::CreateTcpSocket()
{
	return ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
}

TSharedRef<FInternetAddr>
USagaNetworkUtility::MakeEndPoint(const FIPv4Address IpAddress, const int32 Port)
{
	auto Result = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	Result->SetIp(IpAddress.Value);
	Result->SetPort(Port);

	return Result;
}

TSharedRef<FInternetAddr>
USagaNetworkUtility::MakeEndPointFrom(const FString String, const int32 Port)
{
	FIPv4Address IpAddress;
	FIPv4Address::Parse(String, IpAddress);

	return MakeEndPoint(IpAddress, Port);
}

FIPv4Address
USagaNetworkUtility::MakeIpAddress(const FString String)
{
	FIPv4Address Result;
	FIPv4Address::Parse(String, Result);

	return Result;
}
