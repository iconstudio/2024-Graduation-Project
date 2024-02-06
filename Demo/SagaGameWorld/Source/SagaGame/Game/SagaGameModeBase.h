#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SagaGameModeBase.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Game Modes")
class SAGAGAME_API ASagaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASagaGameMode();
};
