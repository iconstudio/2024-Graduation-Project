#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NativeSocket.h"
#include "Socket.generated.h"

UCLASS(BlueprintType, Blueprintable, Abstract, meta = (DisplayName = "Unreal Engine Socket Interface Component"), ClassGroup = (Iconer))
class CPPDEMO202312280021_API USocket : public UActorComponent
{
	GENERATED_BODY()

public:	
	USocket();

	UFUNCTION()
	bool Connect(const FEndpoint& endpoint) const noexcept;
	UFUNCTION()
	bool ConnectTo(FStringView ip_address, uint16 port) const noexcept;
	UFUNCTION()
	bool Listen() const noexcept;
	UFUNCTION()
	FNativeSocket Accept() const noexcept;
	UFUNCTION()
	FNativeSocket ReserveAccept(const FNativeSocket&) const noexcept;
	UFUNCTION()
	FNativeSocket ReserveAccept(USocket& socket_component) const noexcept;
	UFUNCTION()
	FNativeSocket ReserveAccept(USocket* const socket_component) const noexcept;
	UFUNCTION()
	bool Disconnect() const noexcept

	UFUNCTION()
	FNativeSocket& GetNativeHandle() noexcept
	UFUNCTION()
	const FNativeSocket& GetNativeHandle() const noexcept

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UFUNCTION(BlueprintSetter)
	void SetReuseAddress(bool) noexcept;
	UFUNCTION(BlueprintGetter)
	bool GetReuseAddress() const noexcept;
	UFUNCTION()

	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, meta = (DisplayName = "Socket"))
	FNativeSocket myHandle;
	UPROPERTY(EditInstanceOnly, BlueprintSetter = SetReuseAddress, BlueprintGetter = GetReuseAddress)
	bool DoesReuseAddress;
};

namespace net::ue
{
	using SocketComponent = ::USocket;
	using SocketOptions = ::ESocketOptions;
	using SocketType = ::ESocketType;
}
