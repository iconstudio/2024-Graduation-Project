#pragma once
#include "Utility/HeaderHelper.inl"
#include "GameFramework/PlayerController.h"

#include "SagaPlayerControllerBase.generated.h"

UCLASS(BlueprintType, Abstract, Category = "CandyLandSaga|Game Mode|Controller")
class SAGAGAME_API ASagaPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
};
