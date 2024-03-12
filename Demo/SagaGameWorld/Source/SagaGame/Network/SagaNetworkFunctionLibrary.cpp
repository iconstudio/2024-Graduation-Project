#include "Network/SagaNetworkFunctionLibrary.h"
#include "Async/Async.h"
#include "SagaNetwork.h"

FSocket&
USagaNetworkFunctionLibrary::SagaNetworkGetSocket()
noexcept
{
	return saga::USagaNetwork::GetLocalSocket();
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
USagaNetworkFunctionLibrary::GetPlayerList()
noexcept
{
	return saga::USagaNetwork::GetPlayerList();
}

const TArray<FSagaVirtualRoom>&
USagaNetworkFunctionLibrary::GetRoomList()
noexcept
{
	return saga::USagaNetwork::GetRoomList();
}

const TArray<FSagaVirtualUser>&
USagaNetworkFunctionLibrary::AwaitPlayerList(TPromise<bool> promise)
{
	UpdatePlayerList();

	AsyncTask(ENamedThreads::AnyThread, []() {
		// 이 코드는 게임 스레드를 멈추지 않고 비동기적으로 실행됩니다.
	});
	//promise.

	// TODO
	return saga::USagaNetwork::GetPlayerList();
}

const TArray<FSagaVirtualRoom>&
USagaNetworkFunctionLibrary::AwaitRoomList(TPromise<bool> promise)
{
	UpdateRoomList();


	// TODO
	return saga::USagaNetwork::GetRoomList();
}

void
USagaNetworkFunctionLibrary::UpdatePlayerList()
{
	//TAtomic<bool> a;
}

void
USagaNetworkFunctionLibrary::UpdateRoomList()
{

}
