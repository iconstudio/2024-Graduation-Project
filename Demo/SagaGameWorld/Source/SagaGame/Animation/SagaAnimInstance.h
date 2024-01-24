// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SagaAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAGAGAME_API USagaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	USagaAnimInstance();

protected:
	//�̺�Ʈ �Լ�
	virtual void NativeInitializeAnimation() override; // AnimInstance�� ó�� �����ɶ� �ѹ� ȣ��

	virtual void NativeUpdateAnimation(float DeltaSeconds) override; //�� �����Ӹ��� ȣ���

	//anim graph�� ������ �������� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity; //�ӵ� ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed; //������ �ӷ� ����

	//idle�������� �ƴ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsIdle : 1;

	//�����̴��� Idle����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float MovingThreshould;

	//��������������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1;

	//���� ����������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1;

	//���������� ��Ÿ��������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreshould;

};
