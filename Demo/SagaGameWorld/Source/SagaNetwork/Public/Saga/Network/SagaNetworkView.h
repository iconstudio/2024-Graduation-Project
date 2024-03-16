#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "SagaNetworkView.generated.h"

UINTERFACE(MinimalAPI)
class USagaNetworkView : public UInterface
{
	GENERATED_BODY()
};

class SAGANETWORK_API ISagaNetworkView
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnConnected();
	virtual void OnConnected_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnFailedToConnect(int32 reason);
	virtual void OnFailedToConnect_Implementation(int32 reason);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnDisconnected();
	virtual void OnDisconnected_Implementation();
};
