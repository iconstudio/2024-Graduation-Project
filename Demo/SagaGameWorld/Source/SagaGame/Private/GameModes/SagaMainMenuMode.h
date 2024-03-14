#pragma once
#include "CoreMinimal.h"

#include "SagaUserInterfaceModeBase.h"
#include "SagaMainMenuMode.generated.h"

UCLASS(BlueprintType, Category = "CandyLandSaga|Game Mode")
class SAGAGAME_API ASagaMainMenuMode : public ASagaUserInterfaceModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode|Main Menu")
	bool TryLoginToServer(FString nickname);
};
