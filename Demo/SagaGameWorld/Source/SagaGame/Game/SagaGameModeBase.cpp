#include "Game/SagaGameModeBase.h"
#include "Player/SagaPlayerController.h"

ASagaGameMode::ASagaGameMode()
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
