#include "Game/SagaGameInitializationMode.h"
#include "Kismet/GameplayStatics.h"

ASagaGameInitializationMode::ASagaGameInitializationMode()
{
}

void
ASagaGameInitializationMode::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(initTimer, this, &ASagaGameInitializationMode::GotoNextLevel, 1.0f);
}

void
ASagaGameInitializationMode::BeginDestroy()
{
	Super::BeginDestroy();

	GetWorldTimerManager().ClearTimer(initTimer);
}

void
ASagaGameInitializationMode::GotoNextLevel()
{
	UGameplayStatics::OpenLevel(this, *TransferLevelName);
}
