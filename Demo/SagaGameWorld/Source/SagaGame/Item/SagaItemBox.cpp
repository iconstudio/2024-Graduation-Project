// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SagaItemBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/SagaCollision.h"
#include "Interface/SagaCharacterItemInterface.h"

ASagaItemBox::ASagaItemBox()
{
 	
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));

    RootComponent = Trigger;
    Mesh->SetupAttachment(Trigger);
    Effect->SetupAttachment(Trigger);

    Trigger->SetCollisionProfileName(CPROFILE_SAGATRIGGER);
    Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));//ũ�� ���� (�����ۺ��� �°� �����ʿ�)
    Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASagaItemBox::OnOverlapBegin); //�������Ʈ������ ���� �����ϱ⶧���� ���⿡ ���� �Լ��� UFUNCTION �����ʿ�.

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Map/Item/Cube.Cube'"));
    if (BoxMeshRef.Object)
    {
        Mesh->SetStaticMesh(BoxMeshRef.Object);
    }
    Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
    Mesh->SetCollisionProfileName(TEXT("NoCollision"));

    static ConstructorHelpers::FObjectFinder<UParticleSystem> EffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/Effect/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
    if (EffectRef.Object)
    {
        Effect->SetTemplate(EffectRef.Object);
        Effect->bAutoActivate = false; //�ٷ� �ߵ����� �ʵ���
    }
}

void ASagaItemBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
    //������ ȹ�� ���� �� ȹ���� Actor���� TakeItem()�Լ��� ȣ���ϵ��� �Ѵ�.

    if (nullptr == Item) //�������� ��
    {
        Destroy();
        return;
    }

    ISagaCharacterItemInterface* OverlappingPawn = Cast<ISagaCharacterItemInterface>(OtherActor);
    if (OverlappingPawn)
    {
        OverlappingPawn->TakeItem(Item);
    }

    Effect->Activate(true);
    Mesh->SetHiddenInGame(true);
    SetActorEnableCollision(false); //�� �浹�ϸ� �ȵǴϱ� ��Ȱ��ȭ
    Effect->OnSystemFinished.AddDynamic(this, &ASagaItemBox::OnEffectFinished); //����Ʈ ������ �ߵ� delegate
}

void ASagaItemBox::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
    Destroy();
}
