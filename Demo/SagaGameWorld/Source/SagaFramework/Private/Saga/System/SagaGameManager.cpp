#include "Saga/System/SagaGameManager.h"
#include "Templates/SharedPointer.h"
#include "Containers/Array.h"
#include "Async/Async.h"
#include "Sockets.h"

#include "Saga/Network/SagaNetworkSettings.h"
#include "Saga/Network/SagaNetworkUtility.h"
#include "Saga/Network/SagaNetworkFunctionLibrary.h"
#include "Saga/Network/SagaVirtualUser.h"
#include "Saga/Network/SagaVirtualRoom.h"

USagaGameManager::USagaGameManager(const FObjectInitializer& initializer)
	: Super(initializer)
	, clientSocket(nullptr), netWorker(nullptr)
	, localUserId(-1), localUserName(), currentRoomId(-1), currentRoomTitle()
	, everyUsers(), wasUsersUpdated(true)
	, everyRooms(), wasRoomsUpdated(true)
	, listLock(), internalList()
{
}

void
USagaGameManager::Init()
{
	Super::Init();

	everyUsers.Reserve(50);
	everyRooms.Reserve(30);
	internalList.Reserve(100);
	listLock = false;

	if (InitializeNetwork())
	{
		UE_LOG(LogSagaFramework, Log, TEXT("The network system is initialized."));
		BroadcastOnNetworkInitialized();
	}
	else
	{
		UE_LOG(LogSagaFramework, Error, TEXT("Cannot initialize the network system."));
		BroadcastOnFailedToInitializeNetwork();
	}
}

void
USagaGameManager::Shutdown()
{
	Super::Shutdown();
	CloseNetwork();
}

USagaGameManager*
USagaGameManager::GetInstance(UObject* WorldContextObject)
{
	return WorldContextObject->GetClass()->GetWorld()->GetGameInstance<USagaGameManager>();
}

bool USagaGameManager::InitializeNetwork()
{
	return this->InitializeNetwork_Implementation();
}

bool USagaGameManager::ConnectToServer()
{
	return this->ConnectToServer_Implementation();
}

bool USagaGameManager::CloseNetwork()
{
	return this->CloseNetwork_Implementation();
}

void
USagaGameManager::SetLocalUserId(int32 id)
noexcept
{
	this->localUserId = id;
}

int32
USagaGameManager::GetLocalUserId()
noexcept
{
	return this->localUserId;
}

void
USagaGameManager::SetLocalUserName(const FString& nickname)
{
	this->localUserName = nickname;
}

FString
USagaGameManager::GetLocalUserName()
{
	return this->localUserName;
}

void
USagaGameManager::SetCurrentRoomId(int32 id)
noexcept
{
	this->currentRoomId = id;
}

int32
USagaGameManager::GetCurrentRoomId()
noexcept
{
	return this->currentRoomId;
}

void
USagaGameManager::SetCurrentRoomTitle(const FString& title)
{
	this->currentRoomTitle = title;
}

FString
USagaGameManager::GetCurrentRoomTitle()
{
	return this->currentRoomTitle;
}

void
USagaGameManager::AddUser(FSagaVirtualUser client)
{
	this->AddUser_Implementation(MoveTempIfPossible(client));
}

bool
USagaGameManager::FindUser(int32 id, FSagaVirtualUser& output)
noexcept
{
	return this->FindUser_Implementation(id, output);
}

bool
USagaGameManager::RemoveUser(int32 id)
noexcept
{
	return this->RemoveUser_Implementation(id);
}

const TArray<FSagaVirtualUser>&
USagaGameManager::GetUserList()
noexcept
{
	return this->everyUsers;
}

void
USagaGameManager::ClearUserList()
noexcept
{
	return this->ClearUserList_Implementation();
}

bool
USagaGameManager::HasUser(int32 id)
noexcept
{
	return this->everyUsers.ContainsByPredicate(FSagaSessionIdComparator{ id });
}

