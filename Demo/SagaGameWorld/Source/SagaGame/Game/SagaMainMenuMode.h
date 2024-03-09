#pragma once
#include "CoreMinimal.h"

#include "SagaGameModeBase.h"
#include "SagaMainMenuMode.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga|Game Mode")
class SAGAGAME_API ASagaMainMenuMode : public ASagaGameModeBase
{
	GENERATED_BODY()

public:
	ASagaMainMenuMode();

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode|Main Menu")
	void StoreNickname(FString nickname);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode|Main Menu")
	bool TryLoginToServer();

	virtual bool CanGotoPrevLevel_Implementation() const noexcept override
	{
		return false;
	}

	virtual bool CanGotoNextLevel_Implementation() const noexcept override
	{
		return true;
	}

	FString NicknameInput;
};
