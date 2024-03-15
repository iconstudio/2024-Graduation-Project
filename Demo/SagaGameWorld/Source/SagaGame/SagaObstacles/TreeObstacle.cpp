// Fill out your copyright notice in the Description page of Project Settings.


#include "SagaObstacles/TreeObstacle.h"

// Sets default values
ATreeObstacle::ATreeObstacle()
{
    // 컴포넌트 초기화
    HealthComponent = CreateDefaultSubobject<UObstacleHPComponent>(TEXT("HealthComponent"));
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent")); //메시 지정

    static ConstructorHelpers::FObjectFinder<UStaticMesh> TreeMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Map/MapObstacles/Tree/cartoon_lowpoly_trees_fbx_Tree_2.cartoon_lowpoly_trees_fbx_Tree_2'"));
    if (TreeMeshRef.Object)
    {
        MeshComponent->SetStaticMesh(TreeMeshRef.Object);
    }

    // 메쉬 컴포넌트를 RootComponent로 설정
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

    // HealthComponent가 있는지 확인하고, 있다면 TakeDamage 호출
    if (HealthComponent)
    {
        HealthComponent->TakeDamage(DamageAmount);
    }

    return DamageApplied;
}