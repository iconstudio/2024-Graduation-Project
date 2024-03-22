#pragma once
#include "CoreMinimal.h"
#include "IpAddressFamily.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EIpAddressFamily
{
	Unknown,
	IPv4 = 2,
	IPv6 = 23
};

namespace net
{
	using IpAddressFamily = ::EIpAddressFamily;
}
