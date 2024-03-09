#include "SagaMainMenuMode.h"
#include "../Network/SagaNetwork.h"

ASagaMainMenuMode::ASagaMainMenuMode()
	: ASagaGameModeBase()
	, NicknameInput()
{
}

void ASagaMainMenuMode::StoreNickname(FString nickname)
{
	NicknameInput = nickname;
}

bool
ASagaMainMenuMode::TryLoginToServer()
{
	if (saga::USagaNetwork::Start(NicknameInput))
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
