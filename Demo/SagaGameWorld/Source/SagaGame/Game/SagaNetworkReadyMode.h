#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SagaGameModeBase.h"
#include "SagaNetworkReadyMode.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Game Modes")
class SAGAGAME_API ASagaNetworkReadyMode : public ASagaGameMode
{
	GENERATED_BODY()

public:
	ASagaNetworkReadyMode();
};
