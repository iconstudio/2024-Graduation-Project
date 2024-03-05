#include "SagaNetwork.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Sockets.h"
#include "Settings/SagaNetworkSettings.h"
#include "SagaNetworkUtility.h"
#include "SagaLocalPlayer.h"

void
USagaNetwork::Init()
{
	Super::Init();

	EveryClients.Reserve(100);

	LocalSocket = USagaNetworkUtility::CreateTcpSocket();
	if (nullptr == LocalSocket)
	{
		throw "error!";
	}
	
	auto local_endpoint = USagaNetworkUtility::MakeEndPoint(FIPv4Address::InternalLoopback, USagaNetworkSettings::GetLocalPort());
	if (not LocalSocket->Bind(*local_endpoint))
	{
		throw "error!";
	}

	if (not LocalSocket->SetReuseAddr())
	{
		throw "error!";
	}
	// 연결 부분

#if true
	{
		auto remote_endpoint = USagaNetworkSettings::CreateRemoteEndPoint();
		if (LocalSocket->Connect(*remote_endpoint))
		{
			// 연결 성공
		}
		else
		{
			// 연결 실패 처리
			throw "error!";
		}

		// #1
		// 클라는 접속 이후에 닉네임 패킷을 보내야 한다.

		constexpr FSagaPacket_CS_SignIn packet{ L"Nickname" };
		auto ptr = packet.Serialize();
	
		int32 sent_bytes = USagaNetworkUtility::Send(MakeShareable(LocalSocket), ptr, packet.WannabeSize());
		if (sent_bytes <= 0)
		{
			throw "error!";
		}

		// #2
		// 서버가 닉네임 패킷을 받으면 서버는 ID 부여 패킷을 보낸다.
		// 클라는 ID 부여 패킷을 받아서 갱신하고, 게임 or 메뉴 레벨로 넘어가야 한다.
		uint8 recv_buffer[512]{};

		int32 recv_bytes{};
		if (not LocalSocket->Recv(recv_buffer, sizeof(recv_buffer), recv_bytes))
		{
			throw "error!";
		}

		// 패킷 검증 필요

		FSagaPacket_SC_SucceedSignIn id_packet{};
		id_packet.Read(recv_buffer);

		if (id_packet.myProtocol != EPacketProtocol::SC_SIGNIN_SUCCESS or id_packet.mySize <= 0)
		{
			throw "error!";
		}

		if (id_packet.mySize != static_cast<int32>(FSagaPacket_SC_SucceedSignIn::SignedWannabeSize()))
		{
			throw "error!";
		}

		// 플레이어 ID 읽기
		auto local_client = new FSagaLocalPlayer{};
		local_client->MyID = id_packet.clientId;

		EveryClients.Add(local_client);

		// #3
		// 좌표 송수신 
	
		FSagaPacket_CS_ClientPosition pk_position{};

		// #3-a
		// 로우 버퍼 사용
		uint8 position_raw_buffer[256]{};
		pk_position.Write(position_raw_buffer);
		USagaNetworkUtility::RawSend(LocalSocket, position_raw_buffer, FSagaPacket_CS_ClientPosition::WannabeSize());

		// #3-b
		// 공유 포인터 사용
		//auto position_buffer = pk_position.Serialize();
		//USagaNetworkUtility::Send(MakeShareable(LocalSocket), position_buffer, FSagaPacket_CS_ClientPosition::WannabeSize());
	}
#endif
}

void
USagaNetwork::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);
}

void
USagaNetwork::Shutdown()
{
	Super::Shutdown();

	LocalSocket->Close();
}

void
USagaNetwork::SendKeyToServer(FKey Key)
{
	FString KeyString = Key.ToString();
	//TCHAR* SerializedChar = KeyString.GetCharArray().GetData();
	//int32 Size = FCString::Strlen(SerializedChar) + 1;
	//int32 Sent = 0;

	//// 데이터 전송
	//bool Successful = SagaClientSocket->Send((uint8*)TCHAR_TO_UTF8(SerializedChar), Size, Sent);
}

void
USagaNetwork::AssignPlayerID(APlayerController* PlayerController)
{
}
