#include "SagaGameInitializationMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Network/SagaNetwork.h"

ASagaGameInitializationMode::ASagaGameInitializationMode()
	: ASagaGameModeBase()
{
	auto instance = saga::USagaNetwork::Instance();
}

void
ASagaGameInitializationMode::BeginPlay()
{
	Super::BeginPlay();

	if (saga::USagaNetwork::Awake(TEXT("Nickname")))
	{
		UE_LOG(LogNet, Log, TEXT("The network system is initialized."));
	}
	else
	{
		UE_LOG(LogNet, Error, TEXT("Cannot initialize the network system."));
	}

	if (saga::USagaNetwork::Start())
	{
		UE_LOG(LogNet, Log, TEXT("The network system is started."));
	}
	else
	{
		UE_LOG(LogNet, Error, TEXT("Cannot start the network system."));
	}
}
