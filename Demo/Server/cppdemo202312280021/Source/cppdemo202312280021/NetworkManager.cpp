// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"

// Sets default values for this component's properties
UNetworkManager::UNetworkManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNetworkManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNetworkManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UNetworkManager::InternalWorker::InternalWorker(int32 target) noexcept
{
}

UNetworkManager::InternalWorker::~InternalWorker() noexcept
{
}
