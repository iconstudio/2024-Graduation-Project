#include "Saga/System/SagaGameManager.h"
#include "Saga/Network/SagaNetworkFunctionLibrary.h"

void
USagaGameManager::Shutdown()
{
	Super::Shutdown();
	USagaNetworkFunctionLibrary::SagaNetworkClose();
}
