#include "Saga/Network/SagaNetworkFunctionLibrary.h"
#include "UObject/ScriptInterface.h"
#include "Containers/UnrealString.h"
#include "Async/Async.h"

#include "Saga/Network/SagaNetworkSystem.h"
#include "Saga/Network/SagaNetworkViewAnnihilator.h"
#include "Saga/Network/SagaPacketSenders.h"

namespace
{
	TArray<TScriptInterface<ISagaNetworkView>, FConcurrentLinearArrayAllocator> internalList{};
}

void
USagaNetworkFunctionLibrary::BroadcastOnNetworkInitialized()
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnNetworkInitialized`"));

	for (auto& interface_view : internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnNetworkInitialized(object);
		}
	}
}

void
USagaNetworkFunctionLibrary::BroadcastOnFailedToInitializeNetwork()
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnFailedToInitializeNetwork`"));

	for (auto& interface_view : internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnFailedToInitializeNetwork(object);
		}
	}
}

void
USagaNetworkFunctionLibrary::BroadcastOnConnected()
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnConnected`"));

	for (auto& interface_view : internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnConnected(object);
		}
	}
}

void
USagaNetworkFunctionLibrary::BroadcastOnFailedToConnect(ESagaConnectionContract reason)
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnFailedToConnect`"));

	for (auto& interface_view : internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnFailedToConnect(object, reason);
		}
	}
}

void
USagaNetworkFunctionLibrary::BroadcastOnDisconnected()
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnDisconnected`"));

	for (auto& interface_view : internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnDisconnected(object);
		}
	}
}

void
USagaNetworkFunctionLibrary::BroadcastOnRespondVersion(const FString& version_string)
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnRespondVersion`"));

	for (auto& interface_view : internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnRespondVersion(object, version_string);
		}
	}
}

void
USagaNetworkFunctionLibrary::BroadcastOnUpdateRoomList(const TArray<FSagaVirtualRoom>& list)
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnUpdateRoomList`"));

	for (auto& interface_view : internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnUpdateRoomList(object, list);
		}
	}
}

void
USagaNetworkFunctionLibrary::BroadcastOnUpdateMembers(const TArray<FSagaVirtualUser>& list)
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnUpdateMembers`"));

	for (auto& interface_view : internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnUpdateMembers(object, list);
		}
	}
}

void
USagaNetworkFunctionLibrary::RegisterNetworkView(AActor* event_interface)
{
	if (event_interface != nullptr)
	{
		FString name = event_interface->GetName();

		if (event_interface->GetClass()->ImplementsInterface(USagaNetworkView::StaticClass()))
		{
			internalList.Add(MoveTempIfPossible(event_interface));
			UE_LOG(LogNet, Log, TEXT("The actor `%s` have been registered to network view."), *name);

			//event_interface->OnDestroyed.AddDynamic(GetSingleInstance(), &USagaNetworkFunctionLibrary::_DestroyNetworkView_Implementation);
			UE_LOG(LogNet, Log, TEXT("Also binded a event to `OnDestroyed`"));
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
USagaNetworkFunctionLibrary::DeregisterNetworkView(AActor* event_interface)
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
USagaNetworkFunctionLibrary::SagaNetworkClose()
{
	return saga::USagaNetwork::Destroy();
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
