#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "SagaNetworkView.h"
#include "SagaNetwork.generated.h"

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

	// 클라이언트에게 고유 ID를 할당하고 알림
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
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

	/// <remarks>로컬 플레이어도 포함</remarks>
	TArray<USagaNetworkView*> EveryClients;
};