void USagaGameManager::AddRoom(FSagaVirtualRoom room)
{
	this->AddRoom_Implementation(MoveTempIfPossible(room));
}

bool
USagaGameManager::FindRoom(int32 id, FSagaVirtualRoom& output)
noexcept
{
	return this->FindRoom_Implementation(id, output);
}

bool
USagaGameManager::RoomAt(int32 index, FSagaVirtualRoom& output)
noexcept
{
	return this->RoomAt_Implementation(index, output);
}

bool
USagaGameManager::RemoveRoom(int32 id)
noexcept
{
	return this->RemoveRoom_Implementation(id);
}

void
USagaGameManager::ClearRoomList()
noexcept
{
	this->ClearRoomList_Implementation();
}


const TArray<FSagaVirtualRoom>&
USagaGameManager::GetRoomList()
noexcept
{
	return this->everyRooms;
}

bool
USagaGameManager::HasRoom(int32 id)
noexcept
{
	return this->everyRooms.ContainsByPredicate(FSagaSessionIdComparator{ id });
}

void
USagaGameManager::UpdatePlayerList()
{
	if (this->wasUsersUpdated)
	{
		this->wasUsersUpdated = false;
	}
}

void
USagaGameManager::UpdateRoomList()
{
	if (this->wasRoomsUpdated)
	{
		this->wasRoomsUpdated = false;
	}
}

bool
USagaGameManager::RegisterNetworkView(AActor* event_interface)
{
	if (event_interface != nullptr)
	{
		USagaGameManager* single = event_interface->GetGameInstance<USagaGameManager>();

		FString name = event_interface->GetName();

		if (event_interface->GetClass()->ImplementsInterface(USagaNetworkView::StaticClass()))
		{
			single->LockList();
			single->internalList.Add(MoveTempIfPossible(event_interface));
			single->UnlockList();

			UE_LOG(LogSagaFramework, Log, TEXT("The actor `%s` has been registered to network view."), *name);

			//UE_LOG(LogSagaFramework, Log, TEXT("Also binded a event to `OnDestroyed`"));
			return true;
		}
		else
		{
			UE_LOG(LogSagaFramework, Error, TEXT("The actor `%s` has not implemented network view."), *name);
		}
	}
	else
	{
		UE_LOG(LogSagaFramework, Error, TEXT("The actor handle is nullptr."));
	}

	return false;
}

void
USagaGameManager::DeregisterNetworkView(AActor* event_interface)
{
	if (event_interface != nullptr)
	{
		USagaGameManager* single = event_interface->GetGameInstance<USagaGameManager>();

		single->LockList();
		if (0 < single->internalList.RemoveSwap(event_interface, false))
		{
			FString name = event_interface->GetName();
			UE_LOG(LogSagaFramework, Display, TEXT("The actor `%s` has been removed from the view list"), *name);
		}
		single->UnlockList();
	}
	else
	{
		UE_LOG(LogSagaFramework, Error, TEXT("The destroying actor handle is nullptr."));
	}
}

FSocket*
USagaGameManager::GetClientSocket()
noexcept
{
	if (this != nullptr)
	{
		return this->clientSocket;
	}
	else
	{
		return nullptr;
	}
}

bool
USagaGameManager::IsSocketAvailable()
noexcept
{
	return this->IsSocketAvailable_Implementation();
}

bool
USagaGameManager::IsConnected()
noexcept
{
	return this->IsConnected_Implementation();
}

bool
USagaGameManager::InitializeNetwork_Implementation()
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

