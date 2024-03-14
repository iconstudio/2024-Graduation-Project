#include "GameModes/SagaMainMenuMode.h"
#include "Network/SagaNetwork.h"

bool
ASagaMainMenuMode::TryLoginToServer(FString nickname)
{
	if (saga::USagaNetwork::Start(MoveTemp(nickname)))
	{
		UE_LOG(LogNet, Log, TEXT("The network system is started."));
		return true;
	}
	else
	{
		UE_LOG(LogNet, Error, TEXT("Cannot start the network system."));
		return false;
	}
}
