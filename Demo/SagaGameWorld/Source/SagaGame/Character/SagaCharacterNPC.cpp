// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SagaCharacterNPC.h"
#include "Character/SagaCharacterPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"


ASagaCharacterNPC::ASagaCharacterNPC()
{

}

void ASagaCharacterNPC::ShowInteractionPrompt(bool bShow)
{
    if (NPCInteractionTEXTWidget)
    {
        NPCInteractionTEXTWidget->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void ASagaCharacterNPC::OnPlayerEnterRange()
{
    if (NPCInteractionTEXTWidget)
    {
        NPCInteractionTEXTWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void ASagaCharacterNPC::OnPlayerExitRange()
{
    if (NPCInteractionTEXTWidget)
    {
        NPCInteractionTEXTWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void ASagaCharacterNPC::SetDead() //NPC ���ó��
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

    // �ݸ��� ����
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASagaCharacterNPC::OnOverlapBegin);
    GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ASagaCharacterNPC::OnOverlapEnd);

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
    // �÷��̾���� ������ ����
    ASagaCharacterPlayer* Player = Cast<ASagaCharacterPlayer>(OtherActor);
    if (Player)
    {
        // �÷��̾ ��ó�� ����
        Player->SetNearbyNPC(this);
    }
}

void ASagaCharacterNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // �÷��̾ �־���
    ASagaCharacterPlayer* Player = Cast<ASagaCharacterPlayer>(OtherActor);
    if (Player)
    {
        Player->SetNearbyNPC(nullptr);
    }
}
