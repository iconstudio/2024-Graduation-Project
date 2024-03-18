#include "Saga/Network/SagaNetworkEventRouter.h"
#include "Saga/Network/SagaNetworkSubSystem.h"
#include "Saga/Network/SagaNetworkSystem.h"
#include "Saga/Network/SagaVirtualUser.h"
#include "Saga/Network/SagaVirtualRoom.h"
#include "Saga/Network/SagaServerPacketPrefabs.h"
#include "Saga/Network/SagaPacketProcessor.h"

void
saga::EventRouter(const std::byte* packet_buffer
	, EPacketProtocol protocol
	, int16 packet_size)
{
	auto& socket = USagaNetwork::GetLocalSocket();
	auto system = USagaNetwork::GetSubsystemInstance();

	switch (protocol)
	{
		case EPacketProtocol::SC_SIGNIN_SUCCESS:
		{
			int32 my_id{};
			ReceiveSignInSucceedPacket(packet_buffer, my_id);

			UE_LOG(LogNet, Log, TEXT("Local client's id is %d"), my_id);
			system->SetLocalUserId(my_id);
		}
		break;

		case EPacketProtocol::SC_SIGNIN_FAILURE:
		{
			int32 error{};
			ReceiveSignInFailurePacket(packet_buffer, error);

			UE_LOG(LogNet, Log, TEXT("Local client can't get an id from server due to %d"), error);
			system->SetLocalUserId(-1);
		}
		break;

		case EPacketProtocol::SC_ROOM_CREATED:
		{
			int32 room_id{};
			ReceiveRoomCreatedPacket(packet_buffer, room_id);

			system->SetCurrentRoomId(room_id);

			UE_LOG(LogNet, Log, TEXT("A room %d is created"), room_id);
			system->BroadcastOnRoomCreated(room_id);
		}
		break;

		case EPacketProtocol::SC_ROOM_CREATE_FAILED:
		{
			ERoomContract error{};
			ReceiveRoomCreationFailedPacket(packet_buffer, error);

			const auto msg = std::to_wstring(error);
			UE_LOG(LogNet, Log, TEXT("Could not create a room due to %d"), msg.data());
		}
		break;

		case EPacketProtocol::SC_ROOM_JOINED:
		{
			int32 newbie_id{};
			int32 room_id{};
			ReceiveRoomJoinedPacket(packet_buffer, newbie_id, room_id);

			if (newbie_id == system->GetLocalUserId())
			{
				system->SetCurrentRoomId(room_id);

				UE_LOG(LogNet, Log, TEXT("Local client has joined to the room %d"), room_id);
				system->BroadcastOnJoinedRoom(newbie_id);
			}
			else
			{
				USagaNetwork::AddUser(FSagaVirtualUser{ newbie_id, TEXT("Member") });

				UE_LOG(LogNet, Log, TEXT("Client %d has joined to the room %d"), newbie_id, room_id);
			}
		}
		break;

		case EPacketProtocol::SC_ROOM_JOIN_FAILED:
		{
			ERoomContract error{};
			ReceiveRoomJoinFailedPacket(packet_buffer, error);

			const auto msg = std::to_wstring(error);
			UE_LOG(LogNet, Log, TEXT("Failed to join to a room due to %s"), msg.data());
		}
		break;

		case EPacketProtocol::SC_ROOM_LEFT:
		{
			int32 left_client_id{};
			ReceiveRoomLeftPacket(packet_buffer, left_client_id);

			if (left_client_id == system->GetLocalUserId())
			{
				system->SetCurrentRoomId(-1);

				UE_LOG(LogNet, Log, TEXT("Local client has been left from room"));
				system->BroadcastOnLeftRoomBySelf();
			}
			else
			{
				UE_LOG(LogNet, Log, TEXT("Remote client %d has been left from room"), left_client_id);
				system->BroadcastOnLeftRoom(left_client_id);
			}
		}
		break;

		case EPacketProtocol::SC_RESPOND_VERSION:
		{
			wchar_t version_string[16]{};

			ReceiveRespondVersionPacket(packet_buffer, version_string, 16);

			UE_LOG(LogNet, Log, TEXT("Version: %s"), version_string);
			system->BroadcastOnRespondVersion(version_string);
		}
		break;

		case EPacketProtocol::SC_RESPOND_ROOMS:
		{
			std::vector<datagrams::SerializedRoom> rooms{};

			ReceiveRespondRoomsPacket(packet_buffer, rooms);

			UE_LOG(LogNet, Log, TEXT("Rooms: %d"), rooms.size());

			USagaNetwork::ClearRoomList();
			for (auto& room : rooms)
			{
				USagaNetwork::AddRoom(FSagaVirtualRoom
					{
						room.id, room.title, static_cast<int>(room.members)
					});
				UE_LOG(LogNet, Log, TEXT("Room (%d): %s (%d/4)"), room.id, room.title, room.members);
			}

			system->BroadcastOnUpdateRoomList(USagaNetwork::GetRoomList());
		}
		break;

		case EPacketProtocol::SC_RESPOND_USERS:
		{
			std::vector<datagrams::SerializedMember> users{};

			ReceiveRespondUsersPacket(packet_buffer, users);

			UE_LOG(LogNet, Log, TEXT("Members: %d"), users.size());

			USagaNetwork::ClearUserList();
			for (auto& user : users)
			{
				USagaNetwork::AddUser(FSagaVirtualUser
					{
						user.id, user.nickname
					});

				UE_LOG(LogNet, Log, TEXT("User (%d): %s"), user.id, user.nickname);
			}

			system->BroadcastOnUpdateMembers(USagaNetwork::GetUserList());
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
			SC_CreatePlayerPacket pk{};
			auto offset = pk.Read(packet_buffer);

			UE_LOG(LogNet, Log, TEXT("A client %d is created"), pk.clientId);

			USagaNetwork::AddUser(FSagaVirtualUser{ pk.clientId, TEXT("Name") });
		}
		break;

		case EPacketProtocol::SC_REMOVE_PLAYER:
		{
			SC_DestroyPlayerPacket pk{};
			auto offset = pk.Read(packet_buffer);

			UE_LOG(LogNet, Log, TEXT("A client %d is destroyed(disconnected)"), pk.clientId);
		}
		break;

		case EPacketProtocol::SC_MOVE_CHARACTER:
		{
			int32 client_id{};
			float x, y, z;

			ReceivePositionPacket(packet_buffer, client_id, x, y, z);

			UE_LOG(LogNet, Log, TEXT("Client id %d: pos(%f,%f,%f)"), client_id, x, y, z);
			UE_LOG(LogNet, Log, TEXT("Client id pos"));
		}
		break;

		case EPacketProtocol::SC_UPDATE_CHARACTER:
		{
		}
		break;

		case EPacketProtocol::SC_RPC:
		{
			SC_RpcPacket pk{};

			wchar_t buffer[sizeof(pk.rpcScript) / sizeof(wchar_t)]{};
			std::copy(std::cbegin(pk.rpcScript), std::cend(pk.rpcScript), std::begin(buffer));

			UE_LOG(LogNet, Log, TEXT("RPC from client %d: %s(%lld))"), pk.clientId, pk.rpcScript, pk.rpcArgument);
		}
		break;
	}
}