bool
USagaGameManager::ConnectToServer_Implementation()
{
	if constexpr (not saga::IsOfflineMode)
	{
		if (not IsSocketAvailable())
		{
			if (InitializeNetwork())
			{
				UE_LOG(LogSagaFramework, Warning, TEXT("The network system was not initialized."));
			}
			else
			{
				UE_LOG(LogSagaFramework, Error, TEXT("Cannot start the network system."));
				return false;
			}
		}

		if (not IsSocketAvailable())
		{
			UE_LOG(LogSagaFramework, Error, TEXT("The socket is not available."));
			USagaGameManager::BroadcastOnFailedToConnect(ESagaConnectionContract::Error);

			UE_LOG(LogSagaFramework, Error, TEXT("Cannot start the network system because the client socket is null."));
			return false;
		}

		// 연결 부분
		if constexpr (not saga::IsOfflineMode)
		{
			auto endpoint_generator = []() {
				if constexpr (saga::ConnectionCategory == ESagaNetworkConnectionCategory::Local)
				{
					return saga::MakeEndPoint(FIPv4Address::Any, saga::RemotePort);
				}
				else if constexpr (saga::ConnectionCategory == ESagaNetworkConnectionCategory::Host)
				{
					return saga::MakeEndPoint(FIPv4Address::InternalLoopback, saga::RemotePort);
				}
				else if constexpr (saga::ConnectionCategory == ESagaNetworkConnectionCategory::Remote)
				{
					return saga::MakeEndPointFrom(saga::RemoteAddress, saga::RemotePort);
				}
				else
				{
					UE_LOG(LogSagaFramework, Error, TEXT("Cannot start the network system because endpoint's setting is invalid."));
					throw "error!";
				}
				};

			auto remote_endpoint = endpoint_generator();
			if (not clientSocket->Connect(*remote_endpoint))
			{
				// 연결 실패 처리
				UE_LOG(LogSagaFramework, Error, TEXT("Cannot connect to the server."));
				USagaGameManager::BroadcastOnFailedToConnect(ESagaConnectionContract::Error);

				UE_LOG(LogSagaFramework, Error, TEXT("Cannot start the network system because connection has been failed."));
				return false;
			}

			// #1
			// 클라는 접속 이후에 닉네임 패킷을 보내야 한다.

			auto sent_r = USagaNetworkFunctionLibrary::SendSignInPacket(localUserName);
			if (sent_r <= 0)
			{
				UE_LOG(LogSagaFramework, Error, TEXT("First try of sending signin packet has been failed."));
				USagaGameManager::BroadcastOnFailedToConnect(ESagaConnectionContract::Error);

				return false;
			}
			else
			{
				UE_LOG(LogSagaFramework, Log, TEXT("User's nickname is %s."), *localUserName);
			}
		}

		AsyncTask(ENamedThreads::AnyNormalThreadHiPriTask, FSagaNetworkWorker{ this });

		UE_LOG(LogSagaFramework, Log, TEXT("The network system is started."));
		return true;
	}
	else
	{
		UE_LOG(LogSagaFramework, Log, TEXT("The network system is started (Offline Mode)."));
		return true;
	}
}

bool
USagaGameManager::CloseNetwork_Implementation()
{
	if constexpr (not saga::IsOfflineMode)
	{
		if (IsSocketAvailable())
		{
			UE_LOG(LogSagaFramework, Warning, TEXT("Closing network system..."));
			return clientSocket->Close();
		}
		else
		{
			UE_LOG(LogSagaFramework, Warning, TEXT("The network system have been destroyed."));
			return true;
		}
	}
	else
	{
		UE_LOG(LogSagaFramework, Warning, TEXT("The network system have been destroyed. (Offline Mode)"));
		return true;
	}
}

void
USagaGameManager::AddUser_Implementation(FSagaVirtualUser user)
{
	everyUsers.Add(MoveTempIfPossible(user));
	wasUsersUpdated = true;
}

bool
USagaGameManager::FindUser_Implementation(int32 id, FSagaVirtualUser& output)
noexcept
{
	FSagaVirtualUser* handle = everyUsers.FindByPredicate(FSagaSessionIdComparator{ id });
	if (nullptr != handle)
	{
		output = *handle;
		return true;
	}
	else
	{
		return false;
	}
}

bool
USagaGameManager::RemoveUser_Implementation(int32 id)
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
USagaGameManager::ClearUserList_Implementation()
noexcept
{
	everyUsers.Reset();
	wasUsersUpdated = true;
}

