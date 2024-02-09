// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/SagaAttackAnimationInterface.h"
#include "Interface/SagaCharacterItemInterface.h"
#include "SagaCharacterBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSagaCharacter, Log, All);


UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class USagaItemData*);
USTRUCT(BlueprintType)
struct FTakeItemDelegateWrapper
{
	GENERATED_BODY()

	FTakeItemDelegateWrapper() {};
	FTakeItemDelegateWrapper(const FOnTakeItemDelegate& InItemDelegate) : ItemDelegate(InItemDelegate) {};
	FOnTakeItemDelegate ItemDelegate;
};


UCLASS()
class SAGAGAME_API ASagaCharacterBase : public ACharacter, public ISagaAttackAnimationInterface, public ISagaCharacterItemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASagaCharacterBase();

protected:
	virtual void SetCharacterControlData(const class USagaCharacterControlData* CharacterControlData); //ĳ������Ʈ�ѵ����Ϳ����� �Է����� ����

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class USagaCharacterControlData*> CharacterControlManager;

//Animation Mantage ����
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USagaComboActionData> ComboActionData;

	void ProcessComboCommand();

	//��Ÿ�� ���۵ɶ� ȣ���ϴ� �Լ�
	void ComboActionBegin();

	//��Ÿ�� ��� ����� ȣ��
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

	//Ÿ�̸� �ߵ�
	void SetComboCheckTimer();

	void ComboCheck();

	//���� �޺��� ������ ����Ǿ����� ������ ����
	int32 CurrentCombo = 0;

	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;

	//���� hit �κ�
protected:
	virtual void AttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	virtual void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 5.0f;

protected:
	float WalkSpeed = 500.f;
	float SprintSpeed = 1000.0f;

	//�����۰���
protected:

	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemActions; //�Լ����� ���ε� �ȴ�.

	virtual void TakeItem(class USagaItemData* InItemData) override;
	virtual void DrinkEnergyDrink(class USagaItemData* InItemData);
	virtual void EquipWeapons(class USagaItemData* InItemData);
	virtual void InstallGumball(class USagaItemData* InItemData);

};
