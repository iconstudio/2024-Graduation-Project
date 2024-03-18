﻿#pragma once
#include "SagaFramework.h"
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "Saga/Network/SagaBasicPacket.h"
#include "Saga/Network/SagaPacketProtocol.h"
#include "Saga/Network/SagaRoomContract.h"
#include "Saga/Network/SagaPacketHelper.inl"
#include "SagaServerPacketPrefabs.generated.h"

USTRUCT(BlueprintType)
struct SAGAFRAMEWORK_API FSagaSerializedRoom
{
	GENERATED_BODY()

public:
	static inline constexpr size_t nameLength = 16;

	int32 id;
	wchar_t title[nameLength];
	size_t members;
};

USTRUCT(BlueprintType)
struct SAGAFRAMEWORK_API FSagaSerializedMember
{
	GENERATED_BODY()

public:
	static inline constexpr size_t nameLength = 16;

	int32 id;
	wchar_t nickname[nameLength];
};

/// <summary>
/// Broadcasted RPC packet for server
/// </summary>
/// <param name="clientId">- An id of the sender client</param>
/// <param name="rpcScript">- A descriptor for rpc msg</param>
/// <param name="rpcArgument">- Single rpc argument</param>
/// <remarks>Server would send it to the client</remarks>
struct FSaga_SC_RpcPacket : public FSagaBasicPacket
{
	using Super = FSagaBasicPacket;

	static inline constexpr size_t msgLength = 10;

	[[nodiscard]]
	static consteval size_t WannabeSize() noexcept
	{
		return Super::MinSize() + sizeof(clientId) + sizeof(rpcScript) + sizeof(rpcArgument);
	}

	[[nodiscard]]
	static consteval ptrdiff_t SignedWannabeSize() noexcept
	{
		return static_cast<ptrdiff_t>(WannabeSize());
	}

	constexpr FSaga_SC_RpcPacket()
		noexcept
		: Super(EPacketProtocol::SC_RPC, SignedWannabeSize())
		, clientId(-1), rpcScript()
		, rpcArgument()
	{
	}

	explicit constexpr FSaga_SC_RpcPacket(int32 id, const wchar_t* begin, const wchar_t* end)
		noexcept
		: Super(EPacketProtocol::SC_RPC, SignedWannabeSize())
		, clientId(id), rpcScript()
		, rpcArgument()
	{
		std::copy(begin, end, rpcScript);
	}

	explicit constexpr FSaga_SC_RpcPacket(int32 id, const wchar_t* nts, const size_t length)
		noexcept
		: Super(EPacketProtocol::SC_RPC, SignedWannabeSize())
		, clientId(id), rpcScript()
		, rpcArgument()
	{
		std::copy_n(nts, std::min(length, msgLength), rpcScript);
	}

	template<size_t Length>
	explicit constexpr FSaga_SC_RpcPacket(int32 id, const wchar_t(&str)[Length])
		noexcept
		: Super(EPacketProtocol::SC_RPC, SignedWannabeSize())
		, clientId(id), rpcScript()
		, rpcArgument()
	{
		std::copy_n(str, std::min(Length, msgLength), rpcScript);
	}

	template<size_t Length>
	explicit constexpr FSaga_SC_RpcPacket(int32 id, wchar_t(&& str)[Length])
		noexcept
		: Super(EPacketProtocol::SC_RPC, SignedWannabeSize())
		, clientId(id), rpcScript()
		, rpcArgument()
	{
		std::move(str, str + std::min(Length, msgLength), rpcScript);
	}

	MAKE_SERIALIZE_METHOD();
	MAKE_RW_METHODS();

