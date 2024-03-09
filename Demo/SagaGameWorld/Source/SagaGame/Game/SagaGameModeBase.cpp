#include "SagaGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ASagaGameModeBase::ASagaGameModeBase()
	: AGameModeBase()
	, PrevLevelName(), NextLevelName()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASagaGameModeBase::TransitionLevel(FName level_name)
{
	UGameplayStatics::OpenLevel(this, MoveTempIfPossible(level_name));
}

bool
ASagaGameModeBase::CanGotoPrevLevel_Implementation()
const noexcept
{
	return false;
}

bool
ASagaGameModeBase::CanGotoNextLevel_Implementation()
const noexcept
{
	return false;
}

void
ASagaGameModeBase::GotoPrevLevel_Implementation()
{
	if (CanGotoPrevLevel())
	{
		TransitionLevel(PrevLevelName);
	}
}

void
ASagaGameModeBase::GotoNextLevel_Implementation()
{
	if (CanGotoNextLevel())
	{
		TransitionLevel(NextLevelName);
	}
}

void ASagaGameModeBase::SetPrevLevelName(FName level_name)
{
	PrevLevelName = level_name;
}

void ASagaGameModeBase::SetNextLevelName(FName level_name)
{
	NextLevelName = level_name;
}

void ASagaGameModeBase::SetPrevLevelNameFrom(ULevel* level)
{
	PrevLevelName = level->GetFName();
}

void ASagaGameModeBase::SetNextLevelNameFrom(ULevel* level)
{
	NextLevelName = level->GetFName();
}
