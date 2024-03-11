// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SagaItemData.generated.h"


//������ ����
UENUM(BlueprintType)
enum class EItemType : uint8
{
	EnergyDrink = 0,
	Gumball,
	Weapon1
};


USTRUCT(BlueprintType)
struct FSagaInventoryItem //������ �� ���� ������ �� �ִ� ����ü ����
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USagaItemData* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;
};



/**
 * 
 */
UCLASS()
class SAGAGAME_API USagaItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EItemType Type;
};
