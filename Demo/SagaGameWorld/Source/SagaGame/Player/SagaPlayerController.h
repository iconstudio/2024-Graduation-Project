#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SagaPlayerController.generated.h"

UCLASS()
class SAGAGAME_API ASagaPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;

	void StartMoveForward();
	void EndMoveForward();
	void StartMoveBackward();
	void EndMoveBackward();
	void StartJump();

private:
	FKey MoveForwardKey;
	FKey MoveBackwardKey;
	FKey MoveLeftKey;
	FKey MoveRightKey;
	FKey JumpKey;
};
