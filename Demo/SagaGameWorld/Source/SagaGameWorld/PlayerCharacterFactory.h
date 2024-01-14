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

	// 플레이어 캐릭터 생성
	ASagaGameWorldCharacter* CreateCharacter(int32 PlayerID, FVector Location);

	
};
