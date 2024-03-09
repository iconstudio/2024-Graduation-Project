#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SagaGameModeBase.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Game Mode")
class SAGAGAME_API ASagaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASagaGameModeBase();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="level_name"></param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga/Game Mode/Event")
	void GotoNextLevel();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="level_name"></param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga/Game Mode/Event")
	void GotoPrevLevel();
	[[nodiscard]] UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga/Game Mode/Event")
	bool CanGotoNextLevel() const noexcept;
	[[nodiscard]] UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga/Game Mode/Event")
	bool CanGotoPrevLevel() const noexcept;

	virtual void GotoNextLevel_Implementation();
	virtual void GotoPrevLevel_Implementation();
	[[nodiscard]] virtual bool CanGotoNextLevel_Implementation() const noexcept;
	[[nodiscard]] virtual bool CanGotoPrevLevel_Implementation() const noexcept;
};
