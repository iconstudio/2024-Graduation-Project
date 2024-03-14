#pragma once
#include "BasicIncludes.inl"

#include "SagaPlayerControllerBase.h"
#include "SagaGameController.generated.h"

UCLASS(BlueprintType, Blueprintable, Category = "CandyLandSaga|Game Mode|Controller")
class SAGAGAME_API ASagaGameController : public ASagaPlayerControllerBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;
};
