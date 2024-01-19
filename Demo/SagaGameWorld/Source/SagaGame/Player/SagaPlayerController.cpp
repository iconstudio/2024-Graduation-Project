// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SagaPlayerController.h"
#include "SagaGame.h"

ASagaPlayerController::ASagaPlayerController()
{

}

void ASagaPlayerController::BeginPlay()
{
	SAGA_Log(LogSagaNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::BeginPlay();

	SAGA_Log(LogSagaNetwork, Log, TEXT("%s"), TEXT("End"));

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
