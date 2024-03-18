#pragma once
#include "SagaFramework.h"
#include "Engine/GameInstance.h"

#include "Saga/Network/SagaPacketProtocol.h"
#include "Saga/Network/SagaNetworkView.h"
#include "SagaGameManager.generated.h"

UCLASS(BlueprintType, Blueprintable, Category = "CandyLandSaga|Framework")
class SAGAFRAMEWORK_API USagaGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	USagaGameManager(const FObjectInitializer& initializer = FObjectInitializer::Get());

	/* Singleton Methods */

	virtual void Init() override;
	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework", meta = (WorldContext = "WorldContextObject"))
	static USagaGameManager* GetInstance(UObject* WorldContextObject);

	/* Worker */


	/* Connection Methods */

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework")
	bool InitializeNetwork();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework")
	bool ConnectToServer();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework")
	bool CloseNetwork();

	/* Local Client Methods */

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework")
	void SetLocalUserId(int32 id) noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Framework", meta = (CompactNodeTitle = "My ID"))
	int32 GetLocalUserId() noexcept;

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework")
	void SetLocalUserName(const FString& nickname);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Framework", meta = (CompactNodeTitle = "My Name"))
	FString GetLocalUserName();

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework")
	void SetCurrentRoomId(int32 id) noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Framework", meta = (CompactNodeTitle = "My Room ID"))
	int32 GetCurrentRoomId() noexcept;

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework")
	void SetCurrentRoomTitle(const FString& title);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Framework", meta = (CompactNodeTitle = "My Room Title"))
	FString GetCurrentRoomTitle();

	/* Overall Users Methods */

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	void AddUser(FSagaVirtualUser client);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	bool FindUser(int32 id, FSagaVirtualUser& output) noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	bool RemoveUser(int32 id) noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	const TArray<FSagaVirtualUser>& GetUserList() noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	void ClearUserList() noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Framework|Session Management")
	bool HasUser(int32 id) noexcept;

	/* Overall Rooms Methods */

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	void AddRoom(FSagaVirtualRoom room);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	bool FindRoom(int32 id, FSagaVirtualRoom& output) noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	bool RoomAt(int32 index, FSagaVirtualRoom& output) noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	bool RemoveRoom(int32 id) noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	void ClearRoomList() noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	const TArray<FSagaVirtualRoom>& GetRoomList() noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Framework|Session Management")
	bool HasRoom(int32 id) noexcept;

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	void UpdatePlayerList();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Session Management")
	void UpdateRoomList();

	/* Network Event Methods */

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework", meta = (CompactNodeTitle = "Register View"))
	bool RegisterNetworkView(AActor* event_interface);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework", meta = (CompactNodeTitle = "Deregister View"))
	void DeregisterNetworkView(AActor* event_interface);

	/* Internal Network Event Methods */

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Internal")
	void BroadcastOnNetworkInitialized();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Internal")
	void BroadcastOnFailedToInitializeNetwork();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Internal")
	void BroadcastOnConnected();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Internal")
	void BroadcastOnFailedToConnect(ESagaConnectionContract reason);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Internal")
	void BroadcastOnDisconnected();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Internal")
	void BroadcastOnRespondVersion(const FString& version_string);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Internal")
	void BroadcastOnUpdateRoomList(const TArray<FSagaVirtualRoom>& list);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Framework|Internal")
	void BroadcastOnUpdateMembers(const TArray<FSagaVirtualUser>& list);

	/* Getters */
	FSocket* GetClientSocket() noexcept;

	/* Observers */

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Framework")
	bool IsSocketAvailable() noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	bool IsConnected() noexcept;

protected:
	UFUNCTION()
	bool InitializeNetwork_Implementation();
	UFUNCTION()
	bool ConnectToServer_Implementation();
	UFUNCTION()
	bool CloseNetwork_Implementation();
	UFUNCTION()
	void AddUser_Implementation(FSagaVirtualUser user);
	UFUNCTION()
	bool FindUser_Implementation(int32 id, FSagaVirtualUser& output) noexcept;
	UFUNCTION()
	bool RemoveUser_Implementation(int32 id) noexcept;
	UFUNCTION()
	void ClearUserList_Implementation() noexcept;
	UFUNCTION()
	void AddRoom_Implementation(FSagaVirtualRoom room);
	UFUNCTION()
	bool FindRoom_Implementation(int32 id, FSagaVirtualRoom& output) noexcept;
	UFUNCTION()
	bool RoomAt_Implementation(int32 index, FSagaVirtualRoom& output) noexcept;
	UFUNCTION()
	bool RemoveRoom_Implementation(int32 id) noexcept;
	UFUNCTION()
	void ClearRoomList_Implementation() noexcept;
	UFUNCTION()
	bool IsSocketAvailable_Implementation() noexcept;
	UFUNCTION()
	bool IsConnected_Implementation() noexcept;
	UFUNCTION()
	void LockList() noexcept;
	UFUNCTION()
	void UnlockList() noexcept;

	FSocket* clientSocket;
	TSharedPtr<FSagaNetworkWorker> netWorker;

	int32 localUserId;
	FString localUserName;
	int32 currentRoomId;
	FString currentRoomTitle;

	TArray<FSagaVirtualUser> everyUsers;
	TAtomic<bool> wasUsersUpdated;
	TArray<FSagaVirtualRoom> everyRooms;
	TAtomic<bool> wasRoomsUpdated;

	TAtomic<bool> listLock;
	UPROPERTY()
	TArray<TScriptInterface<ISagaNetworkView>> internalList;
};

USTRUCT()
struct SAGAFRAMEWORK_API FSagaNetworkWorker
{
	GENERATED_BODY()

public:
	FSagaNetworkWorker() noexcept;

	FSagaNetworkWorker(USagaGameManager* instance) noexcept;

	void operator()();

	void EventRouter(const uint8* packet_buffer, EPacketProtocol protocol, int16 packet_size);

	UPROPERTY()
	USagaGameManager* Instance;
};

