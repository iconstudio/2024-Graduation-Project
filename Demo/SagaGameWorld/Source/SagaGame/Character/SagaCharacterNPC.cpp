﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SagaCharacterNPC.h"
#include "Character/SagaCharacterPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"


ASagaCharacterNPC::ASagaCharacterNPC()
{
    NPCInteractionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractionCapsule"));
    NPCInteractionCapsule->SetupAttachment(RootComponent);
    NPCInteractionCapsule->SetCapsuleSize(150, 400);
    NPCInteractionCapsule->SetCollisionProfileName(TEXT("Trigger"));
}

void ASagaCharacterNPC::InteractWithMe()
{
    UE_LOG(LogTemp, Warning, TEXT("Interacted with NPC!!"));
}

//void ASagaCharacterNPC::ShowInteractionPrompt(bool bShow)
//{
//    if (NPCInteractionTEXTWidget)
//    {
//        NPCInteractionTEXTWidget->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
//    }
//}
//
//void ASagaCharacterNPC::OnPlayerEnterRange()
//{
//    if (NPCInteractionTEXTWidget)
//    {
//        NPCInteractionTEXTWidget->SetVisibility(ESlateVisibility::Visible);
//    }
//}
//
//void ASagaCharacterNPC::OnPlayerExitRange()
//{
//    if (NPCInteractionTEXTWidget)
//    {
//        NPCInteractionTEXTWidget->SetVisibility(ESlateVisibility::Hidden);
//    }
//}

void ASagaCharacterNPC::SetDead() //NPC 사망처리
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

    NPCInteractionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ASagaCharacterNPC::OnOverlapBegin);
    NPCInteractionCapsule->OnComponentEndOverlap.AddDynamic(this, &ASagaCharacterNPC::OnOverlapEnd);


    if (NPCInteractionWidget)
    {
        NPCInteractionTEXTWidget = CreateWidget<UUserWidget>(GetWorld(), NPCInteractionWidget);
        if (NPCInteractionTEXTWidget != nullptr)
        {
            NPCInteractionTEXTWidget->AddToViewport();
            NPCInteractionTEXTWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
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
