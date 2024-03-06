#include "SagaNetwork.h"
#include "Templates/SharedPointer.h"
#include "Sockets.h"

#include "SagaNetworkSettings.h"
#include "SagaNetworkUtility.h"
#include "SagaLocalPlayer.h"
#include "SagaClientPacketPrefabs.h"

using namespace saga;

USagaNetwork::USagaNetwork()
	: LocalSocket()
	, MyWorker(), PacketQueue()
	, EveryClients()
{
	EveryClients.Reserve(100);
}

bool
USagaNetwork::Awake(const TCHAR* nickname)
{
	auto instance = USagaNetwork::Instance();
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
USagaNetwork::Start()
{
	auto instance = USagaNetwork::Instance();
	auto& socket = instance->LocalSocket;

	// 연결 부분
#if true
	auto remote_endpoint = CreateRemoteEndPoint();
	if (not socket->Connect(*remote_endpoint))
	{
		// 연결 실패 처리
		return false;
	}

	// #1
	// 클라는 접속 이후에 닉네임 패킷을 보내야 한다.

#if true
	auto& name = instance->MyName;

	const CS_SignInPacket packet{ name.GetCharArray().GetData(), static_cast<size_t>(name.Len()) };
	auto ptr = packet.Serialize();

	int32 sent_bytes = USagaNetworkUtility::RawSend(socket, ptr.get(), packet.WannabeSize());
	if (sent_bytes <= 0)
	{
		return false;
	}
#endif
#endif

	instance->MyWorker = MakeShared<FSagaNetworkWorker>();
	return (instance->MyWorker != nullptr);
}

void
USagaNetwork::Update()
{
}

void
USagaNetwork::AddPacket(FSagaBasicPacket* packet)
{
	PacketQueue.Add(packet);
}

FSagaBasicPacket*
USagaNetwork::PopPacket()
{
	if (PacketQueue.IsEmpty())
	{
		return nullptr;
	}
	else
	{
		return PacketQueue.Pop(false);
	}
}

bool
USagaNetwork::TryPopPacket(FSagaBasicPacket** handle)
{
	if (PacketQueue.IsEmpty())
	{
		return false;
	}
	else
	{
		*handle = PacketQueue.Pop(false);
		return true;
	}
}

void
USagaNetwork::AssignPlayerID(APlayerController* PlayerController)
{
}

void
saga::USagaNetwork::AddClient(ISagaNetworkView* client)
{
	EveryClients.Add(client->GetID(), client);
}

ISagaNetworkView*
saga::USagaNetwork::FindClient(int32 id)
{
	if (auto it = EveryClients.Find(id); it != nullptr)
	{
		return *it;
	}
	else
	{
		return nullptr;
	}
}

const ISagaNetworkView*
saga::USagaNetwork::FindClient(int32 id) const
{
	if (auto it = EveryClients.Find(id); it != nullptr)
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
	return 0 < EveryClients.Remove(id);
}

bool
saga::USagaNetwork::HasClient(int32 id) const
{
	return EveryClients.Contains(id);
}
