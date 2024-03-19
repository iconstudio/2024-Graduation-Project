// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SagaHpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/SagaCharacterWidgetInterface.h"

USagaHpBarWidget::USagaHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void USagaHpBarWidget::NativeConstruct() //�����ʱ�ȭ�ɶ� ������ �������� ����
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
	ensure(HpProgressBar); //��Ʈ���� �ݵ�� �־�� �ϱ⿡ ensure�� �ۼ��Ͽ���

	ISagaCharacterWidgetInterface* CharacterWidget = Cast<ISagaCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void USagaHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
	}
}
