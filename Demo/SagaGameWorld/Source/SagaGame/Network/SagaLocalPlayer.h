#pragma once
#include "CoreMinimal.h"

#include "SagaNetworkView.h"
#include "SagaLocalPlayer.generated.h"

class SAGAGAME_API FSagaLocalPlayer : public ISagaNetworkView
{
public:
	/* Events */

	virtual void OnPlayerConnected_Implementation(const int32 PlayerID) override;
	virtual void OnPlayerDisconnected_Implementation(const int32 PlayerID) override;
	virtual void OnConnected_Implementation(const int32 LocalID) override;
};
