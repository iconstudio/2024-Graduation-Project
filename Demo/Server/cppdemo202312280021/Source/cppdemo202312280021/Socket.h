#pragma once
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "NativeSocket.h"
#include "Socket.generated.h"

UCLASS(BlueprintType, Blueprintable, Abstract, meta = (DisplayName = "Socket Interface Component"), ClassGroup = (Iconer))
class CPPDEMO202312280021_API USocket : public UActorComponent
{
	GENERATED_BODY()

public:	
	USocket();
	~USocket() noexcept;

	UFUNCTION()
	bool Connect(const FEndpoint& endpoint) const noexcept;
	UFUNCTION()
	bool ConnectTo(FString ip_address, uint16 port) const noexcept;
	UFUNCTION()
	bool Listen() const noexcept;
	UFUNCTION()
	FNativeSocket Accept() const noexcept;
	UFUNCTION()
	bool ReserveAcceptByNativeSocket(FIoContext& context, FNativeSocket& native_socket) const noexcept;
	UFUNCTION()
	bool ReserveAccept(FIoContext& context, USocket* socket_component) const noexcept;
	UFUNCTION()
	bool Disconnect() const noexcept;
	UFUNCTION()
	bool DisconnectAsync(FIoContext& context) const noexcept;

	UFUNCTION()
	const FNativeSocket& GetNativeHandle() const noexcept;

	virtual void TickComponent(float dt, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintSetter)
	void SetReuseAddress(bool flag) noexcept;
	UFUNCTION(BlueprintGetter)
	bool GetReuseAddress() const noexcept;

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
