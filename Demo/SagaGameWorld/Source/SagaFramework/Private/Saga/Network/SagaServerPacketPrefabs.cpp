#include "Saga/Network/SagaServerPacketPrefabs.h"
#include "Saga/Serializer.h"

#include <algorithm>

TUniquePtr<uint8[]>
FSaga_SC_RpcPacket::Serialize()
const
{
	return FSagaSerializer::Serializes(myProtocol, mySize, clientId, std::wstring_view{ rpcScript, msgLength }, rpcArgument);
}

uint8*
FSaga_SC_RpcPacket::Write(uint8* buffer)
const
{
	return FSagaSerializer::Serialize(FSagaSerializer::Serialize(FSagaSerializer::Serialize(Super::Write(buffer), clientId), std::wstring_view{ rpcScript, msgLength }), rpcArgument);
}

const uint8*
FSaga_SC_RpcPacket::Read(const uint8* buffer)
{
	return FSagaSerializer::Deserialize(FSagaSerializer::Deserialize(FSagaSerializer::Deserialize(Super::Read(buffer), clientId), msgLength, rpcScript), rpcArgument);
}

TUniquePtr<uint8[]>
FSaga_SC_RespondVersionPacket::Serialize()
const
{
	return FSagaSerializer::Serializes(myProtocol, mySize, std::wstring_view{ gameVersion, versionLength });
}

uint8*
FSaga_SC_RespondVersionPacket::Write(uint8* buffer)
const
{
	return FSagaSerializer::Serialize(Super::Write(buffer), std::wstring_view{ gameVersion, versionLength });
}

const uint8*
FSaga_SC_RespondVersionPacket::Read(const uint8* buffer)
{
	return FSagaSerializer::Deserialize(Super::Read(buffer), versionLength, gameVersion);
}

TUniquePtr<uint8[]>
FSaga_SC_RespondRoomsPacket::Serialize()
const
{
	TUniquePtr<uint8[]> buffer = MakeUnique<uint8[]>(WannabeSize());

	Write(buffer.Get());

	return std::move(buffer);
}

uint8*
FSaga_SC_RespondRoomsPacket::Write(uint8* buffer)
const
{
	auto seek = FSagaSerializer::Serialize(FSagaSerializer::Serialize(buffer, myProtocol), static_cast<int16>(WannabeSize()));

	seek = FSagaSerializer::Serialize(seek, serializedRooms.size());

	for (auto& room : serializedRooms)
	{
		seek = FSagaSerializer::Serialize(seek, room.id);
		seek = FSagaSerializer::Serialize(seek, std::wstring_view{ room.title, room.nameLength });
		seek = FSagaSerializer::Serialize(seek, room.members);
	}

	return seek;
}

const uint8*
FSaga_SC_RespondRoomsPacket::Read(const uint8* buffer)
{
	auto seek = Super::Read(buffer);

	size_t size{};
	seek = FSagaSerializer::Deserialize(seek, size);

	if (0 < size)
	{
		serializedRooms.clear();
		serializedRooms.resize(size);

		for (auto& room : serializedRooms)
		{
			seek = FSagaSerializer::Deserialize(seek, room.id);
			seek = FSagaSerializer::Deserialize(seek, room.nameLength, room.title);
			seek = FSagaSerializer::Deserialize(seek, room.members);
		}
	}

	return seek;
}

TUniquePtr<uint8[]>
FSaga_SC_RespondMembersPacket::Serialize()
const
{
	TUniquePtr<uint8[]> buffer = MakeUnique<uint8[]>(WannabeSize());

	Write(buffer.Get());

	return std::move(buffer);
}

uint8*
FSaga_SC_RespondMembersPacket::Write(uint8* buffer) const
{
	auto seek = FSagaSerializer::Serialize(FSagaSerializer::Serialize(buffer, myProtocol), static_cast<int16>(WannabeSize()));

	seek = FSagaSerializer::Serialize(seek, serializedMembers.size());

	for (auto& member : serializedMembers)
	{
		seek = FSagaSerializer::Serialize(seek, member.id);
		seek = FSagaSerializer::Serialize(seek, std::wstring_view{ member.nickname, member.nameLength });
	}

	return seek;
}

const uint8*
FSaga_SC_RespondMembersPacket::Read(const uint8* buffer)
{
	auto seek = Super::Read(buffer);

	size_t size{};
	seek = FSagaSerializer::Deserialize(seek, size);

	if (0 < size)
	{
		serializedMembers.clear();
		serializedMembers.resize(size);

		for (auto& member : serializedMembers)
		{
			seek = FSagaSerializer::Deserialize(seek, member.id);
			seek = FSagaSerializer::Deserialize(seek, member.nameLength, member.nickname);
		}
	}

	return seek;
}

