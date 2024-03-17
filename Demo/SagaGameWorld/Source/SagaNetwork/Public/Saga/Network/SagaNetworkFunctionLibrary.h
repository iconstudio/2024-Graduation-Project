#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Saga/Network/SagaVirtualUser.h"
#include "Saga/Network/SagaVirtualRoom.h"
#include "Saga/Network/SagaNetworkView.h"
#include "Saga/Network/SagaConnectionContract.h"
#include "SagaNetworkFunctionLibrary.generated.h"

UCLASS(Category = "CandyLandSaga|Network")
class SAGANETWORK_API USagaNetworkFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal", meta = (BlueprintInternalUseOnly = "true"))
	static void BroadcastOnNetworkInitialized();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal", meta = (BlueprintInternalUseOnly = "true"))
	static void BroadcastOnFailedToInitializeNetwork();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal", meta = (BlueprintInternalUseOnly = "true"))
	static void BroadcastOnConnected();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal", meta = (BlueprintInternalUseOnly = "true"))
	static void BroadcastOnFailedToConnect(ESagaConnectionContract reason);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal", meta = (BlueprintInternalUseOnly = "true"))
	static void BroadcastOnDisconnected();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal", meta = (BlueprintInternalUseOnly = "true"))
	static void BroadcastOnRespondVersion(const FString& version_string);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal", meta = (BlueprintInternalUseOnly = "true"))
	static void BroadcastOnUpdateRoomList(const TArray<FSagaVirtualRoom>& list);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Internal", meta = (BlueprintInternalUseOnly = "true"))
	static void BroadcastOnUpdateMembers(const TArray<FSagaVirtualUser>& list);

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static void RegisterNetworkView(AActor* event_interface);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static void DeregisterNetworkView(AActor* event_interface);

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Phase")
	static bool TryLoginToServer(const FString& nickname);

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static bool SagaNetworkClose();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	static bool SagaNetworkHasSocket() noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	static int32 SagaNetworkLocalPlayerID() noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	static FString SagaNetworkLocalPlayerName() noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	static int32 SagaNetworkCurrentRoomID() noexcept;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	static FString SagaNetworkCurrentRoomTitle() noexcept;

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static const TArray<FSagaVirtualUser>& GetUserList() noexcept;
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static const TArray<FSagaVirtualRoom>& GetRoomList() noexcept;

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static void UpdatePlayerList();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static void UpdateRoomList();

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	static int32 SendSignInPacket(const FString& nickname);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	static int32 SendCreateRoomPacket(const FString& title);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	static int32 SendJoinRoomPacket(int32 room_id);
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	static int32 SendLeaveRoomPacket();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	static int32 SendRequestVersionPacket();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	static int32 SendRequestRoomsPacket();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	static int32 SendRequestMembersPacket();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	static int32 SendGameStartPacket();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	static int32 SendGameIsLoadedPacket();
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Packet")
	static int32 SendPositionPacket(float x, float y, float z);

private:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "CandyLandSaga|Network|Packet")
	void _DestroyNetworkView_Implementation(AActor* destroying_actor);
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "CandyLandSaga|Network|Packet")
	static USagaNetworkFunctionLibrary* GetSingleInstance();
};
