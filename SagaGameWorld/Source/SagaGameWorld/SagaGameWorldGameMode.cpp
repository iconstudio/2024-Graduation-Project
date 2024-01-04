// Copyright Epic Games, Inc. All Rights Reserved.

#include "SagaGameWorldGameMode.h"
#include "SagaGameWorldCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASagaGameWorldGameMode::ASagaGameWorldGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
