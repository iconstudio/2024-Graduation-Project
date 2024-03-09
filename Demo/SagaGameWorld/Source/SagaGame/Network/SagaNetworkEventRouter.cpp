#include "SagaNetworkEventRouter.h"
#include "SagaNetwork.h"
#include "SagaServerPacketPrefabs.h"
#include "SagaLocalPlayer.h"
#include "SagaPacketProcessor.h"

void
saga::EventRouter(const std::byte* packet_buffer
	, EPacketProtocol protocol
	, std::int16_t packet_size)
{
	auto instance = saga::USagaNetwork::Instance();
	auto& socket = instance->LocalSocket;

	switch (protocol)
	{
		case EPacketProtocol::SC_SIGNIN_SUCCESS:
		{
			int32 my_id{};
			auto offset = ReceiveSignInSucceedPacket(packet_buffer, my_id);

			UE_LOG(LogNet, Log, TEXT("Local player's id is %d"), my_id);
		}
		break;

		case EPacketProtocol::SC_SIGNIN_FAILURE:
		{
			int32 error{};
			auto offset = ReceiveSignInFailurePacket(packet_buffer, error);

			UE_LOG(LogNet, Log, TEXT("Local player can't get an id from server due to %d"), error);
		}
		break;

		case EPacketProtocol::SC_ROOM_CREATED:
		{
			int32 room_id{};
			auto offset = ReceiveRoomCreatedPacket(packet_buffer, room_id);

			instance->CurrentRoomId = room_id;

			UE_LOG(LogNet, Log, TEXT("A room %d is created"), room_id);
		}
		break;

		case EPacketProtocol::SC_ROOM_CREATE_FAILED:
		{
			RoomContract error{};
			auto offset = ReceiveRoomCreationFailedPacket(packet_buffer, error);

			const auto msg = std::to_wstring(error);
			UE_LOG(LogNet, Log, TEXT("Could not create a room due to %d"), msg.data());
		}
		break;

		case EPacketProtocol::SC_ROOM_JOINED:
		{
			int32 newbie_id{};
			int32 room_id{};
			auto offset = ReceiveRoomJoinedPacket(packet_buffer, newbie_id, room_id);

			if (newbie_id == instance->MyId)
			{
				instance->CurrentRoomId = room_id;

				UE_LOG(LogNet, Log, TEXT("Local client has joined to the room %d"), room_id);
			}
			else
			{
				instance->AddClient(FSagaLocalPlayer{ id, nickname });

				UE_LOG(LogNet, Log, TEXT("Client %d has joined to the room %d"), newbie_id, room_id);
			}
		}
		break;

		case EPacketProtocol::SC_ROOM_JOIN_FAILED:
		{
			RoomContract error{};
			auto offset = ReceiveRoomJoinFailedPacket(packet_buffer, error);

			const auto msg = std::to_wstring(error);
			UE_LOG(LogNet, Log, TEXT("Failed to join to a room due to %s"), msg.data());
		}
		break;

		case EPacketProtocol::SC_ROOM_LEFT:
		{
			int32 left_client{};
			auto offset = ReceiveRoomLeftPacket(packet_buffer, left_client);

			UE_LOG(LogNet, Log, TEXT("Client %d has been left from room"), left_client);
		}
		break;

		case EPacketProtocol::SC_RESPOND_VERSION:
		{
			SC_RespondVersionPacket pk{};
			auto offset = pk.Read(packet_buffer);

			UE_LOG(LogNet, Log, TEXT("Version: %s"), pk.gameVersion);
		}
		break;

		case EPacketProtocol::SC_RESPOND_ROOMS:
		{
			SC_RespondRoomsPacket pk{};
			auto offset = pk.Read(packet_buffer);

			auto& every_room = pk.serializedRooms;
			UE_LOG(LogNet, Log, TEXT("Rooms: %d"), every_room.size());
		}
		break;

		case EPacketProtocol::SC_RESPOND_USERS:
		{
			SC_RespondMembersPacket pk{};
			auto offset = pk.Read(packet_buffer);

			auto& members = pk.serializedMembers;
			for (auto& [id, nickname] : members)
			{
				instance->AddClient(FSagaLocalPlayer{ id, nickname });
			}

			UE_LOG(LogNet, Log, TEXT("Members: %d"), members.size());
		}
		break;

		case EPacketProtocol::SC_FAILED_GAME_START:
		{
			SC_FailedGameStartingPacket pk{};
			auto offset = pk.Read(packet_buffer);

			UE_LOG(LogNet, Log, TEXT("Failed to start game due to %d"), pk.errCause);
		}
		break;

		case EPacketProtocol::SC_GAME_GETTING_READY:
		{
			SC_ReadyForGamePacket pk{};
			auto offset = pk.Read(packet_buffer);

			UE_LOG(LogNet, Log, TEXT("Now start loading game..."));
		}
		break;

		case EPacketProtocol::SC_GAME_START:
		{
			SC_GameStartPacket pk{};
			auto offset = pk.Read(packet_buffer);

			UE_LOG(LogNet, Log, TEXT("Now start game..."));
		}
		break;

		case EPacketProtocol::SC_CREATE_PLAYER:
		{
			SC_CreatePlayerPacket pk{};
			auto offset = pk.Read(packet_buffer);

			UE_LOG(LogNet, Log, TEXT("A player %d is created"), pk.clientId);

			instance->AddClient(FSagaLocalPlayer{ pk.clientId, TEXT("Name") });
		}
		break;

		case EPacketProtocol::SC_REMOVE_PLAYER:
		{
			SC_DestroyPlayerPacket pk{};
			auto offset = pk.Read(packet_buffer);

			UE_LOG(LogNet, Log, TEXT("A player %d is destroyed(disconnected)"), pk.clientId);
		}
		break;

		case EPacketProtocol::SC_MOVE_CHARACTER:
		{
			SC_UpdatePositionPacket pk{ 0, 0, 0, 0 };
			auto offset = pk.Read(packet_buffer);

			UE_LOG(LogNet, Log, TEXT("Player id %d: pos(%f,%f,%f)"), pk.clientId, pk.x, pk.y, pk.z);
			UE_LOG(LogNet, Log, TEXT("Player id pos"));
		}
		break;

		case EPacketProtocol::SC_UPDATE_CHARACTER:
		{
		}
		break;
	}
	//FKey key;
	//FString KeyString = key.ToString();
	//TCHAR* SerializedChar = KeyString.GetCharArray().GetData();
	//int32 Size = FCString::Strlen(SerializedChar) + 1;
	//int32 Sent = 0;

	//// 데이터 전송
	//bool Successful = SagaClientSocket->Send((uint8*)TCHAR_TO_UTF8(SerializedChar), Size, Sent);

	//if (id_packet.myProtocol != EPacketProtocol::SC_SIGNIN_SUCCESS or id_packet.mySize <= 0)
	{
		// throw "error!";
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
	//RawSend(socket, position_raw_buffer, FSagaPacket_CS_ClientPosition::WannabeSize());

	// #3-b
	// 공유 포인터 사용
	//auto position_buffer = pk_position.Serialize();
	//Send(MakeShareable(LocalSocket), position_buffer, FSagaPacket_CS_ClientPosition::WannabeSize());
}
