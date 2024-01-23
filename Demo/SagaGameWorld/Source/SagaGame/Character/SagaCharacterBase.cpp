// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SagaCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SagaCharacterControlData.h"

// Sets default values
ASagaCharacterBase::ASagaCharacterBase()
{
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

    //움직임
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    //메시
    GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple'"));
    if (CharacterMeshRef.Object)
    {
        GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Characters/Mannequins/Animations/ABP_Quinn.ABP_Quinn_C"));
    if (AnimInstanceClassRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
    }

    //생성한 두가지 컨트롤 데이터들을 Map에 추가
    static ConstructorHelpers::FObjectFinder<USagaCharacterControlData> SoulderDataRef(TEXT("/Script/SagaGame.SagaCharacterControlData'/Game/CharacterControl/SagaControl_Shoulder.SagaControl_Shoulder'"));
    if (SoulderDataRef.Object)
    {
        CharacterControlManager.Add(ECharacterControlType::Shoulder, SoulderDataRef.Object);
    }
    static ConstructorHelpers::FObjectFinder<USagaCharacterControlData> QuaterDataRef(TEXT("/Script/SagaGame.SagaCharacterControlData'/Game/CharacterControl/SagaControl_Quater.SagaControl_Quater'"));
    if (QuaterDataRef.Object)
    {
        CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataRef.Object);
    }

}

void ASagaCharacterBase::SetCharacterControlData(const USagaCharacterControlData* CharacterControlData)
{
    //Pawn
    bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

    // CharacterMovement
    GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
    GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
    GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
}
