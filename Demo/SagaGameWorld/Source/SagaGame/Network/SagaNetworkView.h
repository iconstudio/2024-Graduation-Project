#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "SagaRoomContract.h"
#include "../Utility/MacroHelper.inl"
#include "SagaNetworkView.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class USagaNetworkView : public UInterface
{
	GENERATED_BODY()
};

class SAGAGAME_API ISagaNetworkView
{
	GENERATED_BODY()

	// _Implementation
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnConnected();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnCreatedRoom(int32 room_id);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnFailedToCreateRoom(ERoomContract reason);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnJoinedRoomBySelf(int32 room_id);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnJoinedRoom(int32 client_id);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnFailedToJoinRoom(ERoomContract reason);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnLeftRoomBySelf();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnLeftRoom(int32 client_id);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnUserMoved(int32 client_id, float x, float y, float z);
};
