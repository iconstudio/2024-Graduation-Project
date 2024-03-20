#include "Saga/Network/SagaNetworkSubSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Queue.h"
#include "Delegates/Delegate.h"
#include "Delegates/DelegateInstanceInterface.h"
#include "Async/Async.h"
#include "Sockets.h"

#include "Saga/Network/SagaNetworkWorker.h"
#include "Saga/Network/SagaNetworkSettings.h"
#include "Saga/Network/SagaNetworkUtility.h"
#include "Saga/Network/SagaBasicPacket.h"
#include "Saga/Network/SagaRoomContract.h"
#include "Saga/Network/SagaPacketProcessor.h"
#include "Saga/Network/SagaPacketSenders.h"

TQueue<UE::Tasks::TTask<int32>> USagaNetworkSubSystem::taskQueue{};

USagaNetworkSubSystem::USagaNetworkSubSystem()
	: UGameInstanceSubsystem()
	, localUserId(-1), localUserName(), currentRoomId(), currentRoomTitle()
	, OnNetworkInitialized(), OnConnected(), OnFailedToConnect(), OnDisconnected()
	, OnRoomCreated(), OnJoinedRoom(), OnLeftRoomBySelf(), OnLeftRoom()
	, OnRespondVersion(), OnUpdateRoomList(), OnUpdateMembers()
	, OnGetPreparedGame(), OnStartGame()
	, OnUpdatePosition()
	, TaskCompletionEvents()
	, clientSocket(nullptr), netWorker(nullptr)
	, everyUsers(), wasUsersUpdated(true)
	, everyRooms(), wasRoomsUpdated(true)
{}

void
USagaNetworkSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

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
	OnGetPreparedGame.AddDynamic(this, &USagaNetworkSubSystem::OnGetPreparedGame_Implementation);
	OnStartGame.AddDynamic(this, &USagaNetworkSubSystem::OnStartGame_Implementation);
	OnUpdatePosition.AddDynamic(this, &USagaNetworkSubSystem::OnUpdatePosition_Implementation);

	everyUsers.Reserve(100);
	everyRooms.Reserve(100);

	if (InitializeNetwork_Implementation())
	{
		BroadcastOnNetworkInitialized();
	}
	else
	{
		BroadcastOnFailedToInitializeNetwork();
	}
}

void
USagaNetworkSubSystem::Deinitialize()
{
	Super::Deinitialize();

	if constexpr (not saga::IsOfflineMode)
	{
		if (IsSocketAvailable())
		{
			Close();
		}
		else
		{
			UE_LOG(LogSagaNetwork, Warning, TEXT("The network subsystem has been destroyed."));
		}
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("The network subsystem has been destroyed. (Offline Mode)"));
	}
}