	int32 clientId;
	wchar_t rpcScript[msgLength];
	long long rpcArgument;
};
/// <summary>
/// Getting game ready notification packet for server
/// </summary>
/// <remarks>Server would send it to the client</remarks>
MAKE_EMPTY_PACKET(FSaga_SC_ReadyForGamePacket, EPacketProtocol::SC_GAME_GETTING_READY);
/// <summary>
/// Game starting notification packet for server
/// </summary>
/// <remarks>Server would send it to the client</remarks>
MAKE_EMPTY_PACKET(FSaga_SC_GameStartPacket, EPacketProtocol::SC_GAME_START);
/// <summary>
/// Failed to start game notification packet for server
/// </summary>
/// <param name="errCause">- Cause of the failure</param>
/// <remarks>Server would send it to the client</remarks>
MAKE_EMPTY_PACKET_1VAR(FSaga_SC_FailedGameStartingPacket, EPacketProtocol::SC_FAILED_GAME_START, int, errCause, error, true);
/// <summary>
/// Creating a client packet for server
/// </summary>
/// <param name="clientId">- An id of client</param>
/// <param name="roomId"/>
/// <remarks>Server would send it to the client</remarks>
struct FSaga_SC_RespondVersionPacket : public FSagaBasicPacket
{
	using Super = FSagaBasicPacket;

	static inline constexpr size_t versionLength = 10;

	[[nodiscard]]
	static consteval size_t WannabeSize() noexcept
	{
		return Super::MinSize() + sizeof(gameVersion);
	}

	[[nodiscard]]
	static consteval ptrdiff_t SignedWannabeSize() noexcept
	{
		return static_cast<ptrdiff_t>(WannabeSize());
	}

	constexpr FSaga_SC_RespondVersionPacket() noexcept
		: Super(EPacketProtocol::CS_SIGNIN, SignedWannabeSize())
		, gameVersion()
	{
	}

	explicit constexpr FSaga_SC_RespondVersionPacket(const wchar_t* begin, const wchar_t* end)
		: Super(EPacketProtocol::CS_SIGNIN, SignedWannabeSize())
		, gameVersion()
	{
		std::copy(begin, end, gameVersion);
	}

	explicit constexpr FSaga_SC_RespondVersionPacket(const wchar_t* nts, const size_t length)
		: Super(EPacketProtocol::CS_SIGNIN, SignedWannabeSize())
		, gameVersion()
	{
		std::copy_n(nts, std::min(length, versionLength), gameVersion);
	}

	template<size_t Length>
	explicit constexpr FSaga_SC_RespondVersionPacket(const wchar_t(&str)[Length])
		: Super(EPacketProtocol::CS_SIGNIN, SignedWannabeSize())
		, gameVersion()
	{
		std::copy_n(str, std::min(Length, versionLength), gameVersion);
	}

	template<size_t Length>
	explicit constexpr FSaga_SC_RespondVersionPacket(wchar_t(&& str)[Length])
		: Super(EPacketProtocol::CS_SIGNIN, SignedWannabeSize())
		, gameVersion()
	{
		std::move(str, str + std::min(Length, versionLength), gameVersion);
	}

	MAKE_SERIALIZE_METHOD();
	MAKE_RW_METHODS();

	wchar_t gameVersion[versionLength];
};
/// <summary>
/// Show rooms response packet for server
/// </summary>
/// <param name="serializedRooms">- Serialized every room</param>
/// <remarks>Server would send it to the client</remarks>
struct FSaga_SC_RespondRoomsPacket : public FSagaBasicPacket
{
	using Super = FSagaBasicPacket;

	[[nodiscard]]
	static consteval size_t MaxSize() noexcept
	{
		return Super::MinSize() + sizeof(FSagaSerializedRoom) * 20 + sizeof(std::vector<FSagaSerializedRoom>::size_type);
	}

	[[nodiscard]]
	constexpr size_t WannabeSize() const noexcept
	{
		return Super::MinSize() + sizeof(FSagaSerializedRoom) * serializedRooms.size() + sizeof(std::vector<FSagaSerializedRoom>::size_type);
	}

	[[nodiscard]]
	constexpr ptrdiff_t SignedWannabeSize() const noexcept
	{
		return static_cast<ptrdiff_t>(WannabeSize());
	}

	constexpr FSaga_SC_RespondRoomsPacket() noexcept
		: Super(EPacketProtocol::SC_RESPOND_ROOMS, static_cast<int16>(SignedWannabeSize()))
		, serializedRooms()
	{
	}