TUniquePtr<uint8[]>
FSaga_SC_CreatePlayerPacket::Serialize()
const
{
	return FSagaSerializer::Serializes(myProtocol, mySize, clientId, std::wstring_view{ userName, nickNameLength });
}

uint8*
FSaga_SC_CreatePlayerPacket::Write(uint8* buffer)
const
{
	return FSagaSerializer::Serializes(Super::Write(buffer), clientId, std::wstring_view{ userName, nickNameLength });
}

const uint8*
FSaga_SC_CreatePlayerPacket::Read(const uint8* buffer)
{
	return FSagaSerializer::Deserialize(FSagaSerializer::Deserialize(Super::Read(buffer), clientId), nickNameLength, userName);
}

TUniquePtr<uint8[]>
FSaga_SC_UpdatePositionPacket::Serialize()
const
{
	return FSagaSerializer::Serializes(myProtocol, mySize, clientId, x, y, z);
}

uint8*
FSaga_SC_UpdatePositionPacket::Write(uint8* buffer)
const
{
	return FSagaSerializer::Serializes(Super::Write(buffer), clientId, x, y, z);
}

const uint8*
FSaga_SC_UpdatePositionPacket::Read(const uint8* buffer)
{
	return FSagaSerializer::Deserialize(FSagaSerializer::Deserialize(FSagaSerializer::Deserialize(FSagaSerializer::Deserialize(Super::Read(buffer), clientId), x), y), z);
}

IMPL_SERIALIZE_METHOD(FSaga_SC_FailedGameStartingPacket, errCause);
IMPL_READ_METHODS(FSaga_SC_FailedGameStartingPacket, errCause);
IMPL_WRITE_METHODS_V1(FSaga_SC_FailedGameStartingPacket, errCause);

IMPL_SERIALIZE_METHOD(FSaga_SC_RoomCreatedPacket, roomId);
IMPL_READ_METHODS(FSaga_SC_RoomCreatedPacket, roomId);
IMPL_WRITE_METHODS_V1(FSaga_SC_RoomCreatedPacket, roomId);

IMPL_SERIALIZE_METHOD(FSaga_SC_RoomCreationFailedPacket, errCause);
IMPL_READ_METHODS(FSaga_SC_RoomCreationFailedPacket, errCause);
IMPL_WRITE_METHODS_V1(FSaga_SC_RoomCreationFailedPacket, errCause);

IMPL_SERIALIZE_METHOD(FSaga_SC_RoomJoinedPacket, clientId, roomId);
IMPL_READ_METHODS(FSaga_SC_RoomJoinedPacket, clientId, roomId);
IMPL_WRITE_METHODS_V2(FSaga_SC_RoomJoinedPacket, clientId, roomId);

IMPL_SERIALIZE_METHOD(FSaga_SC_RoomJoinFailedPacket, errCause);
IMPL_READ_METHODS(FSaga_SC_RoomJoinFailedPacket, errCause);
IMPL_WRITE_METHODS_V1(FSaga_SC_RoomJoinFailedPacket, errCause);

IMPL_SERIALIZE_METHOD(FSaga_SC_RoomLeftPacket, clientId);
IMPL_READ_METHODS(FSaga_SC_RoomLeftPacket, clientId);
IMPL_WRITE_METHODS_V1(FSaga_SC_RoomLeftPacket, clientId);

IMPL_SERIALIZE_METHOD(FSaga_SC_DestroyPlayerPacket, clientId);
IMPL_READ_METHODS(FSaga_SC_DestroyPlayerPacket, clientId);
IMPL_WRITE_METHODS_V1(FSaga_SC_DestroyPlayerPacket, clientId);

IMPL_SERIALIZE_METHOD(FSaga_SC_SucceedSignInPacket, clientId);
IMPL_READ_METHODS(FSaga_SC_SucceedSignInPacket, clientId);
IMPL_WRITE_METHODS_V1(FSaga_SC_SucceedSignInPacket, clientId);

IMPL_SERIALIZE_METHOD(FSaga_SC_FailedSignInPacket, errCause);
IMPL_READ_METHODS(FSaga_SC_FailedSignInPacket, errCause);
IMPL_WRITE_METHODS_V1(FSaga_SC_FailedSignInPacket, errCause);
