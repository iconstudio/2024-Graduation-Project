// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SagaComboActionData.generated.h"

/**
 * 
 */
UCLASS()
class SAGAGAME_API USagaComboActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	USagaComboActionData();

	UPROPERTY(EditAnywhere, Category = Name)
	FString MontageSectionNamePrefix; //��Ÿ�� ���� �̸� ����

	UPROPERTY(EditAnywhere, Category = Name)
	uint8 MaxComboCount;			  //�޺��׼� �� ����

	UPROPERTY(EditAnywhere, Category = Name)
	float FrameRate;				//������ ���� ����ӵ�. ��Ȯ�� Ÿ�ֿ̹� üũ�ǵ���.

	UPROPERTY(EditAnywhere, Category = ComboData)
	TArray<float> EffectiveFrameCount; //�Է��� ������ �ԷµȰ��� �����ϴ� ������
};
