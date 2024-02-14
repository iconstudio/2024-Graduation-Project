// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SagaUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAGAGAME_API USagaUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//액터값 가져오기
	FORCEINLINE void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor")
	TObjectPtr<AActor>OwningActor;//액터정보보관
};
