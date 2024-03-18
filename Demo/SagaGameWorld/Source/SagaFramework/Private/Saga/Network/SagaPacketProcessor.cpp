#include "Saga/Network/SagaPacketProcessor.h"

#include "Saga/Network/SagaNetworkUtility.h"
#include "Saga/Network/SagaServerPacketPrefabs.h"

const uint8*
ReceiveSignInSucceedPacket(const uint8* buffer, int32& my_id)
{
	auto seek = buffer;

	FSaga_SC_SucceedSignInPacket pk{};
	pk.Read(buffer);

	my_id = pk.clientId;

	return seek;
}

const uint8*
ReceiveSignInFailurePacket(const uint8* buffer
	, int32& error)
{
	auto seek = buffer;

	FSaga_SC_FailedSignInPacket pk{};
	pk.Read(buffer);

	error = pk.errCause;

	return seek;
}

const uint8*
ReceiveRoomCreatedPacket(const uint8* buffer
	, int32& room_id)
{
	auto seek = buffer;

	FSaga_SC_RoomCreatedPacket pk{};
	pk.Read(buffer);

	room_id = pk.roomId;

	return seek;
}

const uint8*
ReceiveRoomCreationFailedPacket(const uint8* buffer
	, 
	ERoomContract& error)
{
	auto seek = buffer;

	FSaga_SC_RoomCreationFailedPacket pk{};
	pk.Read(buffer);

	error = pk.errCause;

	return seek;
}

const uint8*
ReceiveRoomJoinedPacket(const uint8* buffer
	, int32& client_id
	, int32& room_id)
{
	auto seek = buffer;

	FSaga_SC_RoomJoinedPacket pk{};
	pk.Read(buffer);

	client_id = pk.clientId;
	room_id = pk.roomId;

	return seek;
}

const uint8*
ReceiveRoomJoinFailedPacket(const uint8* buffer
	, ERoomContract& error)
{
	auto seek = buffer;

	FSaga_SC_RoomJoinFailedPacket pk{};
	pk.Read(buffer);

	error = pk.errCause;

	return seek;
}

const uint8*
ReceiveRoomLeftPacket(const uint8* buffer
	, int32& client_id)
{
	auto seek = buffer;

	FSaga_SC_RoomLeftPacket pk{};
	pk.Read(buffer);

	client_id = pk.clientId;

	return seek;
}

const uint8*
ReceiveRespondVersionPacket(const uint8* buffer
	, wchar_t* version_str_buffer, const size_t& buffer_length)
{
	auto seek = buffer;

	FSaga_SC_RespondVersionPacket pk{};
	pk.Read(buffer);

	std::copy(std::cbegin(pk.gameVersion), std::cend(pk.gameVersion), version_str_buffer);

	return seek;
}

const uint8*
ReceiveRespondRoomsPacket(const uint8* buffer
	, std::vector<FSagaSerializedRoom>& rooms)
{
	auto seek = buffer;

	FSaga_SC_RespondRoomsPacket pk{};
	pk.Read(buffer);

	rooms = std::move(pk.serializedRooms);

	return seek;
}

const uint8*
ReceiveRespondUsersPacket(const uint8* buffer
	, std::vector<FSagaSerializedMember>& users)
{
	auto seek = buffer;

	FSaga_SC_RespondMembersPacket pk{};
	pk.Read(buffer);

	users = std::move(pk.serializedMembers);

	return seek;
}

const uint8*
ReceivePositionPacket(const uint8* buffer
	, int32& client_id
	, float& x, float& y, float& z)
{
	auto seek = buffer;

	FSaga_SC_UpdatePositionPacket pk{};
	pk.Read(buffer);

	client_id = pk.clientId;
	x = pk.x;
	y = pk.y;
	z = pk.z;

	return seek;
}
