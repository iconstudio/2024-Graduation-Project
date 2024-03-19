#include "Saga/Network/SagaNetworkSubSystem.h"
#include "UObject/Object.h"
#include "Kismet/GameplayStatics.h"
#include "Delegates/Delegate.h"
#include "Delegates/DelegateInstanceInterface.h"
#include "Async/Async.h"
#include "Sockets.h"

#include "Saga/Network/SagaNetworkWorker.h"
#include "Saga/Network/SagaNetworkSettings.h"
#include "Saga/Network/SagaNetworkUtility.h"
#include "Saga/Network/SagaPacketSenders.h"

USagaNetworkSubSystem::USagaNetworkSubSystem()
	: UGameInstanceSubsystem()
	, localUserId(-1), localUserName(), currentRoomId(), currentRoomTitle()
	, OnNetworkInitialized(), OnConnected(), OnFailedToConnect(), OnDisconnected()
	, OnRoomCreated(), OnJoinedRoom(), OnLeftRoomBySelf(), OnLeftRoom()
	, OnRespondVersion(), OnUpdateRoomList(), OnUpdateMembers()
	, OnUpdatePosition()
{}

[[nodiscard]] TSharedRef<FInternetAddr> CreateRemoteEndPoint();

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

	everyUsers.Reserve(100);
	everyRooms.Reserve(100);

	if (InitializeNetwork_Implementation())
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
		if (not IsSocketAvailable())
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

		USagaNetworkSubSystem::SetLocalUserName(nickname);

		UE_LOG(LogNet, Log, TEXT("Connecting..."));

		auto connect_r = ConnectToServer_Implementation();
		if (connect_r == ESagaConnectionContract::Success)
		{
			// #2
			// 서버가 닉네임 패킷을 받으면 서버는 ID 부여 패킷을 보낸다.
			// 클라는 ID 부여 패킷을 받아서 갱신하고, 게임 or 메뉴 레벨로 넘어가야 한다.
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
		if (IsSocketAvailable())
		{
			UE_LOG(LogNet, Warning, TEXT("Closing network system..."));
			//clientSocket->Shutdown(ESocketShutdownMode::ReadWrite);

			return std::exchange(clientSocket, nullptr)->Close();
		}
		else
		{
			UE_LOG(LogNet, Warning, TEXT("The network system has been destroyed."));
			return true;
		}
	}
	else
	{
		UE_LOG(LogNet, Warning, TEXT("The network system has been destroyed. (Offline Mode)"));
		return true;
	}
}

void
USagaNetworkSubSystem::CallFunctionOnGameThread(TUniqueFunction<void()> function)
{
	/*
	FGraphEventRef Task = FFunctionGraphTask::CreateAndDispatchWhenReady(MoveTemp(function), TStatId(), nullptr, ENamedThreads::GameThread);
	*/

	AsyncTask(ENamedThreads::GameThread, MoveTemp(function));
}

void
USagaNetworkSubSystem::SetLocalUserId(int32 id)
noexcept
{
	localUserId = id;
}

int32
USagaNetworkSubSystem::GetLocalUserId()
const noexcept
{
	return localUserId;
}

void
USagaNetworkSubSystem::SetLocalUserName(const FString& nickname)
{
	localUserName = nickname;
}

FString
USagaNetworkSubSystem::GetLocalUserName()
const
{
	return localUserName;
}

void
USagaNetworkSubSystem::SetCurrentRoomId(int32 id)
noexcept
{
	currentRoomId = id;
}

int32
USagaNetworkSubSystem::GetCurrentRoomId()
const noexcept
{
	return currentRoomId;
}

void
USagaNetworkSubSystem::SetCurrentRoomTitle(const FString& title)
{
	currentRoomTitle = title;
}

FString
USagaNetworkSubSystem::GetCurrentRoomTitle()
const
{
	return currentRoomTitle;
}

void
USagaNetworkSubSystem::AddUser(const FSagaVirtualUser& client)
{
	everyUsers.Add(client);
	wasUsersUpdated = true;
}

bool
USagaNetworkSubSystem::FindUser(int32 id, FSagaVirtualUser& outpin)
noexcept
{
	auto handle = everyUsers.FindByPredicate(FSagaSessionIdComparator{ id });
	if (nullptr != handle)
	{
		outpin = *handle;
		return true;
	}
	else
	{
		return false;
	}
}

