#include "SagaNetwork.h"
#include "Templates/SharedPointer.h"
#include "Sockets.h"

#include "SagaNetworkSettings.h"
#include "SagaNetworkUtility.h"
#include "SagaLocalPlayer.h"
#include "SagaClientPacketPrefabs.h"

[[nodiscard]] TSharedRef<FInternetAddr> CreateRemoteEndPoint();

saga::USagaNetwork::USagaNetwork()
	: Super()
	, MyId(-1), MyName("Empty Client")
	, CurrentRoomId(-1), CurrentRoomTitle()
	, LocalSocket()
	, MyWorker(), PacketQueue()
	, EveryClients()
{
	EveryClients.Reserve(100);
}

bool
saga::USagaNetwork::Awake(const TCHAR* nickname)
{
	auto instance = saga::USagaNetwork::Instance();
	auto& socket = instance->LocalSocket;

	socket = saga::CreateTcpSocket();
	if (nullptr == socket)
	{
		return false;
	}

	// NOTICE: 클라는 바인드 금지
	//auto local_endpoint = saga::MakeEndPoint(FIPv4Address::InternalLoopback, saga::GetLocalPort());
	//if (not socket->Bind(*local_endpoint))
	//{
	//	return false;
	//}

	if (not socket->SetReuseAddr())
	{
		return false;
	}

	if (not socket->SetNoDelay())
	{
		return false;
	}

	auto& name = instance->MyName;
	name = nickname;

	return true;
}

bool
saga::USagaNetwork::Start()
{
	auto instance = saga::USagaNetwork::Instance();
	auto& socket = instance->LocalSocket;

	// 연결 부분
	if constexpr (not saga::IsOfflineMode)
	{
		auto remote_endpoint = CreateRemoteEndPoint();
		if (not socket->Connect(*remote_endpoint))
		{
			// 연결 실패 처리
			UE_LOG(LogNet, Error, TEXT("Cannot connect to the server."));
			return false;
		}

		// #1
		// 클라는 접속 이후에 닉네임 패킷을 보내야 한다.

		auto& name = instance->MyName;

		const saga::CS_SignInPacket packet{ name.GetCharArray().GetData(), static_cast<size_t>(name.Len()) };
		auto ptr = packet.Serialize();
		UE_LOG(LogNet, Log, TEXT("User's nickname is %s."), *name);

		const int32 sent_bytes = saga::RawSend(socket, ptr.get(), packet.WannabeSize());
		if (sent_bytes <= 0)
		{
			UE_LOG(LogNet, Error, TEXT("First send of signin is failed."));
			return false;
		}
	}

	auto& worker = instance->MyWorker;
	worker = MakeShared<saga::FSagaNetworkWorker>();
	if (worker == nullptr)
	{
		UE_LOG(LogNet, Error, TEXT("First send of signin is failed."));
		return false;
	}

	return true;
}

void
saga::USagaNetwork::Update()
{
}

void
saga::USagaNetwork::AddPacket(saga::FSagaBasicPacket* packet)
{
	auto instance = saga::USagaNetwork::Instance();
	auto& queue = instance->PacketQueue;

	queue.Add(packet);
}

saga::FSagaBasicPacket*
saga::USagaNetwork::PopPacket()
{
	auto instance = saga::USagaNetwork::Instance();
	auto& queue = instance->PacketQueue;

	if (queue.IsEmpty())
	{
		return nullptr;
	}
	else
	{
		return queue.Pop(false);
	}
}

bool
saga::USagaNetwork::TryPopPacket(saga::FSagaBasicPacket** handle)
{
	auto instance = saga::USagaNetwork::Instance();
	auto& queue = instance->PacketQueue;

	if (queue.IsEmpty())
	{
		return false;
	}
	else
	{
		*handle = queue.Pop(false);
		return true;
	}
}

void
saga::USagaNetwork::AssignPlayerID(APlayerController* PlayerController)
{
}

void
saga::USagaNetwork::AddClient(const FSagaLocalPlayer& client)
{
	auto instance = saga::USagaNetwork::Instance();
	auto& storage = instance->EveryClients;

	storage.Add(client.GetID(), client);
}

void
saga::USagaNetwork::AddClient(FSagaLocalPlayer&& client)
{
	auto instance = saga::USagaNetwork::Instance();
	auto& storage = instance->EveryClients;

	storage.Add(client.GetID(), std::move(client));
}

std::optional<FSagaLocalPlayer>
saga::USagaNetwork::FindClient(int32 id)
{
	auto instance = saga::USagaNetwork::Instance();
	auto& storage = instance->EveryClients;

	if (auto it = storage.Find(id); it != nullptr)
	{
		return *it;
	}
	else
	{
		return std::nullopt;
	}
}

bool
saga::USagaNetwork::RemoveClient(int32 id)
{
	auto instance = saga::USagaNetwork::Instance();
	auto& storage = instance->EveryClients;

	return 0 < storage.Remove(id);
}

bool
saga::USagaNetwork::HasClient(int32 id)
{
	auto instance = saga::USagaNetwork::Instance();
	auto& storage = instance->EveryClients;

	return storage.Contains(id);
}

bool
saga::USagaNetwork::IsConnected()
noexcept
{
	auto instance = saga::USagaNetwork::Instance();
	auto& socket = instance->LocalSocket;

	if (socket != nullptr and socket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
	{
		return true;
	}
	else
	{
		return false;
	}
}

TSharedRef<FInternetAddr>
CreateRemoteEndPoint()
{
	if constexpr (saga::ConnectionCategory == saga::ESagaNetworkConnectionCategory::Local)
	{
		return saga::MakeEndPoint(FIPv4Address::Any, saga::RemotePort);
	}
	else if constexpr (saga::ConnectionCategory == saga::ESagaNetworkConnectionCategory::Host)
	{
		return saga::MakeEndPoint(FIPv4Address::InternalLoopback, saga::RemotePort);
	}
	else if constexpr (saga::ConnectionCategory == saga::ESagaNetworkConnectionCategory::Remote)
	{
		return saga::MakeEndPointFrom(saga::RemoteAddress, saga::RemotePort);
	}
	else
	{
		throw "error!";
	}
}
