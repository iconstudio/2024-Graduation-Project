#pragma once
#include "CoreMinimal.h"

#include "SagaGameModeBase.h"
#include "SagaMainMenuMode.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Game Mode")
class SAGAGAME_API ASagaMainMenuMode : public ASagaGameMode
{
	GENERATED_BODY()

public:
	ASagaMainMenuMode();

	virtual void GotoPrevLevel_Implementation() override
	{}

	virtual void GotoNextLevel_Implementation() override
	{}

	virtual bool CanGotoNextLevel_Implementation() const noexcept override
	{
		return true;
	}

	virtual bool CanGotoPrevLevel_Implementation() const noexcept override
	{
		return true;
	}
};
