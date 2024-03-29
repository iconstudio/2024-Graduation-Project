#pragma once
#include "Saga/GameMode/SagaUserInterfaceModeBase.h"

#include "SagaMainMenuMode.generated.h"

UCLASS(BlueprintType)
class SAGAFRAMEWORK_API ASagaMainMenuMode : public ASagaUserInterfaceModeBase
{
	GENERATED_BODY()

public:
	bool TryLoginToServer(FString nickname);
};
