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
	
	virtual void BeginPlay() override;

	virtual bool CanGotoNextLevel_Implementation() const noexcept override
	{
		return true;
	}

	virtual bool CanGotoPrevLevel_Implementation() const noexcept override
	{
		return false;
	}
};