void
USagaGameManager::AddRoom_Implementation(FSagaVirtualRoom room)
{
	everyRooms.Add(MoveTempIfPossible(room));
	wasRoomsUpdated = true;
}

bool
USagaGameManager::FindRoom_Implementation(int32 id, FSagaVirtualRoom& output)
noexcept
{
	FSagaVirtualRoom* handle = everyRooms.FindByPredicate(FSagaSessionIdComparator{ id });
	if (nullptr != handle)
	{
		output = *handle;
		return true;
	}
	else
	{
		return false;
	}
}

bool
USagaGameManager::RoomAt_Implementation(int32 index, FSagaVirtualRoom& output)
noexcept
{
	if (everyRooms.IsValidIndex(index))
	{
		output = everyRooms[index];
		return true;
	}
	else
	{
		return false;
	}
}

bool
USagaGameManager::RemoveRoom_Implementation(int32 id)
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
USagaGameManager::ClearRoomList_Implementation()
noexcept
{
	everyRooms.Reset();
	wasRoomsUpdated = true;
}

bool
USagaGameManager::IsSocketAvailable_Implementation()
noexcept
{
	return nullptr != clientSocket;
}

bool
USagaGameManager::IsConnected_Implementation()
noexcept
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
USagaGameManager::LockList()
noexcept
{
	bool expected = false;
	while (not listLock.CompareExchange(expected, true));
}

void
USagaGameManager::UnlockList()
noexcept
{
	listLock = false;
}

void
USagaGameManager::BroadcastOnNetworkInitialized()
{
	UE_LOG(LogSagaFramework, Log, TEXT("Broadcasting `OnNetworkInitialized`"));

	for (auto& interface_view : this->internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnNetworkInitialized(object);
		}
	}
}

void
USagaGameManager::BroadcastOnFailedToInitializeNetwork()
{
	UE_LOG(LogSagaFramework, Log, TEXT("Broadcasting `OnFailedToInitializeNetwork`"));

	for (auto& interface_view : this->internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnFailedToInitializeNetwork(object);
		}
	}
}

void
USagaGameManager::BroadcastOnConnected()
{
	UE_LOG(LogSagaFramework, Log, TEXT("Broadcasting `OnConnected`"));

	for (auto& interface_view : this->internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnConnected(object);
		}
	}
}

void
USagaGameManager::BroadcastOnFailedToConnect(ESagaConnectionContract reason)
{
	UE_LOG(LogSagaFramework, Log, TEXT("Broadcasting `OnFailedToConnect`"));

	for (auto& interface_view : this->internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnFailedToConnect(object, reason);
		}
	}
}

void
USagaGameManager::BroadcastOnDisconnected()
{
	UE_LOG(LogSagaFramework, Log, TEXT("Broadcasting `OnDisconnected`"));

	for (auto& interface_view : this->internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnDisconnected(object);
		}
	}
}

void
USagaGameManager::BroadcastOnRespondVersion(const FString& version_string)
{
	UE_LOG(LogSagaFramework, Log, TEXT("Broadcasting `OnRespondVersion`"));

	for (auto& interface_view : this->internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnRespondVersion(object, version_string);
		}
	}
}

void
USagaGameManager::BroadcastOnUpdateRoomList(const TArray<FSagaVirtualRoom>& list)
{
	UE_LOG(LogSagaFramework, Log, TEXT("Broadcasting `OnUpdateRoomList`"));

	for (auto& interface_view : this->internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnUpdateRoomList(object, list);
		}
	}
}

void
USagaGameManager::BroadcastOnUpdateMembers(const TArray<FSagaVirtualUser>& list)
{
	UE_LOG(LogSagaFramework, Log, TEXT("Broadcasting `OnUpdateMembers`"));

	for (auto& interface_view : this->internalList)
	{
		auto&& object = interface_view.GetObject();
		if (object != nullptr)
		{
			ISagaNetworkView::Execute_OnUpdateMembers(object, list);
		}
	}
}
