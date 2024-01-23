// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetworkManager.generated.h"

UCLASS()
class SAGAGAME_API ANetworkManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetworkManager();

	// 클라이언트에게 고유 ID를 할당하고 알림
	void AssignPlayerID(APlayerController* PlayerController);

	// 클라이언트가 나갈 때 처리
	void HandlePlayerDisconnected(int16 PlayerID);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
