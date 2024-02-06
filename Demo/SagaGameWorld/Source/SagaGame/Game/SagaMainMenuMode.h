#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SagaMainMenuMode.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Game Modes")
class SAGAGAME_API ASagaMainMenuMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASagaMainMenuMode();
};
