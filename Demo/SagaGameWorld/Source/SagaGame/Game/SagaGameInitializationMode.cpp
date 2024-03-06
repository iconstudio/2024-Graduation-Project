#include "Game/SagaGameInitializationMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Network/SagaNetwork.h"

ASagaGameInitializationMode::ASagaGameInitializationMode()
{
	auto instance = saga::USagaNetwork::Instance();
}

void
ASagaGameInitializationMode::BeginPlay()
{
	Super::BeginPlay();

	if (not saga::USagaNetwork::Awake(TEXT("Nickname")))
	{
		UE_LOG(LogNet, Error, TEXT("Cannot initialize the network system."));
	}

	if (not saga::USagaNetwork::Start())
	{
		UE_LOG(LogNet, Error, TEXT("Cannot start the network system."));
	}
}

void
ASagaGameInitializationMode::BeginDestroy()
{
	Super::BeginDestroy();
}
