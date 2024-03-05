#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Templates/UnrealTemplate.h"
#include "Templates/SharedPointer.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"

#include "SagaNetworkView.h"
#include "../Packets/SagaBasicPacket.h"
#include "SagaNetwork.generated.h"

class FSagaNetworkWorker;

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Network")
class SAGAGAME_API USagaNetwork : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
	virtual void Shutdown() override;

	/* Network Methods */

	void SendKeyToServer(FKey Key);

	/* Methods */
	void AddPacket(saga::FSagaBasicPacket* packet);
	saga::FSagaBasicPacket* PopPacket();
	bool TryPopPacket(saga::FSagaBasicPacket** handle);
	void AssignPlayerID(APlayerController* PlayerController);

	/* Local Events */
	
	void OnConnected();
	void OnPlayerConnected();
	void OnPlayerDisconnected();

	/* Observers */

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	constexpr FSocket* GetLocalSocket() const noexcept
	{
		return LocalSocket;
	}

protected:
	FSocket* LocalSocket;
	TSharedPtr<FSagaNetworkWorker> MyWorker;
	TArray<saga::FSagaBasicPacket*> PacketQueue;

	/// <remarks>로컬 플레이어도 포함</remarks>
	TArray<ISagaNetworkView*> EveryClients;
};

class FSagaNetworkWorker : public FRunnable
{
public:
	FSagaNetworkWorker();
	~FSagaNetworkWorker();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
	virtual void Stop() override;

private:
	FRunnableThread* MyThread;
};
