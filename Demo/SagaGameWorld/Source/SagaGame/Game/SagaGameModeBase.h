#pragma once
#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "SagaGameModeBase.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga|Game Mode")
class SAGAGAME_API ASagaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASagaGameModeBase();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Game Mode|Event")
	void GotoNextLevel();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Game Mode|Event")
	void GotoPrevLevel();
	[[nodiscard]] UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Game Mod|Event")
	bool CanGotoNextLevel() const noexcept;
	[[nodiscard]] UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Game Mode|Event")
	bool CanGotoPrevLevel() const noexcept;

	virtual void GotoNextLevel_Implementation();
	virtual void GotoPrevLevel_Implementation();
	[[nodiscard]] virtual bool CanGotoNextLevel_Implementation() const noexcept;
	[[nodiscard]] virtual bool CanGotoPrevLevel_Implementation() const noexcept;

	UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "CandyLandSaga|Game Mode")
	void SetPrevLevelName(FName level_name);
	UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "CandyLandSaga|Game Mode")
	void SetNextLevelName(FName level_name);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode")
	void SetPrevLevelNameFrom(ULevel* level);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Game Mode")
	void SetNextLevelNameFrom(ULevel* level);

	UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "CandyLandSaga|Game Mode")
	void TransitionLevel(FName level_name);

private:
	UPROPERTY(BlueprintSetter = SetPrevLevelName)
	FName PrevLevelName;
	UPROPERTY(BlueprintSetter = SetNextLevelName)
	FName NextLevelName;
};
