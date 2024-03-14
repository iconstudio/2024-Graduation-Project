#pragma once
#ifndef SAGAGAME_INC_GAMEMODE
#define SAGAGAME_INC_GAMEMODE
#include "BasicIncludes.inl"
#endif
#include "GameFramework/PlayerController.h"

#include "SagaPlayerControllerBase.generated.h"

UCLASS(BlueprintType, Abstract, Category = "CandyLandSaga|Game Mode|Controller")
class SAGAGAME_API ASagaPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
};
