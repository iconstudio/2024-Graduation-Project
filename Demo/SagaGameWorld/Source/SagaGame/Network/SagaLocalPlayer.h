#pragma once
#include "CoreMinimal.h"
#include "SagaNetworkView.h"

class SAGAGAME_API FSagaLocalPlayer : public ISagaNetworkView
{
public:
	using ISagaNetworkView::ISagaNetworkView;

	/* Events */

	virtual void OnPlayerConnected_Implementation(const int32 PlayerID) override;
	virtual void OnPlayerDisconnected_Implementation(const int32 PlayerID) override;
	virtual void OnConnected_Implementation(const int32 LocalID) override;
};
