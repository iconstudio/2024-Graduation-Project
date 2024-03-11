#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "SagaVirtualUser.h"
#include "SagaVirtualRoom.h"
#include "SagaNetworkFunctionLibrary.generated.h"

UCLASS()
class SAGAGAME_API USagaNetworkFunctionLibrary : public UBlueprintFunctionLibrary
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
	static const TArray<FSagaVirtualUser>& GetPlayerList() noexcept;
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
};
