#pragma once
#include "CoreMinimal.h"
#include "IoSynchronousType.generated.h"

UENUM(BlueprintType, Blueprintable, meta = (ScriptName = "Io Synchronous Category"))
enum class [[nodiscard]] EIoSynchronousType
{
	Synchronous = 0b000000000U,
	Asynchronous = 0b000000001U,
	Registered = 0b100000000U,
};

namespace net
{
	using IoSynchronousType = ::EIoSynchronousType;
}
