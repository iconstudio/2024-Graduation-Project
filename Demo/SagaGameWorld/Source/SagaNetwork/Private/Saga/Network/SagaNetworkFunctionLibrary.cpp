#include "Saga/Network/SagaNetworkFunctionLibrary.h"
#include "Async/Async.h"
#include "Async/Future.h"
#include "Containers/UnrealString.h"
#include <GameplayTask.h>
#include <Tasks/GameplayTask_WaitDelay.h>

#include "Saga/Network/SagaNetworkSystem.h"
#include "Saga/Network/SagaPacketSenders.h"

namespace
{
	TArray<TScriptInterface<ISagaNetworkView>, FConcurrentLinearArrayAllocator> internalList{};
}

void
USagaNetworkFunctionLibrary::BroadcastOnConnected()
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnConnected`"));

	for (auto& interface_view : internalList)
	{		
		ISagaNetworkView::Execute_OnConnected(interface_view.GetObject());
	}
}

void
USagaNetworkFunctionLibrary::BroadcastOnFailedToConnect(int32 reason)
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnFailedToConnect`"));

	for (auto& interface_view : internalList)
	{
		ISagaNetworkView::Execute_OnFailedToConnect(interface_view.GetObject(), reason);
	}
}

void
USagaNetworkFunctionLibrary::BroadcastOnDisconnected()
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnDisconnected`"));

	for (auto& interface_view : internalList)
	{
		ISagaNetworkView::Execute_OnDisconnected(interface_view.GetObject());
	}
}

void
USagaNetworkFunctionLibrary::BroadcastOnRespondVersion(const FString& version_string)
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnRespondVersion`"));

	for (auto& interface_view : internalList)
	{
		ISagaNetworkView::Execute_OnRespondVersion(interface_view.GetObject(), version_string);
	}
}

void
USagaNetworkFunctionLibrary::BroadcastOnUpdateRoomList(const TArray<FSagaVirtualRoom>& list)
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnUpdateRoomList`"));

	for (auto& interface_view : internalList)
	{
		ISagaNetworkView::Execute_OnUpdateRoomList(interface_view.GetObject(), list);
	}
}

void
USagaNetworkFunctionLibrary::BroadcastOnUpdateMembers(const TArray<FSagaVirtualUser>& list)
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnUpdateMembers`"));

	for (auto& interface_view : internalList)
	{
		ISagaNetworkView::Execute_OnUpdateMembers(interface_view.GetObject(), list);
	}
}

void
USagaNetworkFunctionLibrary::RegisterNetworkView(TScriptInterface<ISagaNetworkView> event_interface)
{
	if (event_interface != nullptr)
	{
		auto&& object = event_interface.GetObject();

		FString name = object->GetName();
		UE_LOG(LogNet, Log, TEXT("The actor `%s` have been registered to network view."), *name);

		internalList.Add(MoveTempIfPossible(event_interface));
	}
	else
	{
		UE_LOG(LogNet, Error, TEXT("The actor handle is nullptr."));
	}
}

void
USagaNetworkFunctionLibrary::DeregisterNetworkView(TScriptInterface<ISagaNetworkView> event_interface)
{
	internalList.RemoveSwap(event_interface, false);
}

bool
USagaNetworkFunctionLibrary::TryLoginToServer(const FString& nickname)
{
	if (saga::USagaNetwork::Start(nickname))
	{
		UE_LOG(LogNet, Log, TEXT("The network system is started."));
		return true;
	}
	else
	{
		UE_LOG(LogNet, Error, TEXT("Cannot start the network system."));
		return false;
	}
}

bool
USagaNetworkFunctionLibrary::SagaNetworkHasSocket()
noexcept
{
	return saga::USagaNetwork::IsSocketAvailable();
}

int32
USagaNetworkFunctionLibrary::SagaNetworkLocalPlayerID()
noexcept
{
	return saga::USagaNetwork::LocalUserId();
}

FString
USagaNetworkFunctionLibrary::SagaNetworkLocalPlayerName()
noexcept
{
	return FString{ saga::USagaNetwork::LocalUserName() };
}

int32
USagaNetworkFunctionLibrary::SagaNetworkCurrentRoomID()
noexcept
{
	return saga::USagaNetwork::CurrentRoomId();
}

FString
USagaNetworkFunctionLibrary::SagaNetworkCurrentRoomTitle()
noexcept
{
	return FString{ saga::USagaNetwork::CurrentRoomTitle() };
}

const TArray<FSagaVirtualUser>&
USagaNetworkFunctionLibrary::GetUserList()
noexcept
{
	return saga::USagaNetwork::GetUserList();
}

const TArray<FSagaVirtualRoom>&
USagaNetworkFunctionLibrary::GetRoomList()
noexcept
{
	return saga::USagaNetwork::GetRoomList();
}

void
USagaNetworkFunctionLibrary::UpdatePlayerList()
{
	// TODO: UpdatePlayerList
	//TAtomic<bool> a;
}

void
USagaNetworkFunctionLibrary::UpdateRoomList()
{
	// TODO: UpdateRoomList

}

int32
USagaNetworkFunctionLibrary::SendSignInPacket(const FString& nickname)
{
	return saga::SendSignInPacket(nickname).value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendCreateRoomPacket(const FString& title)
{
	return saga::SendCreateRoomPacket(title).value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendJoinRoomPacket(int32 room_id)
{
	return saga::SendJoinRoomPacket(room_id).value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendLeaveRoomPacket()
{
	return saga::SendLeaveRoomPacket().value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendRequestVersionPacket()
{
	return saga::SendRequestVersionPacket().value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendRequestRoomsPacket()
{
	return saga::SendRequestRoomsPacket().value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendRequestMembersPacket()
{
	return saga::SendRequestMembersPacket().value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendGameStartPacket()
{
	return saga::SendGameStartPacket().value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendGameIsLoadedPacket()
{
	return saga::SendGameIsLoadedPacket().value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendPositionPacket(float x, float y, float z)
{
	return saga::SendPositionPacket(x, y, z).value_or(0);
}
