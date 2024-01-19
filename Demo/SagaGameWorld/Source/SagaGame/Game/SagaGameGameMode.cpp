// Copyright Epic Games, Inc. All Rights Reserved.

#include "SagaGameGameMode.h"
#include "SagaGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SagaGame.h"

ASagaGameGameMode::ASagaGameGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/SagaGame.SagaPlayerController")); //헤더파일불필요
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}

void ASagaGameGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	SAGA_Log(LogSagaNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	SAGA_Log(LogSagaNetwork, Log, TEXT("%s"), TEXT("End"));
}

APlayerController* ASagaGameGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	SAGA_Log(LogSagaNetwork, Log, TEXT("%s"), TEXT("Begin"));
	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	SAGA_Log(LogSagaNetwork, Log, TEXT("%s"), TEXT("End"));
	return NewPlayerController;
}

void ASagaGameGameMode::PostLogin(APlayerController* NewPlayer)
{
	SAGA_Log(LogSagaNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PostLogin(NewPlayer);
	SAGA_Log(LogSagaNetwork, Log, TEXT("%s"), TEXT("End"));
}

void ASagaGameGameMode::StartPlay()
{
	SAGA_Log(LogSagaNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::StartPlay();
	SAGA_Log(LogSagaNetwork, Log, TEXT("%s"), TEXT("End"));
}
