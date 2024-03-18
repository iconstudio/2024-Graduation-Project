#include "Saga/Network/SagaNetworkSystem.h"
#include "Templates/SharedPointer.h"
#include "Containers/Array.h"
#include "Sockets.h"

#include "Saga/Network/SagaNetworkSettings.h"
#include "Saga/Network/SagaNetworkUtility.h"
#include "Saga/Network/SagaPacketSenders.h"
#include "Saga/Network/SagaNetworkFunctionLibrary.h"
#include "Saga/Network/SagaNetworkWorker.h"

namespace
{
	[[nodiscard]] TSharedRef<FInternetAddr> CreateRemoteEndPoint();

	constinit FSocket* clientSocket = nullptr;

	TSharedPtr<saga::FSagaNetworkWorker> netWorker{};
	TArray<saga::FSagaBasicPacket*> taskQueue{};

	/// <remarks>로컬 플레이어도 포함</remarks>
	TArray<FSagaVirtualUser> everyUsers{};
	TAtomic<bool> wasUsersUpdated = true;
	TArray<FSagaVirtualRoom> everyRooms{};
	TAtomic<bool> wasRoomsUpdated = true;

	constinit int32 localUserId = -1;
	FString localUserName{};
	constinit int32 currentRoomId = -1;
	FString currentRoomTitle{};
}

saga::USagaNetwork::USagaNetwork() noexcept
	: Super()
{
	everyUsers.Reserve(100);
	everyRooms.Reserve(100);
}

bool
saga::USagaNetwork::InitializeNetwork()
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
saga::USagaNetwork::ConnectToServer()
{
	if (not saga::USagaNetwork::IsSocketAvailable())
	{
		UE_LOG(LogNet, Error, TEXT("The socket is not available."));
		return ESagaConnectionContract::NoSocket;
	}

	// 연결 부분
	if constexpr (not saga::IsOfflineMode)
	{
		auto remote_endpoint = CreateRemoteEndPoint();
		if (not clientSocket->Connect(*remote_endpoint))
		{
			// 연결 실패 처리
			UE_LOG(LogNet, Error, TEXT("Cannot connect to the server."));
			return ESagaConnectionContract::OtherError;
		}

		// #1
		// 클라는 접속 이후에 닉네임 패킷을 보내야 한다.

		auto sent_r = saga::SendSignInPacket(localUserName);
		if (not sent_r.has_value())
		{
			UE_LOG(LogNet, Error, TEXT("First try of sending signin packet has been failed."));
			return ESagaConnectionContract::SignInFailed;
		}
		else
		{
			UE_LOG(LogNet, Log, TEXT("User's nickname is %s."), *localUserName);
		}
	}

	netWorker = MakeShared<saga::FSagaNetworkWorker>();
	if (netWorker == nullptr)
	{
		UE_LOG(LogNet, Error, TEXT("Has failed to create the worker thread."));
		return ESagaConnectionContract::CannotCreateWorker;
	}

	return ESagaConnectionContract::Success;
}

void
saga::USagaNetwork::AddUser(const FSagaVirtualUser& client)
{
	everyUsers.Add(client);
	wasUsersUpdated = true;
}

void
saga::USagaNetwork::AddUser(FSagaVirtualUser&& client)
{
	everyUsers.Add(std::move(client));
	wasUsersUpdated = true;
}

std::optional<FSagaVirtualUser*>
saga::USagaNetwork::FindUser(int32 id)
noexcept
{
	auto handle = everyUsers.FindByPredicate(FSagaSessionIdComparator{ id });
	if (nullptr != handle)
	{
		return handle;
	}
	else
	{
		return std::nullopt;
	}
}

bool
saga::USagaNetwork::RemoveUser(int32 id)
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
saga::USagaNetwork::ClearUserList()
noexcept
{
	everyUsers.Reset();
	wasUsersUpdated = true;
}

void
saga::USagaNetwork::AddRoom(const FSagaVirtualRoom& room)
{
	everyRooms.Add(room);
	wasRoomsUpdated = true;
}

