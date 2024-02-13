// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EnergyDrinkItem.h"
#include "Character/SagaCharacterPlayer.h"

void UEnergyDrinkItem::Use(ASagaCharacterPlayer* Character)
{
	if (Character)
	{
		Character->PlayerHP += HealAmount;
	}
}
