#include "Saga/GameMode/SagaGameModeBase.h"

ASagaGameModeBase::ASagaGameModeBase(const FObjectInitializer& intializer)
	: AGameModeBase(intializer), ISagaNetworkView()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void
ASagaGameModeBase::OnConnected_Implementation()
{
}

void
ASagaGameModeBase::OnFailedToConnect_Implementation(int32 reason)
{

}

void
ASagaGameModeBase::OnDisconnected_Implementation()
{
}

void
ASagaGameModeBase::OnRespondVersion_Implementation(const FString& version_string)
{
}

void
ASagaGameModeBase::OnUpdateRoomList_Implementation(const TArray<FSagaVirtualRoom>& list)
{
}

void
ASagaGameModeBase::OnUpdateMembers_Implementation(const TArray<FSagaVirtualUser>& list)
{
}
