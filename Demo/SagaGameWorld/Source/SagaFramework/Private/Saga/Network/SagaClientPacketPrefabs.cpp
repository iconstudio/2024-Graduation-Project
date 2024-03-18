#include "Saga/Network/SagaClientPacketPrefabs.h"
#include "Saga/Serializer.h"

#include <algorithm>

TUniquePtr<uint8[]>
FSaga_CS_RpcPacket::Serialize()
const
{
	return FSagaSerializer::Serializes(myProtocol, mySize, std::wstring_view{ rpcScript, msgLength }, rpcArgument);
}

uint8*
FSaga_CS_RpcPacket::Write(uint8* buffer)
const
{
	return FSagaSerializer::Serialize(FSagaSerializer::Serialize(Super::Write(buffer), std::wstring_view{ rpcScript, msgLength }), rpcArgument);
}

const uint8*
FSaga_CS_RpcPacket::Read(const uint8* buffer)
{
	return FSagaSerializer::Deserialize(FSagaSerializer::Deserialize(Super::Read(buffer), msgLength, rpcScript), rpcArgument);
}

TUniquePtr<uint8[]>
FSaga_CS_CreateRoomPacket::Serialize()
const
{
	return FSagaSerializer::Serializes(myProtocol, mySize, std::wstring_view{ roomTitle, roomTitleLength });
}

uint8*
FSaga_CS_CreateRoomPacket::Write(uint8* buffer)
const
{
	return FSagaSerializer::Serialize(Super::Write(buffer), std::wstring_view{ roomTitle, roomTitleLength });
}

const uint8*
FSaga_CS_CreateRoomPacket::Read(const uint8* buffer)
{
	return FSagaSerializer::Deserialize(Super::Read(buffer), roomTitleLength, roomTitle);
}

TUniquePtr<uint8[]>
FSaga_CS_UpdatePositionPacket::Serialize() const
{
	return FSagaSerializer::Serializes(myProtocol, mySize, x, y, z);
}

uint8*
FSaga_CS_UpdatePositionPacket::Write(uint8* buffer) const
{
	return FSagaSerializer::Serializes(Super::Write(buffer), x, y, z);
}

const uint8*
FSaga_CS_UpdatePositionPacket::Read(const uint8* buffer)
{
	return FSagaSerializer::Deserialize(FSagaSerializer::Deserialize(FSagaSerializer::Deserialize(Super::Read(buffer), x), y), z);
}

[[nodiscard]]
TUniquePtr<uint8[]>
FSaga_CS_SignInPacket::Serialize()
const
{
	return FSagaSerializer::Serializes(myProtocol, mySize, std::wstring_view{ userName, nickNameLength });
}

uint8*
FSaga_CS_SignInPacket::Write(uint8* buffer)
const
{
	return FSagaSerializer::Serialize(Super::Write(buffer), std::wstring_view{ userName, nickNameLength });
}

const uint8*
FSaga_CS_SignInPacket::Read(const uint8* buffer)
{
	return FSagaSerializer::Deserialize(Super::Read(buffer), nickNameLength, userName);
}

IMPL_SERIALIZE_METHOD(FSaga_CS_EnterRoomPacket, roomId);
IMPL_READ_METHODS(FSaga_CS_EnterRoomPacket, roomId);
IMPL_WRITE_METHODS_V1(FSaga_CS_EnterRoomPacket, roomId);
