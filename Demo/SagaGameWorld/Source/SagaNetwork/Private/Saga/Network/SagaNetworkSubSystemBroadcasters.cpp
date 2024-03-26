#include "Saga/Network/SagaNetworkSubSystem.h"

void
USagaNetworkSubSystem::BroadcastOnNetworkInitialized()
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnNetworkInitialized`"));

	if (OnNetworkInitialized.IsBound())
	{
		OnNetworkInitialized.Broadcast(true);
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnFailedToInitializeNetwork` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnFailedToInitializeNetwork()
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnFailedToInitializeNetwork`"));

	if (OnNetworkInitialized.IsBound())
	{
		OnNetworkInitialized.Broadcast(false);
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnFailedToInitializeNetwork` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnConnected()
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnConnected`"));

	if (OnConnected.IsBound())
	{
		OnConnected.Broadcast();
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnConnected` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnFailedToConnect(ESagaConnectionContract reason)
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnFailedToConnect`"));

	if (OnFailedToConnect.IsBound())
	{
		OnFailedToConnect.Broadcast(reason);
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnFailedToConnect` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnDisconnected()
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnDisconnected`"));

	if (OnDisconnected.IsBound())
	{
		OnDisconnected.Broadcast();
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnDisconnected` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnRoomCreated(int32 room_id)
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnRoomCreated`"));

	if (OnRoomCreated.IsBound())
	{
		OnRoomCreated.Broadcast(room_id);
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnRoomCreated` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnJoinedRoom(int32 user_id)
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnJoinedRoom`"));

	if (OnJoinedRoom.IsBound())
	{
		OnJoinedRoom.Broadcast(user_id);
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnJoinedRoom` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnLeftRoomBySelf()
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnLeftRoomBySelf`"));

	if (OnLeftRoomBySelf.IsBound())
	{
		OnLeftRoomBySelf.Broadcast();
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnLeftRoomBySelf` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnLeftRoom(int32 id)
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnLeftRoom`"));

	if (OnLeftRoom.IsBound())
	{
		OnLeftRoom.Broadcast(id);
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnLeftRoom` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnRespondVersion(const FString& version_string)
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnRespondVersion`"));

	if (OnRespondVersion.IsBound())
	{
		OnRespondVersion.Broadcast(version_string);
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnRespondVersion` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnUpdateRoomList(const TArray<FSagaVirtualRoom>& list)
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnUpdateRoomList`"));

	if (OnUpdateRoomList.IsBound())
	{
		OnUpdateRoomList.Broadcast(list);
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnUpdateRoomList` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnUpdateMembers(const TArray<FSagaVirtualUser>& list)
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnUpdateMembers`"));

	if (OnUpdateMembers.IsBound())
	{
		OnUpdateMembers.Broadcast(list);
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnUpdateMembers` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnTeamChanged(int32 id, bool is_red_team) const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnTeamChanged`"));

	if (OnTeamChanged.IsBound())
	{
		OnTeamChanged.Broadcast(id, is_red_team);
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnTeamChanged` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnGetPreparedGame() const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnGetPreparedGame`"));

	if (OnGetPreparedGame.IsBound())
	{
		OnGetPreparedGame.Broadcast();
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnGetPreparedGame` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnFailedToStartGame(ESagaGameContract reason)
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnFailedToStartGame`"));

	if (OnFailedToStartGame.IsBound())
	{
		OnFailedToStartGame.Broadcast(reason);
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnFailedToStartGame` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnStartGame() const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnStartGame`"));

	if (OnStartGame.IsBound())
	{
		OnStartGame.Broadcast();
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnStartGame` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnUpdatePosition(int32 user_id, float x, float y, float z)
const
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Brodcasting `OnUpdatePosition`"));

	if (OnUpdatePosition.IsBound())
	{
		OnUpdatePosition.Broadcast(user_id, x, y, z);
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("`OnUpdatePosition` was not bound"));
	}
}
