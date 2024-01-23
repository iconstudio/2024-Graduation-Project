// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SagaGameModeBase.h"
#include "Player/SagaPlayerController.h"

ASagaGameMode::ASagaGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> SagaCharacterClassRef(TEXT("/Script/SagaGame.SagaCharacterPlayer"));
	if (SagaCharacterClassRef.Class)
	{
		DefaultPawnClass = SagaCharacterClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/SagaGame.SagaPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

}
