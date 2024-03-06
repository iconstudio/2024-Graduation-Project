#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/SagaInitializationLevelUI.h"
#include "SagaGameModeBase.h"
#include "SagaGameInitializationMode.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Game Modes")
class SAGAGAME_API ASagaGameInitializationMode : public ASagaGameMode
{
	GENERATED_BODY()

public:
	static inline const FString TransferLevelName = "MainMenuLevel";
	
	ASagaGameInitializationMode();
	
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
};
