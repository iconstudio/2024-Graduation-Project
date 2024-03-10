#pragma once
#include "CoreMinimal.h"

#include "SagaGameModeBase.h"
#include "SagaInGameMode.generated.h"

UCLASS(BlueprintType, Category = "CandyLandSaga|Game Mode")
class SAGAGAME_API ASagaInGameMode : public ASagaGameModeBase
{
	GENERATED_BODY()

public:
	ASagaInGameMode();
};
