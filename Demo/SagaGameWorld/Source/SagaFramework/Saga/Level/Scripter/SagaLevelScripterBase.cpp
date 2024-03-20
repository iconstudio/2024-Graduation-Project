#include "Saga/Level/Scripter/SagaLevelScripterBase.h"
#include "Kismet/GameplayStatics.h"

ASagaLevelScripterBase::ASagaLevelScripterBase()
	: ALevelScriptActor()
	, PrevLevelName(), NextLevelName()
{
}

void
ASagaLevelScripterBase::GotoPrevLevel()
{
	if (CanGotoPrevLevel())
	{
		TransitionLevel(*PrevLevelName);
	}
}

void
ASagaLevelScripterBase::GotoNextLevel()
{
	if (CanGotoNextLevel())
	{
		TransitionLevel(*NextLevelName);
	}
}

bool
ASagaLevelScripterBase::CanGotoPrevLevel()
const noexcept
{
	return PrevLevelName.IsSet();
}

bool
ASagaLevelScripterBase::CanGotoNextLevel()
const noexcept
{
	return NextLevelName.IsSet();
}

void ASagaLevelScripterBase::TransitionLevel(FName level_name)
{
	AsyncTask(ENamedThreads::GameThread
		, [this, level_name]()
		{
			UGameplayStatics::OpenLevel(this, level_name);
		}
	);
}

void ASagaLevelScripterBase::SetPrevLevelName(FName level_name)
{
	PrevLevelName = level_name;
}

void ASagaLevelScripterBase::SetNextLevelName(FName level_name)
{
	NextLevelName = level_name;
}

void ASagaLevelScripterBase::SetPrevLevelNameFrom(ULevel* level)
{
	PrevLevelName = level->GetFName();
}

void ASagaLevelScripterBase::SetNextLevelNameFrom(ULevel* level)
{
	NextLevelName = level->GetFName();
}
