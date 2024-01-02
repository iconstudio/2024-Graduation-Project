#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HAL/Runnable.h"
#include "NetworkManager.generated.h"

UCLASS(ClassGroup = (Iconer), meta = (BlueprintSpawnableComponent))
class CPPDEMO202312280021_API UNetworkManager : public UActorComponent
{
	GENERATED_BODY()

public:
	struct InternalWorker : public FRunnable
	{
		InternalWorker(int32 target) noexcept;
		virtual ~InternalWorker() noexcept;

		virtual uint32 Run() override { return 0; };
		virtual void Stop() override {};
		virtual void Exit() override {};

		FRunnableThread* myThread;
		bool isCancelled;
	};

	static inline InternalWorker* myWorker = nullptr;

public:
	// Sets default values for this component's properties
	UNetworkManager();

	static bool Initialize() noexcept { return true; };
	static InternalWorker& Start() { return *myWorker; };
	static void Destroy() noexcept {};
	static void Cleanup() noexcept {}

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
