#include "SagaNetworkWorker.h"
#include "Sockets.h"

#include "SagaNetworkSettings.h"
#include "SagaNetwork.h"
#include "SagaClientPacketPrefabs.h"
#include "SagaNetworkEventRouter.h"

saga::FSagaNetworkWorker::FSagaNetworkWorker()
{
	MyThread = FRunnableThread::Create(this, TEXT("Worker Thread"));
}

saga::FSagaNetworkWorker::~FSagaNetworkWorker()
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
saga::FSagaNetworkWorker::Init()
{
	UE_LOG(LogNet, Display, TEXT("Worker has been initialized"));

	return (MyThread != nullptr);
}

uint32
saga::FSagaNetworkWorker::Run()
{
	auto instance = saga::USagaNetwork::Instance();
	auto& socket = instance->LocalSocket;

	constexpr int32 MaxReceiveSize = 512;
	int32 recv_bytes{};
	uint8 recv_buffer[MaxReceiveSize]{};
	std::byte* alt_buffer = reinterpret_cast<std::byte*>(recv_buffer);

	auto PullReceiveBuffer = [&](int32 packet_size) {
		const auto memsz = static_cast<size_t>(MaxReceiveSize - packet_size);
		std::memcpy(recv_buffer, recv_buffer + recv_bytes, memsz);
		std::memset(recv_buffer + recv_bytes, 0, memsz);

		recv_bytes -= packet_size;
	};

	while (true)
	{
#if true
		// Recv 작업 진행
		int32 temp_recv_bytes{};

		if constexpr (not IsOfflineMode)
		{
			// #2
			// 서버가 닉네임 패킷을 받으면 서버는 ID 부여 패킷을 보낸다.
			// 클라는 ID 부여 패킷을 받아서 갱신하고, 게임 or 메뉴 레벨로 넘어가야 한다.
			if (not socket->Recv(recv_buffer + recv_bytes
				, MaxReceiveSize - recv_bytes
				, temp_recv_bytes))
			{
				UE_LOG(LogNet, Error, TEXT("Receiving has been failed!"));
				return 1;
			}
			else if (temp_recv_bytes <= 0)
			{
				UE_LOG(LogNet, Error, TEXT("Received 0 byte!"));
				return 2;
			}

			recv_bytes += temp_recv_bytes;

			// 패킷 검증 필요
			while (true)
			{
				FSagaBasicPacket basic_pk{ EPacketProtocol::UNKNOWN };
				basic_pk.Read(alt_buffer);

				if (basic_pk.mySize <= 0)
				{
					UE_LOG(LogNet, Error, TEXT("Packet's size was zero!"));
					return 3;
				}

				if (recv_bytes <= basic_pk.mySize)
				{
					auto ename = UEnum::GetValueAsString(basic_pk.myProtocol);
					UE_LOG(LogNet, Log, TEXT("Received a packet (%d)"), *ename);

					saga::EventRouter(alt_buffer, basic_pk.myProtocol, basic_pk.mySize);

					UE_LOG(LogNet, Log, TEXT("Packet's size was %d"), basic_pk.mySize);

					PullReceiveBuffer(basic_pk.mySize);
				}
				else
				{
					break; // while (true) #2
				}
			} // while (true) #2
		} // if constexpr (IsOfflineMode)
	} // while (true) #1
#endif
	return 0;
}

void
saga::FSagaNetworkWorker::Exit()
{
	auto instance = saga::USagaNetwork::Instance();
	auto& socket = instance->LocalSocket;

	socket->Close();
}

void
saga::FSagaNetworkWorker::Stop()
{
}
