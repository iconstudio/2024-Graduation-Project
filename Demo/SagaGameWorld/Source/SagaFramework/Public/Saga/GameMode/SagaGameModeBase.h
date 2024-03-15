#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "SagaGameModeBase.generated.h"

UCLASS(BlueprintType, Abstract, Category = "CandyLandSaga|Game Mode")
class SAGAFRAMEWORK_API ASagaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASagaGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode|Event")
	void GotoPrevLevel();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode|Event")
	void GotoNextLevel();
	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode|Event")
	bool CanGotoPrevLevel() const noexcept;
	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mod|Event")
	bool CanGotoNextLevel() const noexcept;

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode")
	void SetPrevLevelName(FName level_name);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode")
	void SetNextLevelName(FName level_name);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode")
	void SetPrevLevelNameFrom(ULevel* level);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode")
	void SetNextLevelNameFrom(ULevel* level);

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode")
	void TransitionLevel(FName level_name);

private:
	TOptional<FName> PrevLevelName;
	TOptional<FName> NextLevelName;
};
