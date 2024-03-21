#pragma once
#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"

#include "SagaLevelScripterBase.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga|Framework|Level")
class SAGAFRAMEWORK_API ASagaLevelScripterBase : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ASagaLevelScripterBase();

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Level")
	void GotoPrevLevel();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Level")
	bool CanGotoPrevLevel() const noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Level")
	bool CanGotoNextLevel() const noexcept;

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Level")
	void SetPrevLevelName(FName level_name);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Level")
	void SetNextLevelName(FName level_name);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Level")
	void SetPrevLevelNameFrom(ULevel* level);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Level")
	void SetNextLevelNameFrom(ULevel* level);

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Level")
	void TransitionLevel(FName level_name);

private:
	TOptional<FName> PrevLevelName;
	TOptional<FName> NextLevelName;
};
