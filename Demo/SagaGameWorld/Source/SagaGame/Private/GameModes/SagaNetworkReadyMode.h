#pragma once
#include "CoreMinimal.h"

#include "SagaUserInterfaceModeBase.h"
#include "SagaNetworkReadyMode.generated.h"

UCLASS(BlueprintType, Category = "CandyLandSaga|Game Mode")
class SAGAGAME_API ASagaNetworkReadyMode : public ASagaUserInterfaceModeBase
{
	GENERATED_BODY()

public:
	ASagaNetworkReadyMode();
};
