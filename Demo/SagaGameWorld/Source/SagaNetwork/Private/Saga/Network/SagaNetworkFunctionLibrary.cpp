#include "Saga/Network/SagaNetworkFunctionLibrary.h"
#include "Async/Async.h"
#include "Async/Future.h"
#include "Containers/UnrealString.h"
#include <GameplayTask.h>
#include <Tasks/GameplayTask_WaitDelay.h>

#include "Saga/Network/SagaNetworkSystem.h"
#include "Saga/Network/SagaPacketSenders.h"

void
USagaNetworkFunctionLibrary::RegisterNetworkView(AActor* event_interface)
{
	if (event_interface != nullptr
		and event_interface->GetClass()->ImplementsInterface(USagaNetworkView::StaticClass()))
	{
		TScriptInterface<ISagaNetworkView> interface { event_interface };
		auto&& object = interface.GetObject();

		FString name = object->GetName();
		UE_LOG(LogNet, Log, TEXT("The actor `%s` have import network view interface."), *name);


	}
	else if (event_interface != nullptr)
	{
		FString name = event_interface->GetName();
		UE_LOG(LogNet, Error, TEXT("The actor have not import network view interface."), *name);
	}
	else
	{
		UE_LOG(LogNet, Error, TEXT("The actor handle is nullptr."));
	}
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
