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
	virtual ~USocket() noexcept override;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Attach(UPARAM(ref) FNativeSocket& native_socket) noexcept;
	UFUNCTION(BlueprintCallable, CallInEditor)
	bool Connect(UPARAM(ref) const FEndpoint& endpoint) const noexcept;
	UFUNCTION(BlueprintCallable, CallInEditor)
	bool ConnectTo(FString ip_address, int32 port) const noexcept;
	UFUNCTION(BlueprintCallable, CallInEditor)
	bool Listen() const noexcept;
	UFUNCTION()
	FNativeSocket Accept() const noexcept;
	UFUNCTION()
	bool ReserveAcceptByNativeSocket(UPARAM(ref) FIoContext& context, UPARAM(ref) FNativeSocket& native_socket) const noexcept;
	UFUNCTION()
	bool ReserveAccept(UPARAM(ref) FIoContext& context, USocket* socket_component) const noexcept;
	UFUNCTION(BlueprintCallable, CallInEditor)
	bool Disconnect() const noexcept;
	UFUNCTION(BlueprintCallable, CallInEditor)
	bool DisconnectAsync(UPARAM(ref) FIoContext& context) const noexcept;

	UFUNCTION()
	const FNativeSocket& GetNativeHandle() const noexcept;

	virtual void TickComponent(float dt, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintSetter, CallInEditor)
	void SetReuseAddress(bool flag) noexcept;
	UFUNCTION(BlueprintPure, BlueprintGetter, CallInEditor)
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