bool
USagaNetworkSubSystem::RemoveUser(int32 id)
noexcept
{
	const bool result = 0 < everyUsers.RemoveAllSwap(FSagaSessionIdComparator{ id });
	if (result)
	{
		wasUsersUpdated = true;
	}

	return result;
}

void
USagaNetworkSubSystem::ClearUserList()
noexcept
{
	everyUsers.Reset();
	wasUsersUpdated = true;
}

void
USagaNetworkSubSystem::AddRoom(const FSagaVirtualRoom& room)
{
	everyRooms.Add(room);
	wasRoomsUpdated = true;
}

bool
USagaNetworkSubSystem::FindRoom(int32 id, FSagaVirtualRoom& outpin)
noexcept
{
	auto handle = everyRooms.FindByPredicate(FSagaSessionIdComparator{ id });
	if (nullptr != handle)
	{
		outpin = *handle;
		return true;
	}
	else
	{
		return false;
	}
}

bool
USagaNetworkSubSystem::RoomAt(int32 index, FSagaVirtualRoom& outpin)
noexcept
{
	if (everyRooms.IsValidIndex(index))
	{
		outpin = everyRooms[index];
		return true;
	}
	else
	{
		return false;
	}
}

bool
USagaNetworkSubSystem::RemoveRoom(int32 id)
noexcept
{
	const bool result = 0 < everyRooms.RemoveAllSwap(FSagaSessionIdComparator{ id });
	if (result)
	{
		wasRoomsUpdated = true;
	}

	return result;
}

void
USagaNetworkSubSystem::ClearRoomList()
noexcept
{
	everyRooms.Reset();
	wasRoomsUpdated = true;
}

const TArray<FSagaVirtualUser>&
USagaNetworkSubSystem::GetUserList()
const noexcept
{
	return everyUsers;
}

const TArray<FSagaVirtualRoom>&
USagaNetworkSubSystem::GetRoomList()
const noexcept
{
	return everyRooms;
}

bool
USagaNetworkSubSystem::HasUser(int32 id)
const noexcept
{
	return everyUsers.ContainsByPredicate(FSagaSessionIdComparator{ id });
}

bool
USagaNetworkSubSystem::HasRoom(int32 id)
const noexcept
{
	return everyRooms.ContainsByPredicate(FSagaSessionIdComparator{ id });
}

int32
USagaNetworkSubSystem::SendSignInPacket(const FString& nickname)
{
	return saga::SendSignInPacket(clientSocket, nickname).value_or(0);
}

int32
USagaNetworkSubSystem::SendCreateRoomPacket(const FString& title)
{
	return saga::SendCreateRoomPacket(clientSocket, title).value_or(0);
}

int32
USagaNetworkSubSystem::SendJoinRoomPacket(int32 room_id)
{
	return saga::SendJoinRoomPacket(clientSocket, room_id).value_or(0);
}

int32
USagaNetworkSubSystem::SendLeaveRoomPacket()
{
	return saga::SendLeaveRoomPacket(clientSocket).value_or(0);
}

int32
USagaNetworkSubSystem::SendRequestVersionPacket()
{
	return saga::SendRequestVersionPacket(clientSocket).value_or(0);
}

int32
USagaNetworkSubSystem::SendRequestRoomsPacket()
{
	return saga::SendRequestRoomsPacket(clientSocket).value_or(0);
}

int32
USagaNetworkSubSystem::SendRequestMembersPacket()
{
	return saga::SendRequestMembersPacket(clientSocket).value_or(0);
}

int32
USagaNetworkSubSystem::SendGameStartPacket()
{
	return saga::SendGameStartPacket(clientSocket).value_or(0);
}

int32
USagaNetworkSubSystem::SendGameIsLoadedPacket()
{
	return saga::SendGameIsLoadedPacket(clientSocket).value_or(0);
}

int32
USagaNetworkSubSystem::SendPositionPacket(float x, float y, float z)
{
	return saga::SendPositionPacket(clientSocket, x, y, z).value_or(0);
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
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnFailedToInitializeNetwork` was not bound"));
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
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnFailedToInitializeNetwork` was not bound"));
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
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnConnected` was not bound"));
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
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnFailedToConnect` was not bound"));
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
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnDisconnected` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnRoomCreated(int32 room_id)
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnRoomCreated`"));

	if (OnRoomCreated.IsBound())
	{
		OnRoomCreated.Broadcast(room_id);
	}
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnRoomCreated` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnJoinedRoom(int32 user_id)
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnJoinedRoom`"));

	if (OnJoinedRoom.IsBound())
	{
		OnJoinedRoom.Broadcast(user_id);
	}
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnJoinedRoom` was not bound"));
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
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnLeftRoomBySelf` was not bound"));
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
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnLeftRoom` was not bound"));
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
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnRespondVersion` was not bound"));
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
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnUpdateRoomList` was not bound"));
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
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnUpdateMembers` was not bound"));
	}
}

