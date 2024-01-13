// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"

USTRUCT(BluprintType)
struct InitData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int32 id;
	FVector initpos;
};

// Sets default values
ANetworkManager::ANetworkManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ANetworkManager::AssignPlayerID(APlayerController* PlayerController)
{
	InitData S_CData;
	//수신받은 데이터 적용하는 코드 작성
}

void ANetworkManager::HandlePlayerDisconnected(int32 PlayerID)
{

}

// Called when the game starts or when spawned
void ANetworkManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void ANetworkManager::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

