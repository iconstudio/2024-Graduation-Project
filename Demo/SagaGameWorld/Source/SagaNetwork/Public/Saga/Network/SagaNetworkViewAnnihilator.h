#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "SagaNetworkViewAnnihilator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSagaActorDestroyedEventPin);

UCLASS(Category = "CandyLandSaga|Network")
class SAGANETWORK_API USagaNetworkViewAnnihilator : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	USagaNetworkViewAnnihilator(const FObjectInitializer& initializer);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "CandyLandSaga|Network")
	static USagaNetworkViewAnnihilator* DestroyNetworkView(const UObject* WorldContextObject, AActor* destroyed_object);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaActorDestroyedEventPin DestroyEventDelegate;

protected:
	UFUNCTION()
	void _DestroyNetworkView_Implementation(AActor* destroyed_object);

	const UObject* WorldContextObject;
	bool IsActived;
	UPROPERTY(VisibleAnywhere, Category = "CandyLandSaga|Network")
	AActor* DestroyingInstance;
};
