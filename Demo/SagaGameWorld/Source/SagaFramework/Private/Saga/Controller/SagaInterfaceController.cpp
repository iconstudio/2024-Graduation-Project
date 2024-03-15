#include "Saga/Controller/SagaInterfaceController.h"

void
ASagaInterfaceController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly UIOnlyInputMode;
    SetInputMode(UIOnlyInputMode);
}

void
ASagaInterfaceController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
