// Fill out your copyright notice in the Description page of Project Settings.


#include "SagaObstacles/TreeObstacle.h"

// Sets default values
ATreeObstacle::ATreeObstacle()
{
    // ������Ʈ �ʱ�ȭ
    HealthComponent = CreateDefaultSubobject<UObstacleHPComponent>(TEXT("HealthComponent"));
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> TreeMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Map/MapObstacles/Tree/cartoon_lowpoly_trees_fbx_Tree_2.cartoon_lowpoly_trees_fbx_Tree_2'"));
    if (TreeMeshRef.Object)
    {
        MeshComponent->SetStaticMesh(TreeMeshRef.Object);
    }

    // �޽� ������Ʈ�� RootComponent�� ����
    RootComponent = MeshComponent;

    MeshComponent->SetCollisionProfileName(TEXT("SagaCapsule"));
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);


    SetActorScale3D(FVector(8.0f, 8.0f, 8.0f));

}

// Called when the game starts or when spawned
void ATreeObstacle::BeginPlay()
{
	Super::BeginPlay();

	
}

float ATreeObstacle::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    // HealthComponent�� �ִ��� Ȯ���ϰ�, �ִٸ� TakeDamage ȣ��
    if (HealthComponent)
    {
        HealthComponent->TakeDamage(DamageAmount);
    }

    return DamageApplied;
}