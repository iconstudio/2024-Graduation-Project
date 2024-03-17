#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "Saga/Network/SagaVirtualUser.h"
#include "Saga/Network/SagaVirtualRoom.h"
#include "SagaNetworkFunctionLibrary.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUSagaUsersAwaitOutputPin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUSagaRoomsAwaitOutputPin);

UCLASS(Category = "CandyLandSaga|Network")
class SAGANETWORK_API USagaNetworkFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network")
	static bool TryLoginToServer(const FString& nickname);

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
};

UCLASS(Category = "CandyLandSaga|Network")
class SAGANETWORK_API USagaUsersAwaiter : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "CandyLandSaga|Network")
	static USagaUsersAwaiter* AwaitUserList(const UObject* WorldContextObject, TArray<FSagaVirtualUser>& out);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FUSagaUsersAwaitOutputPin Success;
	UPROPERTY(BlueprintAssignable)
	FUSagaUsersAwaitOutputPin Failed;

private:
	UFUNCTION()
	void _Update();
	UFUNCTION()
	void _Finish();

	const UObject* WorldContextObject;
	bool IsActived;
	FTimerHandle UpdateTimer;
	TArray<FSagaVirtualUser>* MyOutput;
};

UCLASS(Category = "CandyLandSaga|Network")
class SAGANETWORK_API USagaRoomsAwaiter : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "CandyLandSaga|Network")
	static USagaRoomsAwaiter* AwaitRoomList(const UObject* WorldContextObject, TArray<FSagaVirtualRoom>& out);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FUSagaRoomsAwaitOutputPin Success;
	UPROPERTY(BlueprintAssignable)
	FUSagaRoomsAwaitOutputPin Failed;

private:
	UFUNCTION()
	void _Update();
	UFUNCTION()
	void _Finish();

	const UObject* WorldContextObject;
	bool IsActived;
	FTimerHandle UpdateTimer;
	TArray<FSagaVirtualRoom>* MyOutput;
};
