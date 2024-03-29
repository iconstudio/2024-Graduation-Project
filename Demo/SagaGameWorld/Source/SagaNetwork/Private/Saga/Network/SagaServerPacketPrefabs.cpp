﻿#include "Saga/Network/SagaServerPacketPrefabs.h"
#include "Saga/Serializer.h"

#include <algorithm>

std::unique_ptr<std::byte[]>
saga::sc::SC_RpcPacket::Serialize()
const
{
	return saga::Serializes(myProtocol, mySize, clientId, std::wstring_view{ rpcScript, msgLength }, rpcArgument);
}

std::byte*
saga::sc::SC_RpcPacket::Write(std::byte* buffer)
const
{
	return saga::Serialize(saga::Serialize(saga::Serialize(Super::Write(buffer), clientId), std::wstring_view{ rpcScript, msgLength }), rpcArgument);
}

const std::byte*
saga::sc::SC_RpcPacket::Read(const std::byte* buffer)
{
	return saga::Deserialize(saga::Deserialize(saga::Deserialize(Super::Read(buffer), clientId), msgLength, rpcScript), rpcArgument);
}

std::unique_ptr<std::byte[]>
saga::sc::SC_RespondVersionPacket::Serialize()
const
{
	return saga::Serializes(myProtocol, mySize, std::wstring_view{ gameVersion, versionLength });
}

std::byte*
saga::sc::SC_RespondVersionPacket::Write(std::byte* buffer)
const
{
	return saga::Serialize(Super::Write(buffer), std::wstring_view{ gameVersion, versionLength });
}

const std::byte*
saga::sc::SC_RespondVersionPacket::Read(const std::byte* buffer)
{
	return saga::Deserialize(Super::Read(buffer), versionLength, gameVersion);
}

std::unique_ptr<std::byte[]>
saga::sc::SC_RespondRoomsPacket::Serialize()
const
{
	std::unique_ptr<std::byte[]> buffer = std::make_unique<std::byte[]>(WannabeSize());

	Write(buffer.get());

	return std::move(buffer);
}

std::byte*
saga::sc::SC_RespondRoomsPacket::Write(std::byte* buffer)
const
{
	auto seek = saga::Serialize(saga::Serialize(buffer, myProtocol), static_cast<int16>(WannabeSize()));

	seek = saga::Serialize(seek, serializedRooms.size());

	for (auto& room : serializedRooms)
	{
		seek = saga::Serialize(seek, room.id);
		seek = saga::Serialize(seek, std::wstring_view{ room.title, room.nameLength });
		seek = saga::Serialize(seek, room.members);
	}

	return seek;
}

const std::byte*
saga::sc::SC_RespondRoomsPacket::Read(const std::byte* buffer)
{
	auto seek = Super::Read(buffer);

	size_t size{};
	seek = saga::Deserialize(seek, size);

	if (0 < size)
	{
		serializedRooms.clear();
		serializedRooms.resize(size);

		for (auto& room : serializedRooms)
		{
			seek = saga::Deserialize(seek, room.id);
			seek = saga::Deserialize(seek, room.nameLength, room.title);
			seek = saga::Deserialize(seek, room.members);
		}
	}

	return seek;
}

std::unique_ptr<std::byte[]>
saga::sc::SC_RespondMembersPacket::Serialize()
const
{
	std::unique_ptr<std::byte[]> buffer = std::make_unique<std::byte[]>(WannabeSize());

	Write(buffer.get());

	return std::move(buffer);
}

std::byte*
saga::sc::SC_RespondMembersPacket::Write(std::byte* buffer) const
{
	auto seek = saga::Serialize(saga::Serialize(buffer, myProtocol), static_cast<int16>(WannabeSize()));

	seek = saga::Serialize(seek, serializedMembers.size());

	for (auto& member : serializedMembers)
	{
		seek = saga::Serialize(seek, member.id);
		seek = saga::Serialize(seek, std::wstring_view{ member.nickname, member.nameLength });
	}

	return seek;
}

const std::byte*
saga::sc::SC_RespondMembersPacket::Read(const std::byte* buffer)
{
	auto seek = Super::Read(buffer);

	size_t size{};
	seek = saga::Deserialize(seek, size);

	if (0 < size)
	{
		serializedMembers.clear();
		serializedMembers.resize(size);

		for (auto& member : serializedMembers)
		{
			seek = saga::Deserialize(seek, member.id);
			seek = saga::Deserialize(seek, member.nameLength, member.nickname);
		}
	}

	return seek;
}

