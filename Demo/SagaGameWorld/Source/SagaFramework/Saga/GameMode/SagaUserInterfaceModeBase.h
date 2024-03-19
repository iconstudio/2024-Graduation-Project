#pragma once
#pragma once
#include "Saga/GameMode/SagaGameModeBase.h"

#include "SagaUserInterfaceModeBase.generated.h"

UCLASS(BlueprintType, Abstract, Category = "CandyLandSaga|Game Mode")
class ASagaUserInterfaceModeBase : public ASagaGameModeBase
{
	GENERATED_BODY()

public:
	ASagaUserInterfaceModeBase();
};
