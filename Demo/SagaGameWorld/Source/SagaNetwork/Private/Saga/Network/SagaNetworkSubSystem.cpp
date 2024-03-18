#include "Saga/Network/SagaNetworkSubSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Delegates/Delegate.h"
#include "Delegates/DelegateInstanceInterface.h"
#include "UObject/Object.h"
#include "Sockets.h"

#include "Saga/Network/SagaNetworkSettings.h"
#include "Saga/Network/SagaNetworkSystem.h"

USagaNetworkSubSystem::USagaNetworkSubSystem()
	: UGameInstanceSubsystem()
	, OnNetworkInitialized(), OnConnected(), OnFailedToConnect(), OnDisconnected()
	, OnRoomCreated(), OnJoinedRoom(), OnLeftRoomBySelf(), OnLeftRoom()
	, OnRespondVersion(), OnUpdateRoomList(), OnUpdateMembers()
	, OnUpdatePosition()
{}

bool
USagaNetworkSubSystem::Awake()
{
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
	OnUpdatePosition.AddDynamic(this, &USagaNetworkSubSystem::OnUpdatePosition_Implementation);

	if (saga::USagaNetwork::InitializeNetwork())
	{
		UE_LOG(LogNet, Log, TEXT("The network system is initialized."));
		BroadcastOnNetworkInitialized();

		return true;
	}
	else
	{
		UE_LOG(LogNet, Error, TEXT("Cannot initialize the network system."));
		BroadcastOnFailedToInitializeNetwork();

		return false;
	}
}

bool
USagaNetworkSubSystem::Start(const FString& nickname)
{
	if constexpr (not saga::IsOfflineMode)
	{
		if (not saga::USagaNetwork::IsSocketAvailable())
		{
			if (Awake())
			{
				UE_LOG(LogNet, Warning, TEXT("The network system was not initialized."));
			}
			else
			{
				return false;
			}
		}

		saga::USagaNetwork::LocalUserName(nickname);

		UE_LOG(LogNet, Log, TEXT("Connecting..."));
		auto connect_r = saga::USagaNetwork::ConnectToServer();
		if (connect_r == ESagaConnectionContract::Success)
		{
			BroadcastOnConnected();
			return true;
		}
		else
		{
			BroadcastOnFailedToConnect(connect_r);
			return false;
		}
	}
	else
	{
		return true;
	}
}

bool
USagaNetworkSubSystem::Destroy()
{
	if constexpr (not saga::IsOfflineMode)
	{
		if (saga::USagaNetwork::IsSocketAvailable())
		{
			UE_LOG(LogNet, Warning, TEXT("Closing network system..."));
			return saga::USagaNetwork::GetLocalSocket().Close();
		}
		else
		{
			UE_LOG(LogNet, Warning, TEXT("The network system have been destroyed."));
			return true;
		}
	}
	else
	{
		UE_LOG(LogNet, Warning, TEXT("The network system have been destroyed. (Offline Mode)"));
		return true;
	}
}

void
USagaNetworkSubSystem::BroadcastOnNetworkInitialized()
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnNetworkInitialized`"));

	if (OnNetworkInitialized.IsBound())
	{
		OnNetworkInitialized.Broadcast(true);
	}
}

void
USagaNetworkSubSystem::BroadcastOnFailedToInitializeNetwork()
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnFailedToInitializeNetwork`"));

	if (OnNetworkInitialized.IsBound())
	{
		OnNetworkInitialized.Broadcast(false);
	}
}

void
USagaNetworkSubSystem::BroadcastOnConnected()
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnConnected`"));

	if (OnConnected.IsBound())
	{
		OnConnected.Broadcast();
	}
}

void
USagaNetworkSubSystem::BroadcastOnFailedToConnect(ESagaConnectionContract reason)
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnFailedToConnect`"));

	if (OnFailedToConnect.IsBound())
	{
		OnFailedToConnect.Broadcast(reason);
	}
}

void
USagaNetworkSubSystem::BroadcastOnDisconnected()
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnDisconnected`"));

	if (OnDisconnected.IsBound())
	{
		OnDisconnected.Broadcast();
	}
}

void
USagaNetworkSubSystem::BroadcastOnRoomCreated(int32 id)
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnRoomCreated`"));

	if (OnRoomCreated.IsBound())
	{
		OnRoomCreated.Broadcast(id);
	}
}

void
USagaNetworkSubSystem::BroadcastOnJoinedRoom(int32 id)
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnJoinedRoom`"));

	if (OnJoinedRoom.IsBound())
	{
		OnJoinedRoom.Broadcast(id);
	}
}

void
USagaNetworkSubSystem::BroadcastOnLeftRoomBySelf()
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnLeftRoomBySelf`"));

	if (OnLeftRoomBySelf.IsBound())
	{
		OnLeftRoomBySelf.Broadcast();
	}
}

void
USagaNetworkSubSystem::BroadcastOnLeftRoom(int32 id)
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnLeftRoom`"));

	if (OnLeftRoom.IsBound())
	{
		OnLeftRoom.Broadcast(id);
	}
}

void
USagaNetworkSubSystem::BroadcastOnRespondVersion(const FString& version_string)
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnRespondVersion`"));

	if (OnRespondVersion.IsBound())
	{
		OnRespondVersion.Broadcast(version_string);
	}
}

