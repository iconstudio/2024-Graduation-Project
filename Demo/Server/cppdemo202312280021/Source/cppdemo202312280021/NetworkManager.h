#pragma once
#include "CoreMinimal.h"
#include "NativeSocket.h"
#include "NetworkView.h"

#include "Components/ActorComponent.h"
#include "HAL/Runnable.h"
#include "NetworkManager.generated.h"

struct CPPDEMO202312280021_API FInternalNetworkWorker : public FRunnable
{
	FInternalNetworkWorker(int32 target) noexcept;
	virtual ~FInternalNetworkWorker() noexcept override;

	virtual uint32 Run() override { return 0; };
	virtual void Stop() override {};
	virtual void Exit() override {};

	FRunnableThread* myThread;
	bool isCancelled;
};

	// Ctor / Dtors
	
	UNetworkManager();
	virtual ~UNetworkManager() noexcept override;

	// Unreal Actions
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Methods
	
	// Events
	
	UFUNCTION(BlueprintCallable, Category = "Iconer")
	bool InitializeNetworkSystem() noexcept;
	UFUNCTION(BlueprintCallable, Category = "Iconer")
	bool CleanupNetworkSystem();
	UFUNCTION(BlueprintNativeEvent, Category = "Iconer")
	void OnNetworkInitialized() noexcept;
	UFUNCTION(BlueprintNativeEvent, Category = "Iconer")
	void OnNetworkInitializationFailed() noexcept;
	UFUNCTION(BlueprintNativeEvent, Category = "Iconer")
	void OnNetworkDestructed() noexcept;
	UFUNCTION(BlueprintNativeEvent, Category = "Iconer")
	void OnNetworkDestructionFailed() noexcept;

	// Static fields
	
	static inline FInternalNetworkWorker* myWorker = nullptr;

	// Properties
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsReady;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsConnected;

	// Fields

	TArray<TSharedRef<UNetworkView>> networkViews;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnNetworkInitialized_Implementation() noexcept;
	virtual void OnNetworkInitializationFailed_Implementation() noexcept;
	virtual void OnNetworkDestructed_Implementation() noexcept;
	virtual void OnNetworkDestructionFailed_Implementation() noexcept;
};

namespace net::ue
{
	using NetworkManager = ::UNetworkManager;
}
