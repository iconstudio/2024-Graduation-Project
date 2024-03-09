#pragma once
#include "CoreMinimal.h"

#include "SagaGameModeBase.h"
#include "SagaInGameMode.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga|Game Mode")
class SAGAGAME_API ASagaInGameMode : public ASagaGameModeBase
{
	GENERATED_BODY()

public:
	ASagaInGameMode();

	virtual bool CanGotoPrevLevel_Implementation() const noexcept override
	{
		return true;
	}

	virtual bool CanGotoNextLevel_Implementation() const noexcept override
	{
		return false;
	}
};
