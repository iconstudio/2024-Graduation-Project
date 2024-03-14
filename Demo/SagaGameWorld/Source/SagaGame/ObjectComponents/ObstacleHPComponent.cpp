// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectComponents/ObstacleHPComponent.h"

// Sets default values for this component's properties
UObstacleHPComponent::UObstacleHPComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UObstacleHPComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UObstacleHPComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObstacleHPComponent::TakeDamage(float DamageAmount)
{
	Health -= DamageAmount;
	CheckDeath();
}

void UObstacleHPComponent::CheckDeath()
{
	if (Health <= 0)
	{
		AActor* ThisObestacleActor = GetOwner();
		if (ThisObestacleActor)
		{
			ThisObestacleActor->SetActorEnableCollision(false);
			ThisObestacleActor->FindComponentByClass<UPrimitiveComponent>()->SetSimulatePhysics(true);

			// Ÿ�̸� ����
			GetWorld()->GetTimerManager().SetTimer(DestructionTimerHandle, this, &UObstacleHPComponent::HandleDestruction, DestructionDelay);
		}
	}
}

void UObstacleHPComponent::HandleDestruction()
{
	// ī���� ��Ʈ���� ���� ���� ���� �Լ� ȣ��
	RemoveDestructionPieces();
}

void UObstacleHPComponent::RemoveDestructionPieces()
{
	AActor* ThisObestacleActor = GetOwner();
	if (ThisObestacleActor)
	{
		ThisObestacleActor->Destroy();
	}
}
