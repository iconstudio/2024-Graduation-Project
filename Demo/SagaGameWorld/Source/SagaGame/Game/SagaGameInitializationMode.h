#pragma once
#include "CoreMinimal.h"

#include "SagaGameModeBase.h"
#include "SagaGameInitializationMode.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga|Game Mode")
class SAGAGAME_API ASagaGameInitializationMode : public ASagaGameModeBase
{
	GENERATED_BODY()

public:
	ASagaGameInitializationMode();
};
