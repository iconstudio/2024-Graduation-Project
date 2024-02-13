// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "Character/SagaCharacterPlayer.h"
#include "Items.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class SAGAGAME_API UItems : public UObject
{
	GENERATED_BODY()
	
public:
	UItems();

	virtual class UWorld* GetWorld() const { return World; };


	UPROPERTY(Transient) //�������� � ���忡 �־�����
	class UWorld* World;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item)
	FText UseActionText; //������ ���� �ؽ�Ʈ (���, ��ġ ���� ��)

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item)
	class UStaticMesh* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
	class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item)
	FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item, meta = (MultiLine = true)) //(MultiLine = true)�� ���� �� �� �߰� ����
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item, meta = (ClampMin = 0.0)) //�κ��丮 ��������(�����ۺ� ����) ����ҰŸ� ���α�
	float Weight;

	UPROPERTY()
	class UInventoryComponent* OwningInventory;

	virtual void Use(class ASagaCharacterPlayer* Character) PURE_VIRTUAL(UItems, );

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class ASagaCharacterPlayer* Character);
};
