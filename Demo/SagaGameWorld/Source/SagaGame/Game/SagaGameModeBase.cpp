#include "SagaGameModeBase.h"
#include "Player/SagaPlayerController.h"

ASagaGameMode::ASagaGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
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
