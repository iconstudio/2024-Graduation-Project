// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SagaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SAGAGAME_API ASagaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASagaPlayerController();

protected:
	virtual void BeginPlay() override;

protected:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Catetory = HUD)
	TSubclassOf<class USAGAHUDWidget> SagaWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Catetory = HUD)
	TObjectPtr<class USG*/

	
};
