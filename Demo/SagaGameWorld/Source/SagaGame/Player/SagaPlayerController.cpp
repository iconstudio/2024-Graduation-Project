// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SagaPlayerController.h"

void ASagaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
