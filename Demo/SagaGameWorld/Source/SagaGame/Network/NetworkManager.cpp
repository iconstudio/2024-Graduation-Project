// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkManager.h"

// Sets default values
ANetworkManager::ANetworkManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ANetworkManager::AssignPlayerID(APlayerController* PlayerController)
{

}

void ANetworkManager::HandlePlayerDisconnected(int16 PlayerID)
{

}

// Called when the game starts or when spawned
void ANetworkManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANetworkManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

