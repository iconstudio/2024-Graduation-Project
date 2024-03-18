#include "Saga/Network/SagaNetworkWorker.h"
#include "Sockets.h"

#include "Saga/Network/SagaNetworkSettings.h"
#include "Saga/Network/SagaBasicPacket.h"
#include "Saga/Network/SagaNetworkEventRouter.h"
#include "Saga/Network/SagaNetworkSubSystem.h"
#include "Saga/Network/SagaRoomContract.h"
#include "Saga/Network/SagaPacketProcessor.h"

FSagaNetworkWorker::FSagaNetworkWorker(USagaNetworkSubSystem* instance)
	: SubSystemInstance(instance)
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
	auto& socket = SubSystemInstance->clientSocket;

	constexpr int32 MaxReceiveSize = 512;
	int32 recv_bytes{};
	uint8 recv_buffer[MaxReceiveSize]{};
	std::byte* alt_buffer = reinterpret_cast<std::byte*>(recv_buffer);

	auto PullReceiveBuffer = [&](int32 packet_size) {
		const auto memsz = static_cast<size_t>(MaxReceiveSize - packet_size);
		std::memcpy(recv_buffer, recv_buffer + recv_bytes, memsz);
		std::memset(recv_buffer + recv_bytes, 0, memsz);

		recv_bytes -= packet_size;
		UE_LOG(LogNet, Log, TEXT("Remained receive bytes are %d"), recv_bytes);
		};

	while (true)
	{
#if true
		// Recv 작업 진행
		int32 temp_recv_bytes{};

		if constexpr (not saga::IsOfflineMode)
		{
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
			while (FSagaBasicPacket::MinSize() <= recv_bytes)
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
					UE_LOG(LogNet, Log, TEXT("Received a packet (%s)"), *ename);

					RouteEvents(alt_buffer, basic_pk.myProtocol, basic_pk.mySize);

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
FSagaNetworkWorker::Exit()
{
}

void
FSagaNetworkWorker::Stop()
{
}

void
FSagaNetworkWorker::RouteEvents(const std::byte* packet_buffer, EPacketProtocol protocol, int16 packet_size)
{
	switch (protocol)
	{
	case EPacketProtocol::SC_SIGNIN_SUCCESS:
	{
		int32 my_id{};
		saga::ReceiveSignInSucceedPacket(packet_buffer, my_id);

		UE_LOG(LogNet, Log, TEXT("Local client's id is %d"), my_id);

		SubSystemInstance->CallFunctionOnGameThread([this, my_id]()
			{
				SubSystemInstance->SetLocalUserId(my_id);
				SubSystemInstance->BroadcastOnConnected();
			}
		);
	}
	break;

	case EPacketProtocol::SC_SIGNIN_FAILURE:
	{
		int32 error{};
		saga::ReceiveSignInFailurePacket(packet_buffer, error);

		UE_LOG(LogNet, Log, TEXT("Local client can't get an id from server due to %d"), error);

		SubSystemInstance->CallFunctionOnGameThread([this]()
			{
				SubSystemInstance->SetLocalUserId(-1);
				SubSystemInstance->BroadcastOnFailedToConnect(ESagaConnectionContract::SignInFailed);
			}
		);
	}
	break;

	case EPacketProtocol::SC_ROOM_CREATED:
	{
		int32 room_id{};
		saga::ReceiveRoomCreatedPacket(packet_buffer, room_id);

		UE_LOG(LogNet, Log, TEXT("A room %d is created"), room_id);

		SubSystemInstance->CallFunctionOnGameThread([this, room_id]()
			{
				SubSystemInstance->SetCurrentRoomId(room_id);
				SubSystemInstance->BroadcastOnRoomCreated(room_id);
			}
		);
	}
	break;

	case EPacketProtocol::SC_ROOM_CREATE_FAILED:
	{
		ERoomContract error{};
		saga::ReceiveRoomCreationFailedPacket(packet_buffer, error);

		const auto msg = std::to_wstring(error);
		UE_LOG(LogNet, Log, TEXT("Could not create a room due to %d"), msg.data());
	}
	break;

	case EPacketProtocol::SC_ROOM_JOINED:
	{
		int32 newbie_id{};
		int32 room_id{};
		saga::ReceiveRoomJoinedPacket(packet_buffer, newbie_id, room_id);

		if (newbie_id == SubSystemInstance->GetLocalUserId())
		{
			UE_LOG(LogNet, Log, TEXT("Local client has joined to the room %d"), room_id);

			SubSystemInstance->CallFunctionOnGameThread([this, room_id, newbie_id]()
				{
					SubSystemInstance->SetCurrentRoomId(room_id);
					SubSystemInstance->BroadcastOnJoinedRoom(newbie_id);
				}
			);
		}
		else
		{
			UE_LOG(LogNet, Log, TEXT("Client %d has joined to the room %d"), newbie_id, room_id);

			SubSystemInstance->CallFunctionOnGameThread([this, newbie_id]()
				{
					SubSystemInstance->AddUser(FSagaVirtualUser{ newbie_id, TEXT("Member") });
					SubSystemInstance->BroadcastOnJoinedRoom(newbie_id);
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
		UE_LOG(LogNet, Log, TEXT("Failed to join to a room due to %s"), msg.data());
	}
	break;

	case EPacketProtocol::SC_ROOM_LEFT:
	{
		int32 left_client_id{};
		saga::ReceiveRoomLeftPacket(packet_buffer, left_client_id);

		if (left_client_id == SubSystemInstance->GetLocalUserId())
		{
			UE_LOG(LogNet, Log, TEXT("Local client has been left from room"));

			SubSystemInstance->CallFunctionOnGameThread([this]()
				{
					SubSystemInstance->SetCurrentRoomId(-1);
					SubSystemInstance->ClearUserList();
					SubSystemInstance->BroadcastOnLeftRoomBySelf();
				}
			);
		}
		else
		{
			UE_LOG(LogNet, Log, TEXT("Remote client %d has been left from room"), left_client_id);

			SubSystemInstance->CallFunctionOnGameThread([this, left_client_id]()
				{
					SubSystemInstance->RemoveUser(left_client_id);
					SubSystemInstance->BroadcastOnLeftRoom(left_client_id);
				}
			);
		}
	}
	break;

	case EPacketProtocol::SC_RESPOND_VERSION:
	{
		wchar_t version_string[16]{};

		saga::ReceiveRespondVersionPacket(packet_buffer, version_string, 16);

		UE_LOG(LogNet, Log, TEXT("Version: %s"), version_string);

		SubSystemInstance->CallFunctionOnGameThread([this, version_string]()
			{
				SubSystemInstance->BroadcastOnRespondVersion(version_string);
			}
		);
	}
	break;

	case EPacketProtocol::SC_RESPOND_ROOMS:
	{
		std::vector<saga::datagrams::SerializedRoom> rooms{};

		saga::ReceiveRespondRoomsPacket(packet_buffer, rooms);

		UE_LOG(LogNet, Log, TEXT("Rooms: %d"), rooms.size());

		SubSystemInstance->CallFunctionOnGameThread([this, tr_rooms = std::move(rooms)]()
			{
				SubSystemInstance->ClearRoomList();
				for (auto& room : tr_rooms)
				{
					SubSystemInstance->AddRoom(FSagaVirtualRoom
						{
							room.id, room.title, static_cast<int>(room.members)
						});
					UE_LOG(LogNet, Log, TEXT("Room (%d): %s (%d/4)"), room.id, room.title, room.members);
				}

				SubSystemInstance->BroadcastOnUpdateRoomList(SubSystemInstance->GetRoomList());
			}
		);
	}
	break;

	case EPacketProtocol::SC_RESPOND_USERS:
	{
		std::vector<saga::datagrams::SerializedMember> users{};

		saga::ReceiveRespondUsersPacket(packet_buffer, users);

		UE_LOG(LogNet, Log, TEXT("Members: %d"), users.size());

		SubSystemInstance->CallFunctionOnGameThread([this, tr_users = std::move(users)]()
			{
				SubSystemInstance->ClearUserList();
				for (auto& user : tr_users)
				{
					SubSystemInstance->AddUser(FSagaVirtualUser
						{
							user.id, user.nickname
						});

					UE_LOG(LogNet, Log, TEXT("User (%d): %s"), user.id, user.nickname);
				}

				SubSystemInstance->BroadcastOnUpdateMembers(SubSystemInstance->GetUserList());
			}
		);
	}
	break;

	case EPacketProtocol::SC_FAILED_GAME_START:
	{
		saga::SC_FailedGameStartingPacket pk{};
		auto offset = pk.Read(packet_buffer);

		UE_LOG(LogNet, Log, TEXT("Failed to start game due to %d"), pk.errCause);
	}
	break;

	case EPacketProtocol::SC_GAME_GETTING_READY:
	{
		//SC_ReadyForGamePacket pk{};
		//auto offset = pk.Read(packet_buffer);

		UE_LOG(LogNet, Log, TEXT("Now start loading game..."));
	}
	break;

	case EPacketProtocol::SC_GAME_START:
	{
		//SC_GameStartPacket pk{};
		//auto offset = pk.Read(packet_buffer);

		UE_LOG(LogNet, Log, TEXT("Now start game..."));
	}
	break;

	case EPacketProtocol::SC_CREATE_PLAYER:
	{
		saga::SC_CreatePlayerPacket pk{};
		auto offset = pk.Read(packet_buffer);

		UE_LOG(LogNet, Log, TEXT("A client %d is created"), pk.clientId);

		SubSystemInstance->CallFunctionOnGameThread([this, pk]()
			{
			}
		);
	}
	break;

	case EPacketProtocol::SC_REMOVE_PLAYER:
	{
		saga::SC_DestroyPlayerPacket pk{};
		auto offset = pk.Read(packet_buffer);

		UE_LOG(LogNet, Log, TEXT("A client %d is destroyed(disconnected)"), pk.clientId);

		SubSystemInstance->CallFunctionOnGameThread([this, pk]()
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

		UE_LOG(LogNet, Log, TEXT("Client id %d: pos(%f,%f,%f)"), client_id, x, y, z);
		UE_LOG(LogNet, Log, TEXT("Client id pos"));

		SubSystemInstance->CallFunctionOnGameThread([this, client_id, x, y, z]()
			{
				SubSystemInstance->BroadcastOnUpdatePosition(client_id, x, y, z);
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

		UE_LOG(LogNet, Log, TEXT("RPC from client %d: %s(%lld))"), pk.clientId, pk.rpcScript, pk.rpcArgument);
	}
	break;
	}
}
