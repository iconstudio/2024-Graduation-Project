#include "Saga/System/SagaGameManager.h"
#include "Saga/Network/SagaNetworkSubSystem.h"

void
USagaGameManager::Shutdown()
{
	Super::Shutdown();

	//auto net_system = GetSubsystem<USagaNetworkSubSystem>();

	//net_system->Destroy();
}
