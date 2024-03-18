#pragma once
#include "SagaFramework.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "Saga/Network/SagaVirtualUser.h"
#include "Saga/Network/SagaVirtualRoom.h"
#include "SagaSessionListAwaiter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUSagaUsersAwaitOutputPin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUSagaRoomsAwaitOutputPin);

UCLASS(Category = "CandyLandSaga|Network")
class SAGAFRAMEWORK_API USagaUsersAwaiter : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	USagaUsersAwaiter(const FObjectInitializer& initializer);

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
class SAGAFRAMEWORK_API USagaRoomsAwaiter : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	USagaRoomsAwaiter(const FObjectInitializer& initializer);

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
