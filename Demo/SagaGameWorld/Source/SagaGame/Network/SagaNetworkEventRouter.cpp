#include "SagaNetworkEventRouter.h"
#include "SagaNetwork.h"
#include "SagaVirtualUser.h"
#include "SagaServerPacketPrefabs.h"
#include "SagaPacketProcessor.h"

void
saga::EventRouter(const std::byte* packet_buffer
	, EPacketProtocol protocol
	, std::int16_t packet_size)
{
	auto& socket = USagaNetwork::GetLocalSocket();

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

			USagaNetwork::CurrentRoomId(room_id);

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

			if (newbie_id == USagaNetwork::LocalUserId())
			{
				USagaNetwork::CurrentRoomId(room_id);

				UE_LOG(LogNet, Log, TEXT("Local client has joined to the room %d"), room_id);
			}
			else
			{
				USagaNetwork::AddUser(FSagaVirtualUser{ newbie_id, TEXT("Newbie") });

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
				USagaNetwork::AddUser(FSagaVirtualUser{ id, nickname });
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

			USagaNetwork::AddUser(FSagaVirtualUser{ pk.clientId, TEXT("Name") });
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
}
