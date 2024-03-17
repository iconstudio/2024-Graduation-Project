#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "SagaGameManager.generated.h"

UCLASS(BlueprintType, Blueprintable, Category = "CandyLandSaga|System")
class SAGAFRAMEWORK_API USagaGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Shutdown() override;
};
