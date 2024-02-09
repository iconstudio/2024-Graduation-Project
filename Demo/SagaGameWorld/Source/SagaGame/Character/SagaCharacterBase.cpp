// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SagaCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SagaCharacterControlData.h"
#include "Animation/AnimMontage.h"
#include "SagaComboActionData.h"
#include "Physics/SagaCollision.h"
#include "Engine/DamageEvents.h"
#include "Item/SagaWeaponItemData.h"

DEFINE_LOG_CATEGORY(LogSagaCharacter);

// Sets default values
ASagaCharacterBase::ASagaCharacterBase()
{
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_SAGACAPSULE);

    //������
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    //�޽�
    GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
    GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
    if (CharacterMeshRef.Object)
    {
        GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
    }

    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Animation/SAGABP_Character.SAGABP_Character_C"));
    if (AnimInstanceClassRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
    }

    //������ �ΰ��� ��Ʈ�� �����͵��� Map�� �߰�
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

    //Combo
    static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_ComboAttack.AM_ComboAttack'"));
    if (ComboActionMontageRef.Object)
    {
        ComboActionMontage = ComboActionMontageRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<USagaComboActionData> ComboActionDataRef(TEXT("/Script/SagaGame.SagaComboActionData'/Game/CharacterAction/Saga_ComboAttack.Saga_ComboAttack'"));
    if (ComboActionDataRef.Object)
    {
        ComboActionData = ComboActionDataRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT(""));
    if (DeadMontageRef.Object)
    {
        DeadMontage = DeadMontageRef.Object; //
    }

    //������ �׼�
    TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ASagaCharacterBase::DrinkEnergyDrink)));
    TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ASagaCharacterBase::InstallGumball)));
    TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &ASagaCharacterBase::EquipWeapons)));

    //���� ������Ʈ(Weapon Component)
    Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
    Weapon->SetupAttachment(GetMesh(), TEXT("hand_rSocket")); //ĳ������ Ư�� ���� �׻� �����Ǿ� ���ƴٴ� �� �ֵ��� �����̸��� �������ش�.
    //ĳ���� �ּ¿� ���� �̸��� �����Ǿ� �־�� �Ѵ�.

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

void ASagaCharacterBase::ProcessComboCommand() //�̰Ͱ� SagaCharacterPlayer�� Attack�Լ��� �����ǵ��� Attack�Լ��� �ۼ�
{
    if (CurrentCombo == 0)
    {
        ComboActionBegin();
        return;
    }

    //�Է��� ���� ��
    if (!ComboTimerHandle.IsValid()) //Ÿ�̸Ӱ� ���� �ȵǾ������� �Է��� ���ö����� �̹� Ÿ�̸Ӱ� �ߵ��Ǿ� �ñ⸦ ���ưų� ���̻� ������ �ʿ䰡 ���ٴ� ��
    {
        HasNextComboCommand = false;
    }
    else
    {
        HasNextComboCommand = true;
    }
}

void ASagaCharacterBase::ComboActionBegin()
{
    //���� �޺� ����
    CurrentCombo = 1;

    //Movement ����
    //GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None); //None���� ���� ��--> �����ϴ� ���� �̵��Ұ�

    //�ִϸ��̼� ����
    const float AttackSpeedRate = 1.0f;
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    AnimInstance->Montage_Play(ComboActionMontage, AttackSpeedRate);

    FOnMontageEnded EndDelegate;
    EndDelegate.BindUObject(this, &ASagaCharacterBase::ComboActionEnd);
    AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

    ComboTimerHandle.Invalidate();
    SetComboCheckTimer();
}

void ASagaCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
    ensure(CurrentCombo != 0);// current combo�� 0�� �ƴ����� �˻�
    CurrentCombo = 0;
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ASagaCharacterBase::SetComboCheckTimer()
{
    int32 ComboIndex = CurrentCombo - 1;
    ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));

    const float AttackSpeedRate = 1.0f;
    float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;
    if (ComboEffectiveTime > 0.0f)
    {
        GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ASagaCharacterBase::ComboCheck, ComboEffectiveTime, false);
    }
}

void ASagaCharacterBase::ComboCheck()
{
    ComboTimerHandle.Invalidate();
    if (HasNextComboCommand) //Ÿ�̸� �ߵ� �� �Է��� ���� HasNextComboCommand�� true���� �Ǹ� ���� �������� �Ѿ��
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

        CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount); //������ �޺��� ����� �ʵ���.
        FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);
        AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage);
        SetComboCheckTimer();
        HasNextComboCommand = false;
    }
}

void ASagaCharacterBase::AttackHitCheck() //trace Ȱ���Ͽ� ��ü�� ���� �浹�Ǵ��� �˻��ϴ� ���� ����
{
    FHitResult OutHitResult;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);//false-> ������ �浹üũ ������, this-> ������ ���ʹ� �ڱ� �ڽŻ��̶� this ���

    const float AttackRange = 40.0f;
    const float AttackRadius = 50.0f;
    const float AttackDamage = 30.0f;
    const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
    const FVector End = Start + GetActorForwardVector() * AttackRange;

    bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_SAGAACTION, FCollisionShape::MakeSphere(AttackRadius), Params);
    if (HitDetected)
    {
        FDamageEvent DamageEvent;
        OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
    }

#if ENABLE_DRAW_DEBUG

    FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
    float CapsuleHalfHeight = AttackRange * 0.5f;
    FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
    DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);

#endif
}

float ASagaCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    SetDead();

    return DamageAmount;
}

void ASagaCharacterBase::SetDead()
{
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
    PlayDeadAnimation();
    SetActorEnableCollision(false);
}

void ASagaCharacterBase::PlayDeadAnimation()
{
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    AnimInstance->StopAllMontages(0.0f);
    AnimInstance->Montage_Play(DeadMontage, 1.0f);
}

void ASagaCharacterBase::TakeItem(USagaItemData* InItemData)
{
    if (InItemData)
    {
        TakeItemActions[(uint8)InItemData->Type].ItemDelegate.ExecuteIfBound(InItemData); //ExecuteIfBound�Լ��� InItemData�� �Ѱ��ش�.
    }
}

void ASagaCharacterBase::DrinkEnergyDrink(USagaItemData* InItemData)
{
    UE_LOG(LogSagaCharacter, Log, TEXT("Drink EnergyDrink"));
}

void ASagaCharacterBase::EquipWeapons(USagaItemData* InItemData)
{
    USagaWeaponItemData* WeaponItemData = Cast<USagaWeaponItemData>(InItemData);
    if (WeaponItemData)
    {
        if (WeaponItemData->WeaponMesh.IsPending()) //���� �ε���� �ʾҴٸ�
        {
            WeaponItemData->WeaponMesh.LoadSynchronous();
        }
        Weapon->SetSkeletalMesh(WeaponItemData->WeaponMesh.Get());
    }
    /*if (InItemData)
    {
        Weapon->SetSkeletalMesh(WeaponItemData->WeaponMesh);
    }*/
}

void ASagaCharacterBase::InstallGumball(USagaItemData* InItemData)
{
    UE_LOG(LogSagaCharacter, Log, TEXT("Install Gumball"));
}
