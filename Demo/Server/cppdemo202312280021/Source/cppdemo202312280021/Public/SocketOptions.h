#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class [[nodiscard]] ESocketOptions
{
	SO_UNKNOWN = 0x0000 UMETA(DisplayName = "Unknown"),
	SO_DEBUG = 0x0001 UMETA(DisplayName = "Debug"),
	SO_REUSEADDR = 0x0004 UMETA(DisplayName = "Recyclable"),
	SO_DONTROUTE = 0x0010 UMETA(DisplayName = "Don't Route"),
	SO_BROADCAST = 0x0020 UMETA(DisplayName = "Broadcast"),
	SO_USELOOPBACK = 0x0040 UMETA(DisplayName = "Use Loopback"),
	SO_LINGER = 0x0080 UMETA(DisplayName = "Linger"),
	TCP_NODELAY = 0x0001 UMETA(DisplayName = "No Delay"),
	SO_DONTLINGER = static_cast<int32>(~0x0080) UMETA(DisplayName = "Don't Linger"),
	SO_KEEPALIVE = 0x0008 UMETA(DisplayName = "Keep Alive"),
	SO_UPDATE_ACCEPT_CONTEXT = 0x700B UMETA(DisplayName = "Update"), // MSWSock.h
};

namespace net
{
	using SocketOptions = ::ESocketOptions;
}
