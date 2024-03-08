#pragma once
#include "CoreMinimal.h"

#include "SagaGameModeBase.h"
#include "SagaNetworkReadyMode.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Game Modes")
class SAGAGAME_API ASagaNetworkReadyMode : public ASagaGameMode
{
	GENERATED_BODY()

public:
	ASagaNetworkReadyMode();

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
