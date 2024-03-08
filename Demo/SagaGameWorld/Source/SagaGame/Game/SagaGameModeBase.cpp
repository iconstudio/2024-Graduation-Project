#include "SagaGameModeBase.h"
#include "Player/SagaPlayerController.h"

ASagaGameMode::ASagaGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

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


void
ASagaGameMode::GotoNextLevel_Implementation()
{}

void
ASagaGameMode::GotoPrevLevel_Implementation()
{}

bool
ASagaGameMode::CanGotoNextLevel_Implementation()
const noexcept
{
	return false;
}

bool
ASagaGameMode::CanGotoPrevLevel_Implementation()
const noexcept
{
	return false;
}
