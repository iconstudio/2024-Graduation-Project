#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Saga/Network/SagaVirtualUser.h"
#include "Saga/Network/SagaVirtualRoom.h"
#include "SagaNetworkFunctionLibrary.generated.h"

UCLASS()
class SAGANETWORK_API USagaNetworkFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static FSocket& SagaNetworkGetSocket() noexcept;
	[[nodiscard]] UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	static bool SagaNetworkHasSocket() noexcept;

	[[nodiscard]] UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	static int32 SagaNetworkLocalPlayerID() noexcept;
	[[nodiscard]] UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	static FString SagaNetworkLocalPlayerName() noexcept;
	[[nodiscard]] UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	static int32 SagaNetworkCurrentRoomID() noexcept;
	[[nodiscard]] UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network")
	static FString SagaNetworkCurrentRoomTitle() noexcept;

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static const TArray<FSagaVirtualUser>& GetUserList() noexcept;
	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static const TArray<FSagaVirtualRoom>& GetRoomList() noexcept;
	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static const TArray<FSagaVirtualUser>& AwaitPlayerList(TPromise<bool> promise);
	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static const TArray<FSagaVirtualRoom>& AwaitRoomList(TPromise<bool> promise);

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static void UpdatePlayerList();
	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
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
};
