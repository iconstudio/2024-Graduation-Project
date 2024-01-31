// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SagaAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

USagaAnimInstance::USagaAnimInstance()
{
	MovingThreshould = 3.0f;
	JumpingThreshould = 100.0f;
}

void USagaAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//�ʱ�ȭ ����
	//GetOwningActor(); //���� AnimInstance�� ����ϰ� �ִ� �������� ���� �� ����.
	//����Ÿ������ ��ȯ�Ǳ� ������ ĳ���ͷ� ����ȯ����
	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}

}

void USagaAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
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
