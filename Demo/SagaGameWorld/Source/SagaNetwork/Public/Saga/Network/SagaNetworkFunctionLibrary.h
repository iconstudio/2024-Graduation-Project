#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "SagaNetworkFunctionLibrary.generated.h"

UCLASS(Category = "CandyLandSaga|Network")
class SAGANETWORK_API USagaNetworkFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
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
