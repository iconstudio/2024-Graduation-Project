#include "GameModes/SagaGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ASagaGameModeBase::ASagaGameModeBase()
	: AGameModeBase()
	, PrevLevelName(), NextLevelName()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void
ASagaGameModeBase::GotoPrevLevel()
{
	if (CanGotoPrevLevel())
	{
		TransitionLevel(*PrevLevelName);
	}
}

void
ASagaGameModeBase::GotoNextLevel()
{
	if (CanGotoNextLevel())
	{
		TransitionLevel(*NextLevelName);
	}
}

bool
ASagaGameModeBase::CanGotoPrevLevel()
const noexcept
{
	return PrevLevelName.IsSet();
}

bool
ASagaGameModeBase::CanGotoNextLevel()
const noexcept
{
	return NextLevelName.IsSet();
}

void ASagaGameModeBase::TransitionLevel(FName level_name)
{
	UGameplayStatics::OpenLevel(this, MoveTempIfPossible(level_name));
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
