#include "Saga/Network/SagaNetworkFunctionLibrary.h"
#include "Async/Async.h"
#include "Async/Future.h"
#include "Containers/UnrealString.h"

#include "Saga/Network/SagaNetworkSystem.h"
#include "Saga/Network/SagaPacketSenders.h"

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

const TArray<FSagaVirtualUser>&
USagaNetworkFunctionLibrary::AwaitPlayerList(TPromise<bool> promise)
{
	UpdatePlayerList();

	AsyncTask(ENamedThreads::AnyThread, [&]() {
		// 이 코드는 게임 스레드를 멈추지 않고 비동기적으로 실행됩니다.
		promise.SetValue(true);
	});

	// TODO: AwaitPlayerList
	return saga::USagaNetwork::GetUserList();
}

const TArray<FSagaVirtualRoom>&
USagaNetworkFunctionLibrary::AwaitRoomList(TPromise<bool> promise)
{
	UpdateRoomList();

	AsyncTask(ENamedThreads::AnyThread, [&]() {
		// 이 코드는 게임 스레드를 멈추지 않고 비동기적으로 실행됩니다.
		promise.SetValue(true);
	});

	// TODO: AwaitRoomList
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
	return saga::SendSignInPacket(&saga::USagaNetwork::GetLocalSocket(), nickname).value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendCreateRoomPacket(const FString& title)
{
	return saga::SendCreateRoomPacket(&saga::USagaNetwork::GetLocalSocket(), title).value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendJoinRoomPacket(int32 room_id)
{
	return saga::SendJoinRoomPacket(&saga::USagaNetwork::GetLocalSocket(), room_id).value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendLeaveRoomPacket()
{
	return saga::SendLeaveRoomPacket(&saga::USagaNetwork::GetLocalSocket()).value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendRequestVersionPacket()
{
	return saga::SendRequestVersionPacket(&saga::USagaNetwork::GetLocalSocket()).value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendRequestRoomsPacket()
{
	return saga::SendRequestRoomsPacket(&saga::USagaNetwork::GetLocalSocket()).value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendRequestMembersPacket()
{
	return saga::SendRequestMembersPacket(&saga::USagaNetwork::GetLocalSocket()).value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendGameStartPacket()
{
	return saga::SendGameStartPacket(&saga::USagaNetwork::GetLocalSocket()).value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendGameIsLoadedPacket()
{
	return saga::SendGameIsLoadedPacket(&saga::USagaNetwork::GetLocalSocket()).value_or(0);
}

int32
USagaNetworkFunctionLibrary::SendPositionPacket(float x, float y, float z)
{
	return saga::SendPositionPacket(&saga::USagaNetwork::GetLocalSocket(), x, y, z).value_or(0);
}
