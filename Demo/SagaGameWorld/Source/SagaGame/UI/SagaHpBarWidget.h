// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SagaUserWidget.h"
#include "SagaHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAGAGAME_API USagaHpBarWidget : public USagaUserWidget
{
	GENERATED_BODY()
	
public:
	USagaHpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;
};
