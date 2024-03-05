// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SagaCharacterNPC.h"
#include "Character/SagaCharacterPlayer.h"
#include "Components/CapsuleComponent.h"


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

void ASagaCharacterNPC::BeginPlay()
{
    Super::BeginPlay();

    // 콜리전 설정
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASagaCharacterNPC::OnOverlapBegin);
    GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ASagaCharacterNPC::OnOverlapEnd);
}

void ASagaCharacterNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 플레이어와의 오버랩 감지
    ASagaCharacterPlayer* Player = Cast<ASagaCharacterPlayer>(OtherActor);
    if (Player)
    {
        // 플레이어가 근처에 있음
        Player->SetNearbyNPC(this);
    }
}

void ASagaCharacterNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // 플레이어가 멀어짐
    ASagaCharacterPlayer* Player = Cast<ASagaCharacterPlayer>(OtherActor);
    if (Player)
    {
        Player->SetNearbyNPC(nullptr);
    }
}
