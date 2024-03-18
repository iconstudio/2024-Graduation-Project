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

UCLASS(BlueprintType, Blueprintable, Category = "CandyLandSaga|Network")
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

	/* Local Client Methods */

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Session")
	void SetLocalUserId(int32 id) noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Session")
	int32 GetLocalUserId() const noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Session")
	void SetLocalUserName(const FString& nickname);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network|Session")
	FString GetLocalUserName() const;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Session")
	void SetCurrentRoomId(int32 id) noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network|Session")
	int32 GetCurrentRoomId() const noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Session")
	void SetCurrentRoomTitle(const FString& title);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network|Session")
	FString GetCurrentRoomTitle() const;

	/* Complicated Network Methods */

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Phase")
	bool TryLoginToServer(const FString& nickname);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	void UpdatePlayerList();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	void UpdateRoomList();

	/* Getters */

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	const TArray<FSagaVirtualUser>& GetUserList() const noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	const TArray<FSagaVirtualRoom>& GetRoomList() const noexcept;

	/* Observers */

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	bool SagaNetworkHasSocket() noexcept;

	/* Internal Event Broadcasting Methods */

	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnNetworkInitialized() const;
	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnFailedToInitializeNetwork() const;
	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnConnected() const;
	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnFailedToConnect(ESagaConnectionContract reason) const;
	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnDisconnected() const;
	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnRoomCreated(int32 room_id) const;
	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnJoinedRoom(int32 user_id) const;
	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnLeftRoomBySelf() const;
	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnLeftRoom(int32 id) const;
	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnRespondVersion(const FString& version_string) const;
	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnUpdateRoomList(UPARAM(ref) const TArray<FSagaVirtualRoom>& list) const;
	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnUpdateMembers(UPARAM(ref) const TArray<FSagaVirtualUser>& list) const;
	UFUNCTION(Category = "CandyLandSaga|Network|Internal")
	void BroadcastOnUpdatePosition(int32 user_id, float x, float y, float z) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CandyLandSaga|Network")
	int32 localUserId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CandyLandSaga|Network")
	FString localUserName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CandyLandSaga|Network")
	int32 currentRoomId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CandyLandSaga|Network")
	FString currentRoomTitle;

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
	void OnUpdateRoomList_Implementation(UPARAM(ref) const TArray<FSagaVirtualRoom>& list);
	UFUNCTION()
	void OnUpdateMembers_Implementation(UPARAM(ref) const TArray<FSagaVirtualUser>& list);
	UFUNCTION()
	void OnUpdatePosition_Implementation(int32 id, float x, float y, float z);

	TArray<TScriptInterface<ISagaNetworkView>, FConcurrentLinearArrayAllocator> internalList;
};
