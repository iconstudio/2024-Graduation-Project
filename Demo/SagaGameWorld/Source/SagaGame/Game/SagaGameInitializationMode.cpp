#include "SagaGameInitializationMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Network/SagaNetwork.h"

ASagaGameInitializationMode::ASagaGameInitializationMode()
	: ASagaGameModeBase()
{
	auto instance = saga::USagaNetwork::Instance();
}
