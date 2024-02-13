// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SagaItemData.generated.h"


//아이템 종류
UENUM(BlueprintType)
enum class EItemType : uint8
{
	EnergyDrink = 0,
	Gumball,
	Weapon1
};


USTRUCT(BlueprintType)
struct FSagaInventoryItem //아이템 및 수량 저장할 수 있는 구조체 정의
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
