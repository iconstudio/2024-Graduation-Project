#pragma once
#include "BasicIncludes.inl"

#include "SagaPlayerControllerBase.h"
#include "SagaInterfaceController.generated.h"

UCLASS(BlueprintType, Blueprintable, Category = "CandyLandSaga|Game Mode|Controller")
class SAGAGAME_API ASagaInterfaceController : public ASagaPlayerControllerBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;
};
