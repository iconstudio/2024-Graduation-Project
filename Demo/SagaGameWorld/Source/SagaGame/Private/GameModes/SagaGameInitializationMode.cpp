#include "SagaGameInitializationMode.h"
#include "Network/SagaNetwork.h"

ASagaGameInitializationMode::ASagaGameInitializationMode()
	: ASagaUserInterfaceModeBase()
{
	auto instance = saga::USagaNetwork::Instance();
}