	constexpr void AddMember(int32 room_id, std::wstring_view title, size_t members_count)
	{
		FSagaSerializedRoom room{ room_id };

		auto it = room.title;
		for (auto ch : title)
		{
			*it = ch;

			if (++it == room.title + sizeof(room.title)) break;
		}
		room.members = members_count;

		serializedRooms.emplace_back(std::move(room));
		mySize = static_cast<int16>(WannabeSize());
	}

	MAKE_SERIALIZE_METHOD();
	MAKE_RW_METHODS();

	std::vector<FSagaSerializedRoom> serializedRooms;
};
/// <summary>
/// Room members response packet for server
/// </summary>
/// <param name="serializedMembers">- Serialized members in the room</param>
/// <remarks>Server would send it to the client</remarks>
struct FSaga_SC_RespondMembersPacket : public FSagaBasicPacket
{
	using Super = FSagaBasicPacket;

	[[nodiscard]]
	static consteval size_t MaxSize() noexcept
	{
		return Super::MinSize() + sizeof(FSagaSerializedMember) * 6 + sizeof(std::vector<FSagaSerializedMember>::size_type);
	}

	[[nodiscard]]
	constexpr size_t WannabeSize() const noexcept
	{
		return Super::MinSize() + sizeof(FSagaSerializedMember) * serializedMembers.size() + sizeof(std::vector<FSagaSerializedMember>::size_type);
	}

	[[nodiscard]]
	constexpr ptrdiff_t SignedWannabeSize() const noexcept
	{
		return static_cast<ptrdiff_t>(WannabeSize());
	}

	constexpr FSaga_SC_RespondMembersPacket() noexcept
		: Super(EPacketProtocol::SC_RESPOND_USERS, static_cast<int16>(SignedWannabeSize()))
		, serializedMembers()
	{
	}

	constexpr void AddMember(int32 id, std::wstring_view name)
	{
		FSagaSerializedMember member{ id };

		auto it = member.nickname;
		for (auto ch : name)
		{
			*it = ch;

			if (++it == member.nickname + sizeof(member.nickname)) break;
		}

		serializedMembers.emplace_back(std::move(member));
		mySize = static_cast<int16>(WannabeSize());
	}

	MAKE_SERIALIZE_METHOD();
	MAKE_RW_METHODS();

	std::vector<FSagaSerializedMember> serializedMembers;
};
/// <summary>
/// Room created notification packet for server
/// </summary>
/// <param name="roomId">- An id of the created room</param>
/// <remarks>Server would send it to the client</remarks>
MAKE_EMPTY_PACKET_1VAR(FSaga_SC_RoomCreatedPacket, EPacketProtocol::SC_ROOM_CREATED, int32, roomId, room_id, true);
/// <summary>
/// Failed to join to a room packet for server
/// </summary>
/// <param name="errCause">Reason of couldn't join to the room</param>
/// <remarks>Server would send it to the client</remarks>
MAKE_EMPTY_PACKET_1VAR(FSaga_SC_RoomCreationFailedPacket, EPacketProtocol::SC_ROOM_CREATE_FAILED, ERoomContract, errCause, cause, true);
/// <summary>
/// Joined to a room packet for server
/// </summary>
/// <param name="clientId">- An id of client</param>
/// <param name="roomId">- An id of the room</param>
/// <remarks>Server would send it to the client</remarks>
MAKE_EMPTY_PACKET_2VAR_WITH_DEFAULT(FSaga_SC_RoomJoinedPacket, EPacketProtocol::SC_ROOM_JOINED, int32, clientId, user_id, -1, int32, roomId, room_id, -1);
/// <summary>
/// Failed to join to a room packet for server
/// </summary>
/// <param name="errCause">- Reason of couldn't join to the room</param>
/// <remarks>Server would send it to the client</remarks>
MAKE_EMPTY_PACKET_1VAR(FSaga_SC_RoomJoinFailedPacket, EPacketProtocol::SC_ROOM_JOIN_FAILED, ERoomContract, errCause, cause, true);
/// <summary>
/// Room left packet for server
/// </summary>
/// <param name="clientId">- An id of client</param>
/// <remarks>Server would send it to the client</remarks>
MAKE_EMPTY_PACKET_1VAR_WITH_DEFAULT(FSaga_SC_RoomLeftPacket, EPacketProtocol::SC_ROOM_LEFT, int32, clientId, user_id, -1);
/// <summary>
/// Creating a client packet for server
/// </summary>
/// <param name="clientId">- An id of client</param>
/// <param name="roomId"/>
/// <remarks>Server would send it to the client</remarks>
struct FSaga_SC_CreatePlayerPacket : public FSagaBasicPacket
{
	using Super = FSagaBasicPacket;

