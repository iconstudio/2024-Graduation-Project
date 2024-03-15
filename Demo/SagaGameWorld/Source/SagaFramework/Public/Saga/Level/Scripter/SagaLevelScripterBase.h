#pragma once
#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"

#include "SagaLevelScripterBase.generated.h"

UCLASS(Category = "CandyLandSaga|Framework")
class SAGAFRAMEWORK_API ASagaLevelScripterBase : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ASagaLevelScripterBase();

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
