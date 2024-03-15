#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "SagaGameModeBase.generated.h"

UCLASS(BlueprintType, Category = "CandyLandSaga|Game Mode")
class SAGAFRAMEWORK_API ASagaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASagaGameModeBase();
};