	static inline constexpr size_t nickNameLength = 16;

	[[nodiscard]]
	static consteval size_t WannabeSize() noexcept
	{
		return Super::MinSize() + sizeof(clientId) + sizeof(userName);
	}

	[[nodiscard]]
	static consteval ptrdiff_t SignedWannabeSize() noexcept
	{
		return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(clientId) + sizeof(userName));
	}

	constexpr FSaga_SC_CreatePlayerPacket() noexcept
		: FSaga_SC_CreatePlayerPacket(-1)
	{
	}

	constexpr FSaga_SC_CreatePlayerPacket(int32 id) noexcept
		: Super(EPacketProtocol::SC_CREATE_PLAYER, SignedWannabeSize())
		, clientId(id), userName()
	{
	}

	MAKE_SERIALIZE_METHOD();
	MAKE_RW_METHODS();

	int32 clientId;
	wchar_t userName[nickNameLength];
};
/// <summary>
/// Remove a certain client packet for server
/// </summary>
/// <param name="clientId">- An id of client</param>
/// <remarks>Server would send it to the client</remarks>
MAKE_EMPTY_PACKET_1VAR(FSaga_SC_DestroyPlayerPacket, EPacketProtocol::SC_REMOVE_PLAYER, int32, clientId, user_id, true);
/// <summary>
/// Assigning ID to client packet for server
/// </summary>
/// <param name="clientId">- An id of client</param>
/// <remarks>Server would send it to the client</remarks>
MAKE_EMPTY_PACKET_1VAR_WITH_DEFAULT(FSaga_SC_SucceedSignInPacket, EPacketProtocol::SC_SIGNIN_SUCCESS, int32, clientId, user_id, -1);
/// <summary>
/// Assigning ID to client packet for server
/// </summary>
/// <param name="errCause">- Cause of the failure</param>
/// <remarks>Server would send it to the client</remarks>
MAKE_EMPTY_PACKET_1VAR(FSaga_SC_FailedSignInPacket, EPacketProtocol::SC_SIGNIN_FAILURE, int, errCause, cause, true);
/// <summary>
/// Position packet for server
/// </summary>
/// <param name="clientId">- Target player's id</param>
/// <param name="x"/>
/// <param name="y"/>
/// <param name="z"/>
/// <remarks>Server would broadcast it to clients</remarks>
struct FSaga_SC_UpdatePositionPacket : public FSagaBasicPacket
{
	using Super = FSagaBasicPacket;

	[[nodiscard]]
	static consteval size_t WannabeSize() noexcept
	{
		return Super::MinSize() + sizeof(int) + sizeof(float) * 3;
	}

	[[nodiscard]]
	static consteval ptrdiff_t SignedWannabeSize() noexcept
	{
		return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(int) + sizeof(float) * 3);
	}

	constexpr FSaga_SC_UpdatePositionPacket()
		: FSaga_SC_UpdatePositionPacket(-1, 0, 0, 0)
	{
	}

	constexpr FSaga_SC_UpdatePositionPacket(int32 id, float px, float py, float pz) noexcept
		: Super(EPacketProtocol::SC_MOVE_CHARACTER, SignedWannabeSize())
		, clientId(id), x(px), y(py), z(pz)
	{
	}

	MAKE_SERIALIZE_METHOD();
	MAKE_RW_METHODS();

	int32 clientId;
	float x, y, z;
};
