#include "Saga/Network/SagaNetworkWorker.h"
#include "Sockets.h"

#include "Saga/System/SagaGameManager.h"
#include "Saga/Network/SagaNetworkSettings.h"
#include "Saga/Network/SagaVirtualUser.h"
#include "Saga/Network/SagaVirtualRoom.h"
#include "Saga/Network/SagaBasicPacket.h"
#include "Saga/Network/SagaServerPacketPrefabs.h"
#include "Saga/Network/SagaPacketProcessor.h"
#include "Saga/Network/SagaPacketSenders.h"

FSagaNetworkWorker::FSagaNetworkWorker() noexcept
	: Instance()
{
}

FSagaNetworkWorker::FSagaNetworkWorker(USagaGameManager* instance) noexcept
	: Instance(instance)
{
}

void
FSagaNetworkWorker::operator()()
{
	UE_LOG(LogSagaFramework, Log, TEXT("Worker has been initialized"));

	auto& socket = *(Instance->GetClientSocket());

	constexpr int32 MaxReceiveSize = 512;
	int32 recv_bytes{};
	uint8 recv_buffer[MaxReceiveSize]{};
	uint8* alt_buffer = reinterpret_cast<uint8*>(recv_buffer);

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
			// #2
			// 서버가 닉네임 패킷을 받으면 서버는 ID 부여 패킷을 보낸다.
			// 클라는 ID 부여 패킷을 받아서 갱신하고, 게임 or 메뉴 레벨로 넘어가야 한다.
			if (not socket.Recv(recv_buffer + recv_bytes
				, MaxReceiveSize - recv_bytes
				, temp_recv_bytes))
			{
				UE_LOG(LogNet, Error, TEXT("Receiving has been failed!"));
				return;
			}
			else if (temp_recv_bytes <= 0)
			{
				UE_LOG(LogNet, Error, TEXT("Received 0 byte!"));
				return;
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
					return;
				}

				if (recv_bytes <= basic_pk.mySize)
				{
					auto ename = UEnum::GetValueAsString(basic_pk.myProtocol);
					UE_LOG(LogNet, Log, TEXT("Received a packet (%s)"), *ename);

					EventRouter(alt_buffer, basic_pk.myProtocol, basic_pk.mySize);

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
}

void
FSagaNetworkWorker::EventRouter(const uint8* packet_buffer, EPacketProtocol protocol, int16 packet_size)
{
	switch (protocol)
	{
	case EPacketProtocol::SC_SIGNIN_SUCCESS:
	{
		int32 my_id{};
		ReceiveSignInSucceedPacket(packet_buffer, my_id);

		UE_LOG(LogSagaFramework, Log, TEXT("Local client's id is %d"), my_id);
	}
	break;

	case EPacketProtocol::SC_SIGNIN_FAILURE:
	{
		int32 error{};
		ReceiveSignInFailurePacket(packet_buffer, error);

		UE_LOG(LogSagaFramework, Log, TEXT("Local client can't get an id from server due to %d"), error);
	}
	break;

	case EPacketProtocol::SC_ROOM_CREATED:
	{
		int32 room_id{};
		ReceiveRoomCreatedPacket(packet_buffer, room_id);

		Instance->SetCurrentRoomId(room_id);

		UE_LOG(LogSagaFramework, Log, TEXT("A room %d is created"), room_id);
	}
	break;

	case EPacketProtocol::SC_ROOM_CREATE_FAILED:
	{
		ERoomContract error{};
		ReceiveRoomCreationFailedPacket(packet_buffer, error);

		const auto msg = std::to_wstring(error);
		UE_LOG(LogSagaFramework, Log, TEXT("Could not create a room due to %d"), msg.data());
	}
	break;

	case EPacketProtocol::SC_ROOM_JOINED:
	{
		int32 newbie_id{};
		int32 room_id{};
		ReceiveRoomJoinedPacket(packet_buffer, newbie_id, room_id);

		if (newbie_id == Instance->GetLocalUserId())
		{
			Instance->SetCurrentRoomId(room_id);

			UE_LOG(LogSagaFramework, Log, TEXT("Local client has joined to the room %d"), room_id);
		}
		else
		{
			Instance->AddUser(FSagaVirtualUser{ newbie_id, TEXT("Member") });

			UE_LOG(LogSagaFramework, Log, TEXT("Client %d has joined to the room %d"), newbie_id, room_id);
		}
	}
	break;

	case EPacketProtocol::SC_ROOM_JOIN_FAILED:
	{
		ERoomContract error{};
		ReceiveRoomJoinFailedPacket(packet_buffer, error);

		const auto msg = std::to_wstring(error);
		UE_LOG(LogSagaFramework, Log, TEXT("Failed to join to a room due to %s"), msg.data());
	}
	break;

	case EPacketProtocol::SC_ROOM_LEFT:
	{
		int32 left_client{};
		ReceiveRoomLeftPacket(packet_buffer, left_client);

		UE_LOG(LogSagaFramework, Log, TEXT("Client %d has been left from room"), left_client);
	}
	break;

	case EPacketProtocol::SC_RESPOND_VERSION:
	{
		wchar_t version_string[16]{};

		ReceiveRespondVersionPacket(packet_buffer, version_string, 16);

		UE_LOG(LogSagaFramework, Log, TEXT("Version: %s"), version_string);
	}
	break;

	case EPacketProtocol::SC_RESPOND_ROOMS:
	{
		std::vector<FSagaSerializedRoom> rooms{};

		ReceiveRespondRoomsPacket(packet_buffer, rooms);

		UE_LOG(LogSagaFramework, Log, TEXT("Rooms: %d"), rooms.size());

		Instance->ClearRoomList();
		for (auto& room : rooms)
		{
			Instance->AddRoom(FSagaVirtualRoom
				{
					room.id, room.title, static_cast<int>(room.members)
				});
			UE_LOG(LogSagaFramework, Log, TEXT("Room (%d): %s (%d/4)"), room.id, room.title, room.members);
		}
	}
	break;

	case EPacketProtocol::SC_RESPOND_USERS:
	{
		std::vector<FSagaSerializedMember> users{};

		ReceiveRespondUsersPacket(packet_buffer, users);

		UE_LOG(LogSagaFramework, Log, TEXT("Members: %d"), users.size());

		Instance->ClearUserList();
		for (auto& user : users)
		{
			Instance->AddUser(FSagaVirtualUser
				{
					user.id, user.nickname
				});

			UE_LOG(LogSagaFramework, Log, TEXT("User (%d): %s"), user.id, user.nickname);
		}
	}
	break;

	case EPacketProtocol::SC_FAILED_GAME_START:
	{
		FSaga_SC_FailedGameStartingPacket pk{};
		auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaFramework, Log, TEXT("Failed to start game due to %d"), pk.errCause);
	}
	break;

	case EPacketProtocol::SC_GAME_GETTING_READY:
	{
		//SC_ReadyForGamePacket pk{};
		//auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaFramework, Log, TEXT("Now start loading game..."));
	}
	break;

	case EPacketProtocol::SC_GAME_START:
	{
		//SC_GameStartPacket pk{};
		//auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaFramework, Log, TEXT("Now start game..."));
	}
	break;

	case EPacketProtocol::SC_CREATE_PLAYER:
	{
		FSaga_SC_CreatePlayerPacket pk{};
		auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaFramework, Log, TEXT("A client %d is created"), pk.clientId);

		Instance->AddUser(FSagaVirtualUser{ pk.clientId, TEXT("Name") });
	}
	break;

	case EPacketProtocol::SC_REMOVE_PLAYER:
	{
		FSaga_SC_DestroyPlayerPacket pk{};
		auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaFramework, Log, TEXT("A client %d is destroyed(disconnected)"), pk.clientId);
	}
	break;

	case EPacketProtocol::SC_MOVE_CHARACTER:
	{
		int32 client_id{};
		float x, y, z;

		ReceivePositionPacket(packet_buffer, client_id, x, y, z);

		UE_LOG(LogSagaFramework, Log, TEXT("Client id %d: pos(%f,%f,%f)"), client_id, x, y, z);
		UE_LOG(LogSagaFramework, Log, TEXT("Client id pos"));
	}
	break;

	case EPacketProtocol::SC_UPDATE_CHARACTER:
	{
	}
	break;

	case EPacketProtocol::SC_RPC:
	{
		FSaga_SC_RpcPacket pk{};

		wchar_t buffer[sizeof(pk.rpcScript) / sizeof(wchar_t)]{};
		std::copy(std::cbegin(pk.rpcScript), std::cend(pk.rpcScript), std::begin(buffer));

		UE_LOG(LogSagaFramework, Log, TEXT("RPC from client %d: %s(%lld))"), pk.clientId, pk.rpcScript, pk.rpcArgument);
	}
	break;
	}
}
