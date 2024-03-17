#include "Saga/Network/SagaNetworkFunctionLibrary.h"
#include "Async/Async.h"
#include "Async/Future.h"
#include "Containers/UnrealString.h"
#include <GameplayTask.h>
#include <Tasks/GameplayTask_WaitDelay.h>

#include "Saga/Network/SagaNetworkSettings.h"
#include "Saga/Network/SagaNetworkSystem.h"
#include "Saga/Network/SagaPacketSenders.h"

void
USagaNetworkFunctionLibrary::RegisterNetworkView(TScriptInterface<ISagaNetworkView> event_interface)
{
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

USagaUsersAwaiter::USagaUsersAwaiter(const FObjectInitializer& initializer)
	: UBlueprintAsyncActionBase(initializer)
	, Success(), Failed()
	, WorldContextObject(nullptr), IsActived(false), UpdateTimer()
	, MyOutput(nullptr)
{
}

USagaUsersAwaiter*
USagaUsersAwaiter::AwaitUserList(const UObject* WorldContextObject, TArray<FSagaVirtualUser>& out)
{
	USagaUsersAwaiter* Node = NewObject<USagaUsersAwaiter>();
	Node->WorldContextObject = WorldContextObject;
	Node->MyOutput = &out;

	return Node;
}

void
USagaUsersAwaiter::Activate()
{
	if (nullptr == WorldContextObject)
	{
		FFrame::KismetExecutionMessage(TEXT("Invalid WorldContextObject. Cannot execute `SagaUsersAwaiter`."), ELogVerbosity::Error);
		return;
	}

	UpdatePlayerList();

	WorldContextObject->GetWorld()->GetTimerManager().SetTimer(UpdateTimer, this, &USagaUsersAwaiter::_Update, 1.0f, false);

	IsActived = true;
}

void
USagaUsersAwaiter::_Update()
{
	// TODO: USagaUsersAwaiter
	//AsyncTask(ENamedThreads::AnyThread, [&]() {});
	_Finish();
}

void
USagaUsersAwaiter::_Finish()
{
	// Copy
	*MyOutput = saga::USagaNetwork::GetUserList();

	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(UpdateTimer);
	UpdateTimer.Invalidate();

	if (saga::IsOfflineMode)
	{
		Success.Broadcast();
	}
	else if (saga::USagaNetwork::IsConnected())
	{
		// TODO: USagaUsersAwaiter
		Success.Broadcast();
	}
	else
	{
		Failed.Broadcast();
	}

	IsActived = false;
}

USagaRoomsAwaiter::USagaRoomsAwaiter(const FObjectInitializer& initializer)
	: UBlueprintAsyncActionBase(initializer)
	, Success(), Failed()
	, WorldContextObject(nullptr), IsActived(false), UpdateTimer()
	, MyOutput(nullptr)
{
}

USagaRoomsAwaiter*
USagaRoomsAwaiter::AwaitRoomList(const UObject* WorldContextObject, TArray<FSagaVirtualRoom>& out)
{
	USagaRoomsAwaiter* Node = NewObject<USagaRoomsAwaiter>();
	Node->WorldContextObject = WorldContextObject;
	Node->MyOutput = &out;

	return Node;
}

void
USagaRoomsAwaiter::Activate()
{
	if (nullptr == WorldContextObject)
	{
		FFrame::KismetExecutionMessage(TEXT("Invalid WorldContextObject. Cannot execute `SagaUsersAwaiter`."), ELogVerbosity::Error);
		return;
	}

	UpdateRoomList();

	WorldContextObject->GetWorld()->GetTimerManager().SetTimer(UpdateTimer, this, &USagaRoomsAwaiter::_Update, 1.0f, false);

	IsActived = true;
}

void
USagaRoomsAwaiter::_Update()
{
	// TODO: USagaRoomsAwaiter
	//AsyncTask(ENamedThreads::AnyThread, [&]() {});
	_Finish();
}

void
USagaRoomsAwaiter::_Finish()
{
	// Copy
	*MyOutput = saga::USagaNetwork::GetRoomList();

	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(UpdateTimer);
	UpdateTimer.Invalidate();

	if (saga::IsOfflineMode)
	{
		Success.Broadcast();
	}
	else if (saga::USagaNetwork::IsConnected())
	{
		// TODO: USagaRoomsAwaiter
		Success.Broadcast();
	}
	else
	{
		Failed.Broadcast();
	}

	IsActived = false;
}
