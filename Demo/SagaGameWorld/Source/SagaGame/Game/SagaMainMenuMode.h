#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SagaGameModeBase.h"
#include "SagaMainMenuMode.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Game Modes")
class SAGAGAME_API ASagaMainMenuMode : public ASagaGameMode
{
	GENERATED_BODY()

public:
	ASagaMainMenuMode();
};
