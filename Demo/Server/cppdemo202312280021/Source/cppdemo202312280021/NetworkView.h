#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Socket.h"
#include "NetworkView.generated.h"

UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = (Iconer))
class CPPDEMO202312280021_API UNetworkView : public USocket, public TSharedFromThis<UNetworkView>
{
	GENERATED_BODY()

public:
	UNetworkView();
};

namespace net::ue
{
	using SocketView = ::UNetworkView;
}
