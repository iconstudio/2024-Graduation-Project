#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NativeSocket.h"
#include "Socket.generated.h"

UCLASS(BlueprintType, Blueprintable, Abstract, meta = (DisplayName = "Unreal Engine Socket Interface Component"), ClassGroup = (Custom))
class CPPDEMO202312280021_API USocket : public UActorComponent
{
	GENERATED_BODY()

public:	
	USocket();

	//UFUNCTION()
	//bool Connect() const noexcept;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly)
	FNativeSocket myHandle;
};

namespace net::ue
{
	using SocketComponent = ::USocket;
	using SocketOptions = ::ESocketOptions;
	using SocketType = ::ESocketType;
}
