// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "SagaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SAGAGAME_API ASagaPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
public:
	void SendKeyToServer(FKey Key);
	void SetupInputComponent();
	void Jump();

private:
	FSocket* SagaClientSocket;
	FSocket* CreateSocket();
};
