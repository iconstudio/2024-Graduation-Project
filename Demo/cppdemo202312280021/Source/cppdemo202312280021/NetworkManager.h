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

UCLASS(BlueprintType, Blueprintable, ClassGroup = (Iconer), meta = (BlueprintSpawnableComponent))
class CPPDEMO202312280021_API UNetworkManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Ctor / Dtors

	UNetworkManager();
	virtual ~UNetworkManager() noexcept override;

	// Unreal Actions

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Methods
	UFUNCTION(BlueprintCallable, Category = "Iconer")
	bool InitializeNetworkSystem() noexcept;
	UFUNCTION(BlueprintCallable, Category = "Iconer")
	bool CleanupNetworkSystem();

	// Events

	UFUNCTION(BlueprintNativeEvent, Category = "Iconer")
	void OnNetworkInitialized();
	UFUNCTION(BlueprintNativeEvent, Category = "Iconer")
	void OnNetworkInitializationFailed();
	UFUNCTION(BlueprintNativeEvent, Category = "Iconer")
	void OnNetworkDestructed();
	UFUNCTION(BlueprintNativeEvent, Category = "Iconer")
	void OnNetworkDestructionFailed();

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
	virtual void OnNetworkInitialized_Implementation();
	virtual void OnNetworkInitializationFailed_Implementation();
	virtual void OnNetworkDestructed_Implementation();
	virtual void OnNetworkDestructionFailed_Implementation();
};

namespace net::ue
{
	using NetworkManager = ::UNetworkManager;
}