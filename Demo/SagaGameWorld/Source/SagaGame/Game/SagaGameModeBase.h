#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SagaGameModeBase.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Game Mode")
class SAGAGAME_API ASagaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASagaGameMode();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="level_name"></param>
	UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga/Game Mode/Event")
	void GotoNextLevel();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="level_name"></param>
	UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga/Game Mode/Event")
	void GotoPrevLevel();
	[[nodiscard]] UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga/Game Mode/Event")
	bool CanGotoNextLevel() const noexcept;
	[[nodiscard]] UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga/Game Mode/Event")
	bool CanGotoPrevLevel() const noexcept;

	virtual void GotoNextLevel_Implementation();
	virtual void GotoPrevLevel_Implementation();
	[[nodiscard]] virtual bool CanGotoNextLevel_Implementation() const noexcept;
	[[nodiscard]] virtual bool CanGotoPrevLevel_Implementation() const noexcept;
};
