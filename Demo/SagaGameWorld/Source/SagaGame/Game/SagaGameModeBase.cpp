#include "SagaGameModeBase.h"
#include "Player/SagaPlayerController.h"

ASagaGameModeBase::ASagaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void
ASagaGameModeBase::GotoNextLevel_Implementation()
{}

void
ASagaGameModeBase::GotoPrevLevel_Implementation()
{}

bool
ASagaGameModeBase::CanGotoNextLevel_Implementation()
const noexcept
{
	return false;
}

bool
ASagaGameModeBase::CanGotoPrevLevel_Implementation()
const noexcept
{
	return false;
}
