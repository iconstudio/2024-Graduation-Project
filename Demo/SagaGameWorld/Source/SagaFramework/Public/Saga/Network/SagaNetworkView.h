#pragma once
#include "SagaFramework.h"
#include "UObject/Interface.h"

#include "Saga/Network/SagaConnectionContract.h"
#include "Saga/Network/SagaVirtualRoom.h"
#include "Saga/Network/SagaVirtualUser.h"
#include "SagaNetworkView.generated.h"

UINTERFACE(MinimalAPI, BlueprintType, Blueprintable)
class USagaNetworkView : public UInterface
{
	GENERATED_BODY()
};

class SAGAFRAMEWORK_API ISagaNetworkView
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnNetworkInitialized();
	virtual void OnNetworkInitialized_Implementation() {};

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnFailedToInitializeNetwork();
	virtual void OnFailedToInitializeNetwork_Implementation() {};

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnConnected();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnFailedToConnect(ESagaConnectionContract reason);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnDisconnected();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnRespondVersion(const FString& version_string);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnUpdateRoomList(const TArray<FSagaVirtualRoom>& list);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnUpdateMembers(const TArray<FSagaVirtualUser>& list);
};