void
USagaNetworkSubSystem::BroadcastOnUpdatePosition(int32 user_id, float x, float y, float z)
const
{
	UE_LOG(LogNet, Log, TEXT("Brodcasting `OnUpdatePosition`"));

	if (OnUpdatePosition.IsBound())
	{
		OnUpdatePosition.Broadcast(user_id, x, y, z);
	}
	else
	{
		UE_LOG(LogNet, Warning, TEXT("`OnUpdatePosition` was not bound"));
	}
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
USagaNetworkSubSystem::IsSocketAvailable()
const noexcept
{
	return nullptr != clientSocket;
}

bool
USagaNetworkSubSystem::IsConnected()
const noexcept
{
	if (clientSocket != nullptr and clientSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
	{
		return true;
	}
	else
	{
		return false;
	}
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

bool
USagaNetworkSubSystem::InitializeNetwork_Implementation()
{
	if (nullptr != clientSocket)
	{
		return true;
	}

	clientSocket = saga::CreateTcpSocket();
	if (nullptr == clientSocket)
	{
		return false;
	}

	// NOTICE: 클라는 바인드 금지
	//auto local_endpoint = saga::MakeEndPoint(FIPv4Address::InternalLoopback, saga::GetLocalPort());
	//if (not clientSocket->Bind(*local_endpoint))
	//{
	//	return false;
	//}

	if (not clientSocket->SetReuseAddr())
	{
		return false;
	}

	if (not clientSocket->SetNoDelay())
	{
		return false;
	}

	return true;
}

ESagaConnectionContract
USagaNetworkSubSystem::ConnectToServer_Implementation()
{
	if (not IsSocketAvailable())
	{
		UE_LOG(LogNet, Error, TEXT("The socket is not available."));
		return ESagaConnectionContract::NoSocket;
	}

	// 연결 부분
	if constexpr (not saga::IsOfflineMode)
	{
		auto remote_endpoint = CreateRemoteEndPoint();
		if (not remote_endpoint->IsValid())
		{
			auto err_msg = saga::GetLastErrorContents();
			UE_LOG(LogNet, Error, TEXT("The endpoint has fault, due to '%s'"), err_msg);

			return ESagaConnectionContract::WrongAddress;
		}

		if (not clientSocket->Connect(*remote_endpoint))
		{
			// 연결 실패 처리
			auto err_msg = saga::GetLastErrorContents();
			UE_LOG(LogNet, Error, TEXT("Cannot connect to the server, due to '%s'"), err_msg);

			return ESagaConnectionContract::OtherError;
		}

		// #1
		// 클라는 접속 이후에 닉네임 패킷을 보내야 한다.


		auto sent_r = SendSignInPacket(localUserName);
		if (sent_r <= 0)
		{
			auto err_msg = saga::GetLastErrorContents();
			UE_LOG(LogNet, Error, TEXT("First try of sending signin packet has been failed, due to '%s'"), err_msg);

			return ESagaConnectionContract::SignInFailed;
		}
		else
		{
			UE_LOG(LogNet, Log, TEXT("User's nickname is %s."), *localUserName);
		}
	}

	netWorker = MakeUnique<FSagaNetworkWorker>(this);
	if (netWorker == nullptr)
	{
		UE_LOG(LogNet, Error, TEXT("Has failed to create the worker thread."));
		return ESagaConnectionContract::CannotCreateWorker;
	}

	return ESagaConnectionContract::Success;
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

TSharedRef<FInternetAddr>
CreateRemoteEndPoint()
{
	if constexpr (saga::ConnectionCategory == saga::SagaNetworkConnectionCategory::Local)
	{
		return saga::MakeEndPoint(FIPv4Address::Any, saga::RemotePort);
	}
	else if constexpr (saga::ConnectionCategory == saga::SagaNetworkConnectionCategory::Host)
	{
		return saga::MakeEndPoint(FIPv4Address::InternalLoopback, saga::RemotePort);
	}
	else if constexpr (saga::ConnectionCategory == saga::SagaNetworkConnectionCategory::Remote)
	{
		return saga::MakeEndPointFrom(saga::RemoteAddress, saga::RemotePort);
	}
	else
	{
		throw "error!";
	}
}
