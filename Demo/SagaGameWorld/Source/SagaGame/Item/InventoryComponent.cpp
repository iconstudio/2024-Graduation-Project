// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/InventoryComponent.h"
#include "Item/Items.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	Capacity = 20;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}

bool UInventoryComponent::AddItem(UItems* Item)
{
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}
	Item->OwningInventory = this;
	Item->World = GetWorld();	
	Items.Add(Item);

	//UI ������Ʈ
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::RemoveItem(UItems* Item)
{
	return false;
}
