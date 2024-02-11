// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/SagaCharacterStatComponent.h"

// Sets default values for this component's properties
USagaCharacterStatComponent::USagaCharacterStatComponent()
{
	MaxHp = 200.0f;
	CurrentHp = MaxHp;
}


// Called when the game starts
void USagaCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHp(MaxHp);
}

float USagaCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage); //0���� ���� �ʰ� MaxHp�� �ʰ����� �ʵ��� ����
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		//�׾������� �̺�Ʈ ����
		OnHpZero.Broadcast();
	}
	return ActualDamage;
}

void USagaCharacterStatComponent::SetHp(float NewHp) //hp�����ɶ� �����ϴ� �Լ�
{
	//hp�� ����Ƿ��� �� �Լ��� ���ľ� �մϴ�.
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);

	//hp�ٲ���ٴ� ��ȣ ������
	OnHpChanged.Broadcast(CurrentHp);
}
