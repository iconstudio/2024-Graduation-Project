#pragma once
#include "CoreMinimal.h"

#include "SagaGameModeBase.h"
#include "SagaNetworkReadyMode.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga|Game Mode")
class SAGAGAME_API ASagaNetworkReadyMode : public ASagaGameModeBase
{
	GENERATED_BODY()

public:
	ASagaNetworkReadyMode();
};
