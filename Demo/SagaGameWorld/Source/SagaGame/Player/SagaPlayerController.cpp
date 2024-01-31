#include "Player/SagaPlayerController.h"
//#include "Network/SagaNetwork.h"
//#include "Network/SagaPlayerInputSettings.h"

void
ASagaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}

void
ASagaPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    //MoveForwardKey = USagaPlayerInputSettings::GetMoveForwardKey();
    //MoveBackwardKey = USagaPlayerInputSettings::GetMoveBackwardKey();
    //MoveLeftKey = USagaPlayerInputSettings::GetMoveLeftKey();
    //MoveRightKey = USagaPlayerInputSettings::GetMoveRightKey();
    //JumpKey = USagaPlayerInputSettings::GetJumpKey();

    // Jump 액션에 대한 입력 바인딩
    //InputComponent->BindAction("Jump", IE_Pressed, this, &ASagaPlayerController::Jump);
}

void
ASagaPlayerController::StartMoveForward()
{

}

void
ASagaPlayerController::EndMoveForward()
{

}

void
ASagaPlayerController::StartMoveBackward()
{
}

void
ASagaPlayerController::EndMoveBackward()
{
}

void
ASagaPlayerController::StartJump()
{
	// 서버로 키 입력 전송
	//auto internal_network = Cast<USagaNetwork>(GetGameInstance());
	//internal_network->SendKeyToServer(JumpKey);
}
