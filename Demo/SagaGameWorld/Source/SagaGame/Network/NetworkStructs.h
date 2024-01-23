// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkStructs.generated.h"
/**
 * 
 */
class SAGAGAME_API NetworkStructs
{
public:
	NetworkStructs();
	~NetworkStructs();
};

USTRUCT(Atomic, BlueprintType)
struct FClientNetworkStruct
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector pos{};
};