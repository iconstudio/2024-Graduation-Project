// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SagaCharacterAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/SagaCharacterPlayer.h"

USagaCharacterAnimInstance::USagaCharacterAnimInstance()
{
	MovingThreshould = 3.0f;
	JumpingThreshould = 100.f;
}

void USagaCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void USagaCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//�����Ӹ��� Movement��ü�� ������ Movement��ü�κ��� ���ϴ� ������ ������ ��
	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);
	}
}
