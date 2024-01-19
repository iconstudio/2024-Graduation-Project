// Copyright Epic Games, Inc. All Rights Reserved.

#include "SagaGameGameMode.h"
#include "SagaGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASagaGameGameMode::ASagaGameGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/SagaGame.SagaPlayerController")); //������Ϻ��ʿ�
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
