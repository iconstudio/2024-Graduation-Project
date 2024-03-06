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

	socket = USagaNetworkUtility::CreateTcpSocket();
	if (nullptr == socket)
	{
		return false;
	}

	// NOTICE: 클라는 바인드 금지
	//auto local_endpoint = USagaNetworkUtility::MakeEndPoint(FIPv4Address::InternalLoopback, saga::GetLocalPort());
	//if (not socket->Bind(*local_endpoint))
	//{
	//	return false;
	//}

	if (not socket->SetReuseAddr())
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
			return false;
		}

		// #1
		// 클라는 접속 이후에 닉네임 패킷을 보내야 한다.

		auto& name = instance->MyName;

		const saga::CS_SignInPacket packet{ name.GetCharArray().GetData(), static_cast<size_t>(name.Len()) };
		auto ptr = packet.Serialize();

		int32 sent_bytes = USagaNetworkUtility::RawSend(socket, ptr.get(), packet.WannabeSize());
		if (sent_bytes <= 0)
		{
			return false;
		}
	}

	instance->MyWorker = MakeShared<saga::FSagaNetworkWorker>();
	return (instance->MyWorker != nullptr);
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
saga::USagaNetwork::AddClient(ISagaNetworkView* client)
{
	auto instance = saga::USagaNetwork::Instance();
	auto& storage = instance->EveryClients;

	storage.Add(client->GetID(), client);
}

ISagaNetworkView*
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
		return nullptr;
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
		return USagaNetworkUtility::MakeEndPoint(FIPv4Address::InternalLoopback, saga::RemotePort);
	}
	else if constexpr (saga::ConnectionCategory == saga::ESagaNetworkConnectionCategory::Host)
	{
		return USagaNetworkUtility::MakeEndPoint(FIPv4Address::Any, saga::RemotePort);
	}
	else if constexpr (saga::ConnectionCategory == saga::ESagaNetworkConnectionCategory::Remote)
	{
		return USagaNetworkUtility::MakeEndPointFrom(saga::RemoteAddress, saga::RemotePort);
	}
	else
	{
		throw "error!";
	}
}
