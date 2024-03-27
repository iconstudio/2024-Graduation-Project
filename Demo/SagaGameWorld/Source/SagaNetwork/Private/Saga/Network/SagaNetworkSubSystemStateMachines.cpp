#include "Saga/Network/SagaNetworkSubSystem.h"
#include "Delegates/Delegate.h"

#include "Saga/Network/SagaNetworkSettings.h"

USagaNetworkSubSystem::USagaNetworkSubSystem()
	: UGameInstanceSubsystem()
	, localUserId(-1), localUserName(), currentRoomId(), currentRoomTitle()
	, OnNetworkInitialized(), OnConnected(), OnFailedToConnect(), OnDisconnected()
	, OnRoomCreated(), OnJoinedRoom(), OnLeftRoomBySelf(), OnLeftRoom()
	, OnRespondVersion(), OnUpdateRoomList(), OnUpdateMembers()
	, OnTeamChanged()
	, OnGetPreparedGame(), OnStartGame()
	, OnUpdatePosition()
	, TaskCompletionEvents()
	, rpcDatabase()
	, clientSocket(nullptr), netWorker(nullptr)
	, everyUsers(), wasUsersUpdated(true)
	, everyRooms(), wasRoomsUpdated(true)
{}

void
USagaNetworkSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	OnNetworkInitialized.AddDynamic(this, &USagaNetworkSubSystem::OnNetworkInitialized_Implementation);
	OnConnected.AddDynamic(this, &USagaNetworkSubSystem::OnConnected_Implementation);
	OnFailedToConnect.AddDynamic(this, &USagaNetworkSubSystem::OnFailedToConnect_Implementation);
	OnDisconnected.AddDynamic(this, &USagaNetworkSubSystem::OnDisconnected_Implementation);
	OnRoomCreated.AddDynamic(this, &USagaNetworkSubSystem::OnRoomCreated_Implementation);
	OnJoinedRoom.AddDynamic(this, &USagaNetworkSubSystem::OnJoinedRoom_Implementation);
	OnLeftRoomBySelf.AddDynamic(this, &USagaNetworkSubSystem::OnLeftRoomBySelf_Implementation);
	OnLeftRoom.AddDynamic(this, &USagaNetworkSubSystem::OnLeftRoom_Implementation);
	OnRespondVersion.AddDynamic(this, &USagaNetworkSubSystem::OnRespondVersion_Implementation);
	OnUpdateRoomList.AddDynamic(this, &USagaNetworkSubSystem::OnUpdateRoomList_Implementation);
	OnUpdateMembers.AddDynamic(this, &USagaNetworkSubSystem::OnUpdateMembers_Implementation);
	OnTeamChanged.AddDynamic(this, &USagaNetworkSubSystem::OnTeamChanged_Implementation);
	OnFailedToStartGame.AddDynamic(this, &USagaNetworkSubSystem::OnFailedToStartGame_Implementation);
	OnGetPreparedGame.AddDynamic(this, &USagaNetworkSubSystem::OnGetPreparedGame_Implementation);
	OnStartGame.AddDynamic(this, &USagaNetworkSubSystem::OnStartGame_Implementation);
	OnUpdatePosition.AddDynamic(this, &USagaNetworkSubSystem::OnUpdatePosition_Implementation);

	everyUsers.Reserve(100);
	everyRooms.Reserve(100);

	if (InitializeNetwork_Implementation())
	{
		BroadcastOnNetworkInitialized();
	}
	else
	{
		BroadcastOnFailedToInitializeNetwork();
	}
}

void
USagaNetworkSubSystem::Deinitialize()
{
	Super::Deinitialize();

	if constexpr (not saga::IsOfflineMode)
	{
		if (IsSocketAvailable())
		{
			Close();
		}
		else
		{
			UE_LOG(LogSagaNetwork, Warning, TEXT("The network subsystem has been destroyed."));
		}
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("The network subsystem has been destroyed. (Offline Mode)"));
	}
}

bool
USagaNetworkSubSystem::ShouldCreateSubsystem(UObject* Outer)
const
{
	if (Outer)
	{
		// https://forums.unrealengine.com/t/solved-getworld-from-static-function-without-pass-an-object/245939
		//UWorld* world = GEngine->GameViewport->GetWorld();
		//float TimeSinceCreation = world->GetFirstPlayerController()->GetGameTimeSinceCreation();

		FString name{ 20, TEXT("") };
		Outer->GetWorld()->GetCurrentLevel()->GetName(name);

		static const FString non_network_levels[] =
		{
			TEXT("InitializationLevel")
		};

		for (auto& non_network_level : non_network_levels)
		{
			if (name == non_network_level)
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool
USagaNetworkSubSystem::Close()
{
	if constexpr (not saga::IsOfflineMode)
	{
		if (not IsSocketAvailable())
		{
			UE_LOG(LogSagaNetwork, Warning, TEXT("The socket of client is null."));
			return true;
		}
		else if (not IsConnected())
		{
			UE_LOG(LogSagaNetwork, Warning, TEXT("The network subsystem had been closed."));

			return CloseNetwork_Implementation();
		}
		else
		{
			UE_LOG(LogSagaNetwork, Warning, TEXT("Closing the network subsystem..."));

			return CloseNetwork_Implementation();
		}
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("Closing the network subsystem... (Offline Mode)"));
		return true;
	}
}
