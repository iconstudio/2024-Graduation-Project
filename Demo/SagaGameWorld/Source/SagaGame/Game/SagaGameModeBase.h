#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SagaGameModeBase.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Game Modes")
class SAGAGAME_API ASagaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASagaGameMode();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="level_name"></param>
	UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga/GameMode/Event")
	void GotoNextLevel();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="level_name"></param>
	UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga/GameMode/Event")
	void GotoPrevLevel();

	[[nodiscard]] UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga/GameMode/Event")
	bool CanGotoNextLevel() const noexcept;
	[[nodiscard]] UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga/GameMode/Event")
	bool CanGotoPrevLevel() const noexcept;

	virtual void BeginPlay() override;
	virtual void Tick(float delta_time) override;
	virtual void BeginDestroy() override;
};
