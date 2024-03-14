#pragma once
#include "CoreMinimal.h"

#include "SagaUserInterfaceModeBase.h"
#include "SagaGameInitializationMode.generated.h"

UCLASS(BlueprintType, Category = "CandyLandSaga|Game Mode")
class SAGAGAME_API ASagaGameInitializationMode : public ASagaUserInterfaceModeBase
{
	GENERATED_BODY()

public:
	ASagaGameInitializationMode();
};
