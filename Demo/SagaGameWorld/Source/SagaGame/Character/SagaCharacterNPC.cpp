// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SagaCharacterNPC.h"

ASagaCharacterNPC::ASagaCharacterNPC()
{

}

void ASagaCharacterNPC::SetDead()
{
	Super::SetDead();
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}
