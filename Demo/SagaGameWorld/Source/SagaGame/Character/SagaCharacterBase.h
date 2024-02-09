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
	virtual void SetCharacterControlData(const class USagaCharacterControlData* CharacterControlData); //캐릭터컨트롤데이터에셋을 입력으로 받음

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class USagaCharacterControlData*> CharacterControlManager;

//Animation Mantage 관련
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USagaComboActionData> ComboActionData;

	void ProcessComboCommand();

	//몽타주 시작될때 호출하는 함수
	void ComboActionBegin();

	//몽타주 모두 종료시 호출
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

	//타이머 발동
	void SetComboCheckTimer();

	void ComboCheck();

	//현재 콤보가 어디까지 진행되었는지 저장을 위함
	int32 CurrentCombo = 0;

	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;

	//공격 hit 부분
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

	//아이템관련
protected:

	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemActions; //함수들이 바인딩 된다.

	virtual void TakeItem(class USagaItemData* InItemData) override;
	virtual void DrinkEnergyDrink(class USagaItemData* InItemData);
	virtual void EquipWeapons(class USagaItemData* InItemData);
	virtual void InstallGumball(class USagaItemData* InItemData);

};
