#include "Saga/Network/SagaBasicPacket.h"
#include "Saga/Serializer.h"

TUniquePtr<uint8[]>
FSagaBasicPacket::Serialize()
const
{
	return FSagaSerializer::Serializes(static_cast<uint8>(myProtocol), mySize);
}

uint8*
FSagaBasicPacket::Write(uint8* buffer)
const
{
	return FSagaSerializer::Serialize(FSagaSerializer::Serialize(buffer, static_cast<uint8>(myProtocol)), mySize);
}

const uint8*
FSagaBasicPacket::Read(const uint8* buffer)
{
	return FSagaSerializer::Deserialize(FSagaSerializer::Deserialize(buffer, myProtocol), mySize);
}
