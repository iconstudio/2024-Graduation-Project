#pragma once
#include "CoreMinimal.h"
#include "SagaNetworkConnectionCategory.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class [[nodiscard]] ESagaNetworkConnectionCategory
{
	Unknown = 0
	, Local UMETA(DisplayName="Loopback")
	, Host UMETA(DisplayName="Any Address")
	, Remote UMETA(DisplayName="Remote Address")
};
