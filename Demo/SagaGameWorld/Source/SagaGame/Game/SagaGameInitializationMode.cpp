#include "SagaGameInitializationMode.h"
#include "../Network/SagaNetwork.h"

ASagaGameInitializationMode::ASagaGameInitializationMode()
	: ASagaGameModeBase()
{
	auto instance = saga::USagaNetwork::Instance();
}
