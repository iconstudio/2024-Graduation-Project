#include "SagaMainMenuMode.h"

ASagaMainMenuMode::ASagaMainMenuMode()
	: ASagaGameModeBase()
	, NicknameInput()
{
}

bool
ASagaMainMenuMode::TryLoginToServer()
{
	return false;
}
