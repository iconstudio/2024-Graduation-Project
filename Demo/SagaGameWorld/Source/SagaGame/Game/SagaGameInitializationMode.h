#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SagaGameInitializationMode.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Game Modes")
class SAGAGAME_API ASagaGameInitializationMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASagaGameInitializationMode();
};
