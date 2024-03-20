#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tasks/Task.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"

#include "Saga/Network/SagaPacketProtocol.h"
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

class SAGANETWORK_API FSagaNetworkWorker final : public FRunnable
{
public:
	FSagaNetworkWorker(TObjectPtr<USagaNetworkSubSystem> instance);
	~FSagaNetworkWorker();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
	virtual void Stop() override;

private:
	void RouteEvents(const std::byte* packet_buffer, EPacketProtocol protocol, int16 packet_size);

	FRunnableThread* MyThread;
	TObjectPtr<USagaNetworkSubSystem> SubSystemInstance;
};

UCLASS(BlueprintType, Blueprintable, Category = "CandyLandSaga|Network")
class SAGANETWORK_API USagaNetworkSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USagaNetworkSubSystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }

	/* State Machines */
#pragma region =========================
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	bool Start(const FString& nickname);
#pragma endregion

	/* General Methods */
#pragma region =========================
	void CallFunctionOnGameThread(TUniqueFunction<void()> function);
#pragma endregion

	/* Local Client Methods */
#pragma region =========================
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
#pragma endregion

	/* Overall Clients Methods */
#pragma region =========================
	void AddUser(const FSagaVirtualUser& client);
	bool FindUser(int32 id, FSagaVirtualUser& outpin) noexcept;
	bool RemoveUser(int32 id) noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	const TArray<FSagaVirtualUser>& GetUserList() const noexcept;
	void ClearUserList() noexcept;
	bool HasUser(int32 id) const noexcept;
#pragma endregion

	/* Overall Rooms Methods */
#pragma region =========================
	void AddRoom(const FSagaVirtualRoom& room);
	bool FindRoom(int32 id, FSagaVirtualRoom& outpin) noexcept;
	bool RoomAt(int32 index, FSagaVirtualRoom& outpin) noexcept;
	bool RemoveRoom(int32 id) noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	const TArray<FSagaVirtualRoom>& GetRoomList() const noexcept;
	void ClearRoomList() noexcept;
	bool HasRoom(int32 id) const noexcept;
#pragma endregion

	/* Complicated Network Methods */
#pragma region =========================
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Phase")
	bool TryLoginToServer(const FString& nickname);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	void UpdatePlayerList();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	void UpdateRoomList();
#pragma endregion

	/* Getters */

	/* Observers */
#pragma region =========================
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	bool IsSocketAvailable() const noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	bool IsConnected() const noexcept;
#pragma endregion

	/* Packet Senders */
#pragma region =========================
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	int32 SendSignInPacket(const FString& nickname);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	int32 SendCreateRoomPacket(const FString& title);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	int32 SendJoinRoomPacket(int32 room_id);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	int32 SendLeaveRoomPacket();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	int32 SendRequestVersionPacket();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	int32 SendRequestRoomsPacket();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	int32 SendRequestMembersPacket();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	int32 SendGameStartPacket();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	int32 SendGameIsLoadedPacket();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	int32 SendPositionPacket(float x, float y, float z);
#pragma endregion

	/* Internal Event Broadcasting Methods */

#pragma region =========================
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
#pragma endregion

	friend class FSagaNetworkWorker;

	/* Local Properties */
#pragma region =========================
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CandyLandSaga|Network")
	int32 localUserId;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CandyLandSaga|Network")
	FString localUserName;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CandyLandSaga|Network")
	int32 currentRoomId;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CandyLandSaga|Network")
	FString currentRoomTitle;
#pragma endregion

	/* Events */
#pragma region =========================
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
#pragma endregion

	static TQueue<UE::Tasks::TTask<int32>> taskQueue;
	FGraphEventArray TaskCompletionEvents;

protected:
	/* Internal Functions */
#pragma region =========================
	UFUNCTION()
	bool InitializeNetwork_Implementation();
	UFUNCTION()
	ESagaConnectionContract ConnectToServer_Implementation();
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
#pragma endregion

	FSocket* clientSocket;
	TUniquePtr<FSagaNetworkWorker> netWorker;

	/// <remarks>로컬 플레이어도 포함</remarks>
	TArray<FSagaVirtualUser> everyUsers;
	TAtomic<bool> wasUsersUpdated;
	TArray<FSagaVirtualRoom> everyRooms;
	TAtomic<bool> wasRoomsUpdated;
};
