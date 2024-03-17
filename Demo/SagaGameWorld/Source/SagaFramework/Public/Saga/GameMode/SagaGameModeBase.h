#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Saga/Network/SagaNetworkView.h"
#include "SagaGameModeBase.generated.h"

UCLASS(BlueprintType, Blueprintable, Category = "CandyLandSaga|Game Mode")
class SAGAFRAMEWORK_API ASagaGameModeBase : public AGameModeBase, public ISagaNetworkView
{
	GENERATED_BODY()

public:
	virtual void OnConnected_Implementation() override;
	virtual void OnFailedToConnect_Implementation(int32 reason) override;
	virtual void OnDisconnected_Implementation() override;
	virtual void OnRespondVersion_Implementation(const FString& version_string) override;
	virtual void OnUpdateRoomList_Implementation(const TArray<FSagaVirtualRoom>& list) override;
	virtual void OnUpdateMembers_Implementation(const TArray<FSagaVirtualUser>& list) override;
};
