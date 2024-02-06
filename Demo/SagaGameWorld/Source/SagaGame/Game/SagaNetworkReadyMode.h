#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SagaNetworkReadyMode.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Game Modes")
class SAGAGAME_API ASagaNetworkReadyMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASagaNetworkReadyMode();
};
