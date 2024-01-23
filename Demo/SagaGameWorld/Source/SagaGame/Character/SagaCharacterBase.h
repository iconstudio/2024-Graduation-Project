// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SagaCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

UCLASS()
class SAGAGAME_API ASagaCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASagaCharacterBase();

protected:
	virtual void SetCharacterControlData(const class USagaCharacterControlData* CharacterControlData); //캐릭터컨트롤데이터에셋을 입력으로 받음

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class USagaCharacterControlData*> CharacterControlManager;
};