void
USagaNetworkSubSystem::BroadcastOnUpdateRoomList(const TArray<FSagaVirtualRoom>& list)
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnUpdateRoomList`"));

	if (OnUpdateRoomList.IsBound())
	{
		OnUpdateRoomList.Broadcast(list);
	}
}

void
USagaNetworkSubSystem::BroadcastOnUpdateMembers(const TArray<FSagaVirtualUser>& list)
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnUpdateMembers`"));

	if (OnUpdateMembers.IsBound())
	{
		OnUpdateMembers.Broadcast(list);
	}
}

void
USagaNetworkSubSystem::BroadcastOnUpdatePosition(int32 id, float x, float y, float z)
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnUpdatePosition`"));

	if (OnUpdatePosition.IsBound())
	{
		OnUpdatePosition.Broadcast(id, x, y, z);
	}
}

void
USagaNetworkSubSystem::RegisterNetworkView(AActor* event_interface)
{
	if (event_interface != nullptr)
	{
		FString name = event_interface->GetName();

		if (event_interface->GetClass()->ImplementsInterface(USagaNetworkView::StaticClass()))
		{
			internalList.Add(MoveTempIfPossible(event_interface));
			UE_LOG(LogNet, Log, TEXT("The actor `%s` have been registered to network view."), *name);

			//event_interface->OnDestroyed.AddDynamic(GetSingleInstance(), &USagaNetworkSubSystem::_DestroyNetworkView_Implementation);
			//UE_LOG(LogNet, Log, TEXT("Also binded a event to `OnDestroyed`"));
		}
		else
		{
			UE_LOG(LogNet, Error, TEXT("The actor `%s` have not implemented network view."), *name);
		}
	}
	else
	{
		UE_LOG(LogNet, Error, TEXT("The actor handle is nullptr."));
	}
}

void
USagaNetworkSubSystem::DeregisterNetworkView(AActor* event_interface)
{
	internalList.RemoveSwap(event_interface, false);
}

bool
USagaNetworkSubSystem::TryLoginToServer(const FString& nickname)
{
	if (Start(nickname))
	{
		UE_LOG(LogNet, Log, TEXT("The network subsystem is started."));
		return true;
	}
	else
	{
		UE_LOG(LogNet, Error, TEXT("Cannot start the network subsystem."));
		return false;
	}
}

bool
USagaNetworkSubSystem::SagaNetworkHasSocket()
noexcept
{
	return saga::USagaNetwork::IsSocketAvailable();
}

int32
USagaNetworkSubSystem::SagaNetworkLocalPlayerID()
noexcept
{
	return saga::USagaNetwork::LocalUserId();
}

FString
USagaNetworkSubSystem::SagaNetworkLocalPlayerName()
noexcept
{
	return FString{ saga::USagaNetwork::LocalUserName() };
}

int32
USagaNetworkSubSystem::SagaNetworkCurrentRoomID()
noexcept
{
	return saga::USagaNetwork::CurrentRoomId();
}

FString
USagaNetworkSubSystem::SagaNetworkCurrentRoomTitle()
noexcept
{
	return FString{ saga::USagaNetwork::CurrentRoomTitle() };
}

const TArray<FSagaVirtualUser>&
USagaNetworkSubSystem::GetUserList()
noexcept
{
	return saga::USagaNetwork::GetUserList();
}

const TArray<FSagaVirtualRoom>&
USagaNetworkSubSystem::GetRoomList()
noexcept
{
	return saga::USagaNetwork::GetRoomList();
}

void
USagaNetworkSubSystem::UpdatePlayerList()
{
	// TODO: UpdatePlayerList
	//TAtomic<bool> a;
}

void
USagaNetworkSubSystem::UpdateRoomList()
{
	// TODO: UpdateRoomList

}

void
USagaNetworkSubSystem::OnNetworkInitialized_Implementation(bool succeed)
{
}

void
USagaNetworkSubSystem::OnConnected_Implementation()
{
}

void
USagaNetworkSubSystem::OnFailedToConnect_Implementation(ESagaConnectionContract reason)
{
}

void
USagaNetworkSubSystem::OnDisconnected_Implementation()
{
}

void
USagaNetworkSubSystem::OnRoomCreated_Implementation(int32 id)
{
}

void
USagaNetworkSubSystem::OnJoinedRoom_Implementation(int32 id)
{
}

void
USagaNetworkSubSystem::OnLeftRoomBySelf_Implementation()
{
}

void
USagaNetworkSubSystem::OnLeftRoom_Implementation(int32 id)
{
}

void
USagaNetworkSubSystem::OnRespondVersion_Implementation(const FString& version_string)
{
}

void
USagaNetworkSubSystem::OnUpdateRoomList_Implementation(const TArray<FSagaVirtualRoom>& list)
{
}

void
USagaNetworkSubSystem::OnUpdateMembers_Implementation(const TArray<FSagaVirtualUser>& list)
{
}

void
USagaNetworkSubSystem::OnUpdatePosition_Implementation(int32 id, float x, float y, float z)
{
}
