// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SagaGameWorldCharacter.h"
#include "PlayerCharacterFactory.generated.h"

/**
 * 
 */
UCLASS()
class SAGAGAMEWORLD_API UPlayerCharacterFactory : public UObject
{
	GENERATED_BODY()

public:

	// �÷��̾� ĳ���� ����
	ASagaGameWorldCharacter* CreateCharacter(int32 PlayerID, FVector Location);

	
};
