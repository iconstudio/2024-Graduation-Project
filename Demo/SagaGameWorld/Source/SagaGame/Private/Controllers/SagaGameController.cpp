#include "Controllers/SagaGameController.h"

void ASagaGameController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}

void ASagaGameController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Jump 액션에 대한 입력 바인딩
	// InputComponent->BindAction("Jump", IE_Pressed, this,
	// &ASagaPlayerController::Jump);
}
