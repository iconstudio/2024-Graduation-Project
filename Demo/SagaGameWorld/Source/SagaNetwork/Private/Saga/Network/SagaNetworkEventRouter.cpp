#include "Saga/Network/SagaNetworkSubSystem.h"
#include "Saga/Network/SagaPacketProcessor.h"
#include "Saga/Network/SagaGameContract.h"
#include "Player/UserTeam.h"

void
USagaNetworkSubSystem::RouteEvents(const std::byte* packet_buffer, EPacketProtocol protocol, int16 packet_size)
{
	switch (protocol)
	{
	case EPacketProtocol::SC_SIGNIN_SUCCESS:
	{
		int32 my_id{};
		saga::ReceiveSignInSucceedPacket(packet_buffer, my_id);

		UE_LOG(LogSagaNetwork, Log, TEXT("Local client's id is %d"), my_id);

		CallFunctionOnGameThread([this, my_id]()
			{
				SetLocalUserId(my_id);

				BroadcastOnConnected();
			}
		);
	}
	break;

	case EPacketProtocol::SC_SIGNIN_FAILURE:
	{
		int32 error{};
		saga::ReceiveSignInFailurePacket(packet_buffer, error);

		CallFunctionOnGameThread([this]()
			{
				SetLocalUserId(-1);

				BroadcastOnFailedToConnect(ESagaConnectionContract::SignInFailed);
			}
		);
	}
	break;

	case EPacketProtocol::SC_ROOM_CREATED:
	{
		int32 room_id{};
		saga::ReceiveRoomCreatedPacket(packet_buffer, room_id);

		CallFunctionOnGameThread([this, room_id]()
			{
				SetCurrentRoomId(room_id);

				BroadcastOnRoomCreated(room_id);
			}
		);
	}
	break;

	case EPacketProtocol::SC_ROOM_CREATE_FAILED:
	{
		ERoomContract error{};
		saga::ReceiveRoomCreationFailedPacket(packet_buffer, error);

		const auto msg = std::to_wstring(error);
		UE_LOG(LogSagaNetwork, Log, TEXT("Could not create a room due to %s"), msg.data());
	}
	break;

	case EPacketProtocol::SC_ROOM_JOINED:
	{
		int32 newbie_id{};
		int32 room_id{};
		saga::ReceiveRoomJoinedPacket(packet_buffer, newbie_id, room_id);

		if (newbie_id == GetLocalUserId())
		{
			UE_LOG(LogSagaNetwork, Log, TEXT("Local client has joined to the room %d"), room_id);

			CallFunctionOnGameThread([this, room_id, newbie_id]()
				{
					SetCurrentRoomId(room_id);

					BroadcastOnJoinedRoom(newbie_id);
				}
			);
		}
		else
		{
			UE_LOG(LogSagaNetwork, Log, TEXT("Client %d has joined to the room %d"), newbie_id, room_id);

			CallFunctionOnGameThread([this, newbie_id]()
				{
					AddUser(FSagaVirtualUser{ newbie_id, TEXT("Member") });

					BroadcastOnJoinedRoom(newbie_id);
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
		UE_LOG(LogSagaNetwork, Log, TEXT("Failed to join to a room due to %s"), msg.data());
	}
	break;

	case EPacketProtocol::SC_ROOM_LEFT:
	{
		int32 left_client_id{};
		saga::ReceiveRoomLeftPacket(packet_buffer, left_client_id);

		if (left_client_id == GetLocalUserId())
		{
			CallFunctionOnGameThread([this]()
				{
					SetCurrentRoomId(-1);
					ClearUserList();

					BroadcastOnLeftRoomBySelf();
				}
			);
		}
		else
		{
			CallFunctionOnGameThread([this, left_client_id]()
				{
					RemoveUser(left_client_id);

					BroadcastOnLeftRoom(left_client_id);
				}
			);
		}
	}
	break;

	case EPacketProtocol::SC_RESPOND_VERSION:
	{
		wchar_t version_string[16]{};

		saga::ReceiveRespondVersionPacket(packet_buffer, version_string, 16);

		CallPureFunctionOnGameThread([this, version_string]()
			{
				BroadcastOnRespondVersion(version_string);
			}
		);
	}
	break;

	case EPacketProtocol::SC_RESPOND_ROOMS:
	{
		std::vector<saga::datagrams::SerializedRoom> rooms{};

		saga::ReceiveRespondRoomsPacket(packet_buffer, rooms);

		UE_LOG(LogSagaNetwork, Log, TEXT("Number of rooms: %d"), rooms.size());

		CallFunctionOnGameThread([this, tr_rooms = std::move(rooms)]()
			{
				ClearRoomList();
				for (auto& room : tr_rooms)
				{
					AddRoom(FSagaVirtualRoom
						{
							room.id, room.title, static_cast<int>(room.members)
						});
					UE_LOG(LogSagaNetwork, Log, TEXT("Room (%d): %s (%d/4)"), room.id, room.title, room.members);
				}

				BroadcastOnUpdateRoomList(everyRooms);
			}
		);
	}
	break;

	case EPacketProtocol::SC_RESPOND_USERS:
	{
		std::vector<saga::datagrams::SerializedMember> users{};

		saga::ReceiveRespondUsersPacket(packet_buffer, users);

		UE_LOG(LogSagaNetwork, Log, TEXT("Members: %d"), users.size());

		CallFunctionOnGameThread([this, tr_users = std::move(users)]()
			{
				ClearUserList();
				for (auto& user : tr_users)
				{
					const auto team_id = static_cast<EUserTeam>(user.team_id);

					AddUser(FSagaVirtualUser
						{
							user.id,
							user.nickname,
							nullptr,
							team_id
						});

					auto str = UEnum::GetValueAsString(team_id);
					UE_LOG(LogSagaNetwork, Log, TEXT("User (%d): %s in team '%s'"), user.id, user.nickname, *str);
				}

				BroadcastOnUpdateMembers(everyUsers);
			}
		);
	}
	break;

	case EPacketProtocol::SC_FAILED_GAME_START:
	{
		saga::SC_FailedGameStartingPacket pk{};
		auto offset = pk.Read(packet_buffer);

		const ESagaGameContract cause = static_cast<ESagaGameContract>(static_cast<uint8>(pk.errCause));
		auto str = UEnum::GetValueAsString(cause);

		UE_LOG(LogSagaNetwork, Log, TEXT("Failed to start game due to %s"), *str);

		CallPureFunctionOnGameThread([this, cause]()
			{
				BroadcastOnFailedToStartGame(cause);
			}
		);
	}
	break;

	case EPacketProtocol::SC_GAME_GETTING_READY:
	{
		//SC_ReadyForGamePacket pk{};
		//auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaNetwork, Log, TEXT("Now start loading game..."));

		CallPureFunctionOnGameThread([this]()
			{
				BroadcastOnGetPreparedGame();
			}
		);
	}
	break;

	case EPacketProtocol::SC_GAME_START:
	{
		//SC_GameStartPacket pk{};
		//auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaNetwork, Log, TEXT("Now start game..."));

		CallPureFunctionOnGameThread([this]()
			{
				BroadcastOnStartGame();
			}
		);
	}
	break;

	case EPacketProtocol::SC_CREATE_PLAYER:
	{
		saga::SC_CreatePlayerPacket pk{};
		auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaNetwork, Log, TEXT("A client %d is created"), pk.clientId);

		CallFunctionOnGameThread([this, pk]()
			{
			}
		);
	}
	break;

	case EPacketProtocol::SC_REMOVE_PLAYER:
	{
		saga::SC_DestroyPlayerPacket pk{};
		auto offset = pk.Read(packet_buffer);

		UE_LOG(LogSagaNetwork, Log, TEXT("A client %d is destroyed(disconnected)"), pk.clientId);

		CallFunctionOnGameThread([this, pk]()
			{
			}
		);
	}
	break;

	case EPacketProtocol::SC_MOVE_CHARACTER:
	{
		int32 client_id{};
		float x{}, y{}, z{};

		saga::ReceivePositionPacket(packet_buffer, client_id, x, y, z);

		UE_LOG(LogSagaNetwork, Log, TEXT("Client id %d: pos(%f,%f,%f)"), client_id, x, y, z);

		CallFunctionOnGameThread([this, client_id, x, y, z]()
			{
				BroadcastOnUpdatePosition(client_id, x, y, z);
			}
		);
	}
	break;

	case EPacketProtocol::SC_SET_TEAM:
	{
		int32 client_id{};
		bool is_red_team{};

		saga::ReceiveTeamChangerPacket(packet_buffer, client_id, is_red_team);

		UE_LOG(LogSagaNetwork, Log, TEXT("Client %d's team changed to %s"), client_id, is_red_team ? TEXT("Red") : TEXT("Blue"));

		CallFunctionOnGameThread([this, client_id, is_red_team]()
			{
				for (auto& member : everyUsers)
				{
					if (member.MyID == client_id)
					{
						member.myTeam = is_red_team ? EUserTeam::Red : EUserTeam::Blue;
					}
				}

				BroadcastOnTeamChanged(client_id, is_red_team);
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

		UE_LOG(LogSagaNetwork, Log, TEXT("RPC from client %d: %s(%lld))"), pk.clientId, pk.rpcScript, pk.rpcArgument);
	}
	break;
	}
}
