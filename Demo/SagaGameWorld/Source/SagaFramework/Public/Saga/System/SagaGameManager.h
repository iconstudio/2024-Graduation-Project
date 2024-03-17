#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "SagaGameManager.generated.h"

UCLASS(BlueprintType, Category = "CandyLandSaga|System")
class SAGAFRAMEWORK_API USagaGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	USagaGameManager();
};
