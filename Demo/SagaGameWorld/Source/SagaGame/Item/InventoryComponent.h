// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

//�������Ʈ�� UI�� ������Ű�� ���� ���ε��Ұ���.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAGAGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	virtual void BeginPlay() override;

	bool AddItem(class UItems* Item);
	bool RemoveItem(class UItems* Item);

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UItems*> DefaultItems;

	UPROPERTY(EditDefaultsOnly, Category = Inventory) //���� ������ �Ѱ�ġ
	int32 Capacity;

	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Item) //���� ������ �ִ� �����۵�
	TArray<class UItems*> Items;

		
};
