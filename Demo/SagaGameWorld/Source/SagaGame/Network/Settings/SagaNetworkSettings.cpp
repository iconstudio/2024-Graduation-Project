#include "SagaNetworkSettings.h"
#include "../SagaNetworkUtility.h"

TSharedRef<FInternetAddr>
USagaNetworkSettings::CreateRemoteEndPoint()
{
	if constexpr (ConnectionCategory == ESagaNetworkConnectionCategory::Local)
	{
		return USagaNetworkUtility::MakeEndPoint(FIPv4Address::InternalLoopback, GetRemotePort());
	}
	else if constexpr (ConnectionCategory == ESagaNetworkConnectionCategory::Host)
	{
		return USagaNetworkUtility::MakeEndPoint(FIPv4Address::Any, GetRemotePort());
	}
	else if constexpr (ConnectionCategory == ESagaNetworkConnectionCategory::Remote)
	{
		return USagaNetworkUtility::MakeEndPointFrom(RemoteAddress, GetRemotePort());
	}
	else
	{
		throw "error!";
	}
}
