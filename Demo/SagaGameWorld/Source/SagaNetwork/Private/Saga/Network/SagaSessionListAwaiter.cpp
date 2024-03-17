#include "Saga/Network/SagaSessionListAwaiter.h"
#include "Saga/Network/SagaNetworkSettings.h"
#include "Saga/Network/SagaNetworkSystem.h"

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
