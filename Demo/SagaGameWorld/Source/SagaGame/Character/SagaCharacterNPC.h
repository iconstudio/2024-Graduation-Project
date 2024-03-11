// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SagaCharacterBase.h"
#include "Interface/InteractionInterface.h"
#include "SagaCharacterNPC.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SAGAGAME_API ASagaCharacterNPC : public ASagaCharacterBase, public IInteractionInterface
{
	GENERATED_BODY()
public:
	ASagaCharacterNPC();

	void ShowInteractionPrompt(bool bShow);

	void OnPlayerEnterRange();

	void OnPlayerExitRange();

	virtual void InteractWithMe() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> NPCInteractionWidget;

	UPROPERTY()
	UUserWidget* NPCInteractionTEXTWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
	UCapsuleComponent* NPCInteractionCapsule;

protected:
	void SetDead() override;
	virtual void BeginPlay() override;
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