void
saga::USagaNetwork::AddRoom(FSagaVirtualRoom&& room)
{
	everyRooms.Add(std::move(room));
	wasRoomsUpdated = true;
}

std::optional<FSagaVirtualRoom*>
saga::USagaNetwork::FindRoom(int32 id)
noexcept
{
	auto handle = everyRooms.FindByPredicate(FSagaSessionIdComparator{ id });
	if (nullptr != handle)
	{
		return handle;
	}
	else
	{
		return std::nullopt;
	}
}

std::optional<FSagaVirtualRoom*>
saga::USagaNetwork::RoomAt(int32 index)
noexcept
{
	//everyRooms.RangeCheck(index);
	if (everyRooms.IsValidIndex(index))
	{
		return std::addressof(everyRooms[index]);
	}
	else
	{
		return std::nullopt;
	}
}

bool
saga::USagaNetwork::RemoveRoom(int32 id)
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
saga::USagaNetwork::ClearRoomList()
noexcept
{
	everyRooms.Reset();
	wasRoomsUpdated = true;
}

void
saga::USagaNetwork::AddPacket(saga::FSagaBasicPacket* packet)
{
	taskQueue.Add(packet);
}

std::optional<saga::FSagaBasicPacket*>
saga::USagaNetwork::PopPacket()
noexcept
{
	if (taskQueue.IsEmpty())
	{
		return std::nullopt;
	}
	else
	{
		return taskQueue.Pop(false);
	}
}

bool
saga::USagaNetwork::TryPopPacket(saga::FSagaBasicPacket** handle)
noexcept
{
	if (taskQueue.IsEmpty())
	{
		return false;
	}
	else
	{
		*handle = taskQueue.Pop(false);
		return true;
	}
}

bool
saga::USagaNetwork::TryPopPacket(FSagaBasicPacket*& handle)
noexcept
{
	if (taskQueue.IsEmpty())
	{
		return false;
	}
	else
	{
		handle = taskQueue.Pop(false);
		return true;
	}
}

void
saga::USagaNetwork::LocalUserId(int32 id)
noexcept
{
	localUserId = id;
}

int32
saga::USagaNetwork::LocalUserId()
noexcept
{
	return localUserId;
}

void
saga::USagaNetwork::LocalUserName(FStringView nickname)
{
	localUserName = nickname;
}

FStringView
saga::USagaNetwork::LocalUserName()
noexcept
{
	return localUserName;
}

void
saga::USagaNetwork::CurrentRoomId(int32 id)
noexcept
{
	currentRoomId = id;
}

int32
saga::USagaNetwork::CurrentRoomId()
noexcept
{
	return currentRoomId;
}

void
saga::USagaNetwork::CurrentRoomTitle(FStringView title)
{
	currentRoomTitle = title;
}

FStringView
saga::USagaNetwork::CurrentRoomTitle()
noexcept
{
	return currentRoomTitle;
}

FSocket&
saga::USagaNetwork::GetLocalSocket()
noexcept
{
	return *clientSocket;
}

const TArray<FSagaVirtualUser>&
saga::USagaNetwork::GetUserList()
noexcept
{
	return everyUsers;
}

const TArray<FSagaVirtualRoom>&
saga::USagaNetwork::GetRoomList()
noexcept
{
	return everyRooms;
}

bool
saga::USagaNetwork::HasUser(int32 id)
noexcept
{
	return everyUsers.ContainsByPredicate(FSagaSessionIdComparator{ id });
}

bool saga::USagaNetwork::HasRoom(int32 id) noexcept
{
	return everyRooms.ContainsByPredicate(FSagaSessionIdComparator{ id });
}

bool
saga::USagaNetwork::IsSocketAvailable()
noexcept
{
	return nullptr != clientSocket;
}

bool
saga::USagaNetwork::IsConnected()
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

namespace
{
	TSharedRef<FInternetAddr> CreateRemoteEndPoint()
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
}

void
UpdatePlayerList()
{
	if (wasUsersUpdated)
	{
		wasUsersUpdated = false;
	}
}

void
UpdateRoomList()
{
	if (wasRoomsUpdated)
	{
		wasRoomsUpdated = false;
	}
}
