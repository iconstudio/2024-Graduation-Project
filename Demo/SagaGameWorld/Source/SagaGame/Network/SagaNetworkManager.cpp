// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/SagaNetworkManager.h"

// Sets default values
ASagaNetworkManager::ASagaNetworkManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASagaNetworkManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASagaNetworkManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