std::unique_ptr<std::byte[]>
saga::sc::SC_CreatePlayerPacket::Serialize()
const
{
	return saga::Serializes(myProtocol, mySize, clientId, std::wstring_view{ userName, nickNameLength });
}

std::byte*
saga::sc::SC_CreatePlayerPacket::Write(std::byte* buffer)
const
{
	return saga::Serializes(Super::Write(buffer), clientId, std::wstring_view{ userName, nickNameLength });
}

const std::byte*
saga::sc::SC_CreatePlayerPacket::Read(const std::byte* buffer)
{
	return saga::Deserialize(saga::Deserialize(Super::Read(buffer), clientId), nickNameLength, userName);
}

std::unique_ptr<std::byte[]>
saga::sc::SC_UpdatePositionPacket::Serialize()
const
{
	return saga::Serializes(myProtocol, mySize, clientId, x, y, z);
}

std::byte*
saga::sc::SC_UpdatePositionPacket::Write(std::byte* buffer)
const
{
	return saga::Serializes(Super::Write(buffer), clientId, x, y, z);
}

const std::byte*
saga::sc::SC_UpdatePositionPacket::Read(const std::byte* buffer)
{
	return saga::Deserialize(saga::Deserialize(saga::Deserialize(saga::Deserialize(Super::Read(buffer), clientId), x), y), z);
}

IMPL_SERIALIZE_METHOD(saga::sc::SC_FailedGameStartingPacket, errCause);
IMPL_READ_METHODS(saga::sc::SC_FailedGameStartingPacket, errCause);
IMPL_WRITE_METHODS_V1(saga::sc::SC_FailedGameStartingPacket, errCause);

IMPL_SERIALIZE_METHOD(saga::sc::SC_RoomCreatedPacket, roomId);
IMPL_READ_METHODS(saga::sc::SC_RoomCreatedPacket, roomId);
IMPL_WRITE_METHODS_V1(saga::sc::SC_RoomCreatedPacket, roomId);

IMPL_SERIALIZE_METHOD(saga::sc::SC_RoomCreationFailedPacket, errCause);
IMPL_READ_METHODS(saga::sc::SC_RoomCreationFailedPacket, errCause);
IMPL_WRITE_METHODS_V1(saga::sc::SC_RoomCreationFailedPacket, errCause);

IMPL_SERIALIZE_METHOD(saga::sc::SC_RoomJoinedPacket, clientId, roomId);
IMPL_READ_METHODS(saga::sc::SC_RoomJoinedPacket, clientId, roomId);
IMPL_WRITE_METHODS_V2(saga::sc::SC_RoomJoinedPacket, clientId, roomId);

IMPL_SERIALIZE_METHOD(saga::sc::SC_RoomJoinFailedPacket, errCause);
IMPL_READ_METHODS(saga::sc::SC_RoomJoinFailedPacket, errCause);
IMPL_WRITE_METHODS_V1(saga::sc::SC_RoomJoinFailedPacket, errCause);

IMPL_SERIALIZE_METHOD(saga::sc::SC_RoomLeftPacket, clientId);
IMPL_READ_METHODS(saga::sc::SC_RoomLeftPacket, clientId);
IMPL_WRITE_METHODS_V1(saga::sc::SC_RoomLeftPacket, clientId);

IMPL_SERIALIZE_METHOD(saga::sc::SC_DestroyPlayerPacket, clientId);
IMPL_READ_METHODS(saga::sc::SC_DestroyPlayerPacket, clientId);
IMPL_WRITE_METHODS_V1(saga::sc::SC_DestroyPlayerPacket, clientId);

IMPL_SERIALIZE_METHOD(saga::sc::SC_SucceedSignInPacket, clientId);
IMPL_READ_METHODS(saga::sc::SC_SucceedSignInPacket, clientId);
IMPL_WRITE_METHODS_V1(saga::sc::SC_SucceedSignInPacket, clientId);

IMPL_SERIALIZE_METHOD(saga::sc::SC_FailedSignInPacket, errCause);
IMPL_READ_METHODS(saga::sc::SC_FailedSignInPacket, errCause);
IMPL_WRITE_METHODS_V1(saga::sc::SC_FailedSignInPacket, errCause);

IMPL_SERIALIZE_METHOD(saga::sc::SC_SetTeamPacket, clientId, teamId);
IMPL_READ_METHODS(saga::sc::SC_SetTeamPacket, clientId, teamId);
IMPL_WRITE_METHODS_V2(saga::sc::SC_SetTeamPacket, clientId, teamId);