bool
USagaNetworkSubSystem::ShouldCreateSubsystem(UObject* Outer)
const
{
	if (Outer)
	{
		// https://forums.unrealengine.com/t/solved-getworld-from-static-function-without-pass-an-object/245939
		//UWorld* world = GEngine->GameViewport->GetWorld();
		//float TimeSinceCreation = world->GetFirstPlayerController()->GetGameTimeSinceCreation();

		FString name{ 20, TEXT("") };
		Outer->GetWorld()->GetCurrentLevel()->GetName(name);

		static const FString non_network_levels[] =
		{
			TEXT("InitializationLevel")
		};

		for (auto& non_network_level : non_network_levels)
		{
			if (name == non_network_level)
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

[[nodiscard]] TSharedRef<FInternetAddr> CreateRemoteEndPoint();

bool
USagaNetworkSubSystem::Start(const FString& nickname)
{
	if constexpr (not saga::IsOfflineMode)
	{
		if (not IsSocketAvailable())
		{
			if (InitializeNetwork_Implementation())
			{
				UE_LOG(LogSagaNetwork, Warning, TEXT("The network subsystem was not initialized."));
			}
			else
			{
				UE_LOG(LogSagaNetwork, Error, TEXT("Could not initialize network subsystem."));
				return false;
			}
		}

		USagaNetworkSubSystem::SetLocalUserName(nickname);

		UE_LOG(LogSagaNetwork, Log, TEXT("Connecting..."));

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
			auto str = UEnum::GetValueAsString(connect_r);

			UE_LOG(LogSagaNetwork, Error, TEXT("Could not connect to the server, due to `%s`"), *str);
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
USagaNetworkSubSystem::Close()
{
	if constexpr (not saga::IsOfflineMode)
	{
		if (not IsSocketAvailable())
		{
			UE_LOG(LogSagaNetwork, Warning, TEXT("The socket of client is null."));
			return true;
		}
		else if (not IsConnected())
		{
			clientSocket = nullptr;

			UE_LOG(LogSagaNetwork, Warning, TEXT("The network subsystem had been closed."));
			return true;
		}
		else
		{
			UE_LOG(LogSagaNetwork, Warning, TEXT("Closing the network subsystem..."));

			return CloseNetwork_Implementation();
		}
	}
	else
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("Closing the network subsystem... (Offline Mode)"));
		return true;
	}
}

void
USagaNetworkSubSystem::CallFunctionOnGameThread(TUniqueFunction<void()>&& function)
{
	/*
	FGraphEventRef Task = FFunctionGraphTask::CreateAndDispatchWhenReady(MoveTemp(function), TStatId(), nullptr, ENamedThreads::GameThread);
	*/

	if (IsInGameThread())
	{
		function();
	}
	else
	{
		AsyncTask(ENamedThreads::GameThread, MoveTemp(function));
	}
}

void
USagaNetworkSubSystem::CallPureFunctionOnGameThread(TUniqueFunction<void()>&& function)
const
{
	if (IsInGameThread())
	{
		function();
	}
	else
	{
		AsyncTask(ENamedThreads::GameThread, MoveTemp(function));
	}
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

bool
USagaNetworkSubSystem::TryLoginToServer(const FString& nickname)
{
	if (Start(nickname))
	{
		UE_LOG(LogSagaNetwork, Log, TEXT("The network subsystem is started."));
		return true;
	}
	else if (IsConnected())
	{
		UE_LOG(LogSagaNetwork, Warning, TEXT("The network subsystem had been started."));
		return true;
	}
	else
	{
		UE_LOG(LogSagaNetwork, Error, TEXT("Cannot start the network subsystem."));
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
		UE_LOG(LogSagaNetwork, Error, TEXT("The socket is not available."));
		return ESagaConnectionContract::NoSocket;
	}

	// 연결 부분
	if constexpr (not saga::IsOfflineMode)
	{
		auto remote_endpoint = CreateRemoteEndPoint();
		if (not remote_endpoint->IsValid())
		{
			auto err_msg = saga::GetLastErrorContents();
			UE_LOG(LogSagaNetwork, Error, TEXT("The endpoint has fault, due to '%s'"), err_msg);

			return ESagaConnectionContract::WrongAddress;
		}

		if (not clientSocket->Connect(*remote_endpoint))
		{
			// 연결 실패 처리
			auto err_msg = saga::GetLastErrorContents();
			UE_LOG(LogSagaNetwork, Error, TEXT("Cannot connect to the server, due to '%s'"), err_msg);

			return ESagaConnectionContract::OtherError;
		}

		// #1
		// 클라는 접속 이후에 닉네임 패킷을 보내야 한다.

		auto sent_r = SendSignInPacket(localUserName);
		if (sent_r <= 0)
		{
			auto err_msg = saga::GetLastErrorContents();
			UE_LOG(LogSagaNetwork, Error, TEXT("First try of sending signin packet has been failed, due to '%s'"), err_msg);

			return ESagaConnectionContract::SignInFailed;
		}
		else
		{
			UE_LOG(LogSagaNetwork, Log, TEXT("User's nickname is %s."), *localUserName);
		}
	}

	netWorker = MakeUnique<FSagaNetworkWorker>(this);
	if (netWorker == nullptr)
	{
		UE_LOG(LogSagaNetwork, Error, TEXT("Has failed to create the worker thread."));
		return ESagaConnectionContract::CannotCreateWorker;
	}

	return ESagaConnectionContract::Success;
}

bool USagaNetworkSubSystem::CloseNetwork_Implementation()
{
	clientSocket->Shutdown(ESocketShutdownMode::ReadWrite);

	return CloseNetwork_Implementation(); std::exchange(clientSocket, nullptr)->Close();
}

void
USagaNetworkSubSystem::OnNetworkInitialized_Implementation(bool succeed)
{
	if (succeed)
	{
		UE_LOG(LogSagaNetwork, Log, TEXT("The network subsystem is initialized."));
	}
	else
	{
		UE_LOG(LogSagaNetwork, Error, TEXT("Cannot initialize the network subsystem."));
	}
}

void
USagaNetworkSubSystem::OnConnected_Implementation()
{
}

void
USagaNetworkSubSystem::OnFailedToConnect_Implementation(ESagaConnectionContract reason)
{
	auto msg = UEnum::GetValueAsString(reason);
	UE_LOG(LogSagaNetwork, Log, TEXT("Local client can't get an id from server due to %d"), *msg);
}

void
USagaNetworkSubSystem::OnDisconnected_Implementation()
{
}

void
USagaNetworkSubSystem::OnRoomCreated_Implementation(int32 id)
{
	UE_LOG(LogSagaNetwork, Log, TEXT("A room %d is created"), id);
}

void
USagaNetworkSubSystem::OnJoinedRoom_Implementation(int32 id)
{
}

void
USagaNetworkSubSystem::OnLeftRoomBySelf_Implementation()
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Local client has been left from room"));
}

void
USagaNetworkSubSystem::OnLeftRoom_Implementation(int32 id)
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Remote client %d has been left from room"), id);
}

void
USagaNetworkSubSystem::OnRespondVersion_Implementation(const FString& version_string)
{
	UE_LOG(LogSagaNetwork, Log, TEXT("Version: %s"), *version_string);
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
USagaNetworkSubSystem::OnGetPreparedGame_Implementation()
{
}

void
USagaNetworkSubSystem::OnStartGame_Implementation()
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

void
USagaNetworkSubSystem::RouteEvents(const std::byte* packet_buffer, EPacketProtocol protocol, int16 packet_size)
{
	switch (protocol)
	{
	case EPacketProtocol::SC_SIGNIN_SUCCESS:
	{
		int32 my_id{};
		saga::ReceiveSignInSucceedPacket(packet_buffer, my_id);

		UE_LOG(LogSagaNetwork, Log, TEXT("Local client's id is %d"), my_id);

		CallFunctionOnGameThread([this, my_id]()
			{
				SetLocalUserId(my_id);

				BroadcastOnConnected();
			}
		);
	}
	break;

	case EPacketProtocol::SC_SIGNIN_FAILURE:
	{
		int32 error{};
		saga::ReceiveSignInFailurePacket(packet_buffer, error);

		CallFunctionOnGameThread([this]()
			{
				SetLocalUserId(-1);

				BroadcastOnFailedToConnect(ESagaConnectionContract::SignInFailed);
			}
		);
	}
	break;

	case EPacketProtocol::SC_ROOM_CREATED:
	{
		int32 room_id{};
		saga::ReceiveRoomCreatedPacket(packet_buffer, room_id);

		CallFunctionOnGameThread([this, room_id]()
			{
				SetCurrentRoomId(room_id);

				BroadcastOnRoomCreated(room_id);
			}
		);
	}
	break;

	case EPacketProtocol::SC_ROOM_CREATE_FAILED:
	{
		ERoomContract error{};
		saga::ReceiveRoomCreationFailedPacket(packet_buffer, error);

		const auto msg = std::to_wstring(error);
		UE_LOG(LogSagaNetwork, Log, TEXT("Could not create a room due to %d"), msg.data());
	}
	break;

	case EPacketProtocol::SC_ROOM_JOINED:
	{
		int32 newbie_id{};
		int32 room_id{};
		saga::ReceiveRoomJoinedPacket(packet_buffer, newbie_id, room_id);

		if (newbie_id == GetLocalUserId())
		{
			UE_LOG(LogSagaNetwork, Log, TEXT("Local client has joined to the room %d"), room_id);

			CallFunctionOnGameThread([this, room_id, newbie_id]()
				{
					SetCurrentRoomId(room_id);

					BroadcastOnJoinedRoom(newbie_id);
				}
			);
		}
		else
		{
			UE_LOG(LogSagaNetwork, Log, TEXT("Client %d has joined to the room %d"), newbie_id, room_id);

			CallFunctionOnGameThread([this, newbie_id]()
				{
					AddUser(FSagaVirtualUser{ newbie_id, TEXT("Member") });

					BroadcastOnJoinedRoom(newbie_id);
				}
			);
		}
	}
	break;

	case EPacketProtocol::SC_ROOM_JOIN_FAILED:
	{
		ERoomContract error{};
		saga::ReceiveRoomJoinFailedPacket(packet_buffer, error);

		const auto msg = std::to_wstring(error);
		UE_LOG(LogSagaNetwork, Log, TEXT("Failed to join to a room due to %s"), msg.data());
	}
	break;

	case EPacketProtocol::SC_ROOM_LEFT:
	{
		int32 left_client_id{};
		saga::ReceiveRoomLeftPacket(packet_buffer, left_client_id);

		if (left_client_id == GetLocalUserId())
		{
			CallFunctionOnGameThread([this]()
				{
					SetCurrentRoomId(-1);
					ClearUserList();

					BroadcastOnLeftRoomBySelf();
				}
			);
		}
		else
		{
			CallFunctionOnGameThread([this, left_client_id]()
				{
					RemoveUser(left_client_id);

					BroadcastOnLeftRoom(left_client_id);
				}
			);
		}
	}
	break;

	case EPacketProtocol::SC_RESPOND_VERSION:
	{
		wchar_t version_string[16]{};

		saga::ReceiveRespondVersionPacket(packet_buffer, version_string, 16);

		CallPureFunctionOnGameThread([this, version_string]()
			{
				BroadcastOnRespondVersion(version_string);
			}
		);
	}
	break;

	case EPacketProtocol::SC_RESPOND_ROOMS:
	{
		std::vector<saga::datagrams::SerializedRoom> rooms{};

		saga::ReceiveRespondRoomsPacket(packet_buffer, rooms);

		UE_LOG(LogSagaNetwork, Log, TEXT("Number of rooms: %d"), rooms.size());

		CallFunctionOnGameThread([this, tr_rooms = std::move(rooms)]()
			{
				ClearRoomList();
				for (auto& room : tr_rooms)
				{
					AddRoom(FSagaVirtualRoom
						{
							room.id, room.title, static_cast<int>(room.members)
						});
					UE_LOG(LogSagaNetwork, Log, TEXT("Room (%d): %s (%d/4)"), room.id, room.title, room.members);
				}

				BroadcastOnUpdateRoomList(everyRooms);
			}
		);
	}
	break;

	case EPacketProtocol::SC_RESPOND_USERS:
	{
		std::vector<saga::datagrams::SerializedMember> users{};

		saga::ReceiveRespondUsersPacket(packet_buffer, users);

		UE_LOG(LogSagaNetwork, Log, TEXT("Members: %d"), users.size());

		CallFunctionOnGameThread([this, tr_users = std::move(users)]()
			{
				ClearUserList();
				for (auto& user : tr_users)
				{
					AddUser(FSagaVirtualUser
						{
							user.id, user.nickname
						});

					UE_LOG(LogSagaNetwork, Log, TEXT("User (%d): %s"), user.id, user.nickname);
				}

				BroadcastOnUpdateMembers(everyUsers);
			}
		);
	}
	break;

	case EPacketProtocol::SC_FAILED_GAME_START:
	{
		saga::SC_FailedGameStartingPacket pk{};
		auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaNetwork, Log, TEXT("Failed to start game due to %d"), pk.errCause);
	}
	break;

	case EPacketProtocol::SC_GAME_GETTING_READY:
	{
		//SC_ReadyForGamePacket pk{};
		//auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaNetwork, Log, TEXT("Now start loading game..."));

		CallPureFunctionOnGameThread([this]()
			{
				BroadcastOnGetPreparedGame();
			}
		);
	}
	break;

	case EPacketProtocol::SC_GAME_START:
	{
		//SC_GameStartPacket pk{};
		//auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaNetwork, Log, TEXT("Now start game..."));

		CallPureFunctionOnGameThread([this]()
			{
				BroadcastOnStartGame();
			}
		);
	}
	break;

	case EPacketProtocol::SC_CREATE_PLAYER:
	{
		saga::SC_CreatePlayerPacket pk{};
		auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaNetwork, Log, TEXT("A client %d is created"), pk.clientId);

		CallFunctionOnGameThread([this, pk]()
			{
			}
		);
	}
	break;

	case EPacketProtocol::SC_REMOVE_PLAYER:
	{
		saga::SC_DestroyPlayerPacket pk{};
		auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaNetwork, Log, TEXT("A client %d is destroyed(disconnected)"), pk.clientId);

		CallFunctionOnGameThread([this, pk]()
			{
			}
		);
	}
	break;

	case EPacketProtocol::SC_MOVE_CHARACTER:
	{
		int32 client_id{};
		float x, y, z;

		saga::ReceivePositionPacket(packet_buffer, client_id, x, y, z);

		UE_LOG(LogSagaNetwork, Log, TEXT("Client id %d: pos(%f,%f,%f)"), client_id, x, y, z);
		UE_LOG(LogSagaNetwork, Log, TEXT("Client id pos"));

		CallFunctionOnGameThread([this, client_id, x, y, z]()
			{
				BroadcastOnUpdatePosition(client_id, x, y, z);
			}
		);
	}
	break;

	case EPacketProtocol::SC_UPDATE_CHARACTER:
	{
	}
	break;

	case EPacketProtocol::SC_RPC:
	{
		saga::SC_RpcPacket pk{};

		wchar_t buffer[sizeof(pk.rpcScript) / sizeof(wchar_t)]{};
		std::copy(std::cbegin(pk.rpcScript), std::cend(pk.rpcScript), std::begin(buffer));

		UE_LOG(LogSagaNetwork, Log, TEXT("RPC from client %d: %s(%lld))"), pk.clientId, pk.rpcScript, pk.rpcArgument);
	}
	break;
	}
}
