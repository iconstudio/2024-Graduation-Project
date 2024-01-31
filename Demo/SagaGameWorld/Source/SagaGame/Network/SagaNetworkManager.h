#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SagaNetwork.h"
#include "SagaNetworkManager.generated.h"

UCLASS()
class SAGAGAME_API ASagaNetworkManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASagaNetworkManager();
	
	virtual void Tick(float DeltaTime) override;

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	USagaNetwork* AcquireInternalNetwork() const
	{
		return Cast<USagaNetwork>(GetGameInstance());
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
