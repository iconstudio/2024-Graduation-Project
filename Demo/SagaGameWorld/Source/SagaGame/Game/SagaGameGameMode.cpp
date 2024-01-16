// Copyright Epic Games, Inc. All Rights Reserved.

#include "SagaGameGameMode.h"
#include "SagaGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASagaGameGameMode::ASagaGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}