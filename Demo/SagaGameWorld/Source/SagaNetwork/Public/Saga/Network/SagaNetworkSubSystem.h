#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "Saga/Network/SagaConnectionContract.h"
#include "Saga/Network/SagaVirtualRoom.h"
#include "Saga/Network/SagaVirtualUser.h"
#include "Saga/Network/SagaNetworkView.h"
#include "SagaNetworkSubSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSagaEventOnNetworkInitialized, bool, was_succeed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSagaEventOnConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSagaEventOnFailedToConnect, ESagaConnectionContract, reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSagaEventOnDisconnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSagaEventOnRoomCreated, int32, id);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSagaEventOnJoinedRoom, int32, id);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSagaEventOnLeftRoomBySelf);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSagaEventOnLeftRoom, int32, id);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSagaEventOnRespondVersion, const FString&, version_string);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSagaEventOnUpdateRoomList, const TArray<FSagaVirtualRoom>&, list);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSagaEventOnUpdateUserList, const TArray<FSagaVirtualUser>&, list);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSagaEventOnUpdatePosition, int32, id, float, x, float, y, float, z);


UCLASS()
class SAGANETWORK_API USagaNetworkSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USagaNetworkSubSystem();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const { return true; }

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	bool Awake();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	bool Start(const FString& nickname);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	bool Destroy();

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	void RegisterNetworkView(AActor* event_interface);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	void DeregisterNetworkView(AActor* event_interface);

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Phase")
	bool TryLoginToServer(const FString& nickname);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	bool SagaNetworkHasSocket() noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	int32 SagaNetworkLocalPlayerID() noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	FString SagaNetworkLocalPlayerName() noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	int32 SagaNetworkCurrentRoomID() noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	FString SagaNetworkCurrentRoomTitle() noexcept;

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	const TArray<FSagaVirtualUser>& GetUserList() noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	const TArray<FSagaVirtualRoom>& GetRoomList() noexcept;

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	void UpdatePlayerList();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	void UpdateRoomList();

	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaEventOnNetworkInitialized OnNetworkInitialized;
	//FDelegateHandle OnNetworkInitializedDelegateHandle;

	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaEventOnConnected OnConnected;
	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaEventOnFailedToConnect OnFailedToConnect;
	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaEventOnDisconnected OnDisconnected;

	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaEventOnRoomCreated OnRoomCreated;
	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaEventOnJoinedRoom OnJoinedRoom;
	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaEventOnLeftRoomBySelf OnLeftRoomBySelf;
	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaEventOnLeftRoom OnLeftRoom;

	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaEventOnRespondVersion OnRespondVersion;
	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaEventOnUpdateRoomList OnUpdateRoomList;
	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaEventOnUpdateUserList OnUpdateMembers;
	UPROPERTY(BlueprintAssignable, Category = "CandyLandSaga|Network")
	FSagaEventOnUpdatePosition OnUpdatePosition;

protected:
	UFUNCTION()
	void OnNetworkInitialized_Implementation(bool succeed);
	UFUNCTION()
	void OnConnected_Implementation();
	UFUNCTION()
	void OnFailedToConnect_Implementation(ESagaConnectionContract reason);
	UFUNCTION()
	void OnDisconnected_Implementation();
	UFUNCTION()
	void OnRoomCreated_Implementation(int32 id);
	UFUNCTION()
	void OnJoinedRoom_Implementation(int32 id);
	UFUNCTION()
	void OnLeftRoomBySelf_Implementation();
	UFUNCTION()
	void OnLeftRoom_Implementation(int32 id);
	UFUNCTION()
	void OnRespondVersion_Implementation(const FString& version_string);
	UFUNCTION()
	void OnUpdateRoomList_Implementation(const TArray<FSagaVirtualRoom>& list);
	UFUNCTION()
	void OnUpdateMembers_Implementation(const TArray<FSagaVirtualUser>& list);
	UFUNCTION()
	void OnUpdatePosition_Implementation(int32 id, float x, float y, float z);

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnNetworkInitialized();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnFailedToInitializeNetwork();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnConnected();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnFailedToConnect(ESagaConnectionContract reason);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnDisconnected();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnRespondVersion(const FString& version_string);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnUpdateRoomList(const TArray<FSagaVirtualRoom>& list);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnUpdateMembers(const TArray<FSagaVirtualUser>& list);

	TArray<TScriptInterface<ISagaNetworkView>, FConcurrentLinearArrayAllocator> internalList;
};
