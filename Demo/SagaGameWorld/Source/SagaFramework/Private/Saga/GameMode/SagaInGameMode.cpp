#include "Saga/GameMode/SagaInGameMode.h"

ASagaInGameMode::ASagaInGameMode()
	: ASagaGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> SagaCharacterClassRef(TEXT("/Script/Engine.Blueprint'/Game/BP/BP_SagaCharacterPlayer.BP_SagaCharacterPlayer_C'"));
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
