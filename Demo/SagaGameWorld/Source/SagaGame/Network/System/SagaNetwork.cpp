#include "Network/System/SagaNetwork.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Sockets.h"
#include "Network/System/SagaNetworkSettings.h"
#include "Network/SagaNetworkUtility.h"

void
USagaNetwork::Init()
{
	Super::Init();

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
