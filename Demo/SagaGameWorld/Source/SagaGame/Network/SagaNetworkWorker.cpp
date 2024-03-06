#include "SagaNetworkWorker.h"
#include "SagaBasicPacket.h"
#include "SagaClientPacketPrefabs.h"
#include "SagaNetwork.h"
#include "Sockets.h"

using namespace saga;

FSagaNetworkWorker::FSagaNetworkWorker()
{
	MyThread = FRunnableThread::Create(this, TEXT("Worker Thread"));
}

FSagaNetworkWorker::~FSagaNetworkWorker()
{
	if (MyThread)
	{
		// 스레드 종료
		MyThread->WaitForCompletion();
		MyThread->Kill();
		delete MyThread;

		MyThread = nullptr;
	}
}

bool
FSagaNetworkWorker::Init()
{
	UE_LOG(LogNet, Display, TEXT("Worker has been initialized"));

	return (MyThread != nullptr);
}

uint32
FSagaNetworkWorker::Run()
{
	auto instance = USagaNetwork::Instance();
	auto& socket = instance->LocalSocket;

	int32 recv_bytes{};
	uint8 recv_buffer[512]{};
	std::byte* alt_buffer = reinterpret_cast<std::byte*>(recv_buffer);

	while (true)
	{
#if true
		// Recv 작업 진행

		// #2
		// 서버가 닉네임 패킷을 받으면 서버는 ID 부여 패킷을 보낸다.
		// 클라는 ID 부여 패킷을 받아서 갱신하고, 게임 or 메뉴 레벨로 넘어가야 한다.
		if (not socket->Recv(recv_buffer, sizeof(recv_buffer), recv_bytes))
		{
			UE_LOG(LogNet, Error, TEXT("Receiving has failed"));
			return 1;
		}

		if (recv_bytes <= 0)
		{
			UE_LOG(LogNet, Error, TEXT("Received 0 byte"));
			return 2;
		}

		// 패킷 검증 필요
		FSagaBasicPacket reader{ EPacketProtocol::UNKNOWN };
		auto seek = reader.Read(alt_buffer);


		//FKey key;
		//FString KeyString = key.ToString();
		//TCHAR* SerializedChar = KeyString.GetCharArray().GetData();
		//int32 Size = FCString::Strlen(SerializedChar) + 1;
		//int32 Sent = 0;

		//// 데이터 전송
		//bool Successful = SagaClientSocket->Send((uint8*)TCHAR_TO_UTF8(SerializedChar), Size, Sent);

		//if (id_packet.myProtocol != EPacketProtocol::SC_SIGNIN_SUCCESS or id_packet.mySize <= 0)
		{
		//	throw "error!";
		}

		//if (id_packet.mySize != static_cast<int32>(FSagaPacket_SC_SucceedSignIn::SignedWannabeSize()))
		{
			//	throw "error!";
		}

		// 플레이어 ID 읽기
		//auto local_client = new FSagaLocalPlayer{};
		//local_client->MyID = id_packet.clientId;

		//EveryClients.Add(local_client);

		// #3
		// 좌표 송수신 

		//FSagaPacket_CS_ClientPosition pk_position{};

		// #3-a
		// 로우 버퍼 사용
		//uint8 position_raw_buffer[256]{};
		//pk_position.Write(position_raw_buffer);
		//USagaNetworkUtility::RawSend(socket, position_raw_buffer, FSagaPacket_CS_ClientPosition::WannabeSize());

		// #3-b
		// 공유 포인터 사용
		//auto position_buffer = pk_position.Serialize();
		//USagaNetworkUtility::Send(MakeShareable(LocalSocket), position_buffer, FSagaPacket_CS_ClientPosition::WannabeSize());
	}
#endif
	return 0;
}

void
FSagaNetworkWorker::Exit()
{
}

void
FSagaNetworkWorker::Stop()
{
}
