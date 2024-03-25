#include "Saga/Network/SagaPacketProcessor.h"

#include "Saga/Network/SagaServerPacketPrefabs.h"

const std::byte*
saga::ReceiveSignInSucceedPacket(const std::byte* buffer, int32& my_id)
{
	auto seek = buffer;

	SC_SucceedSignInPacket pk{};
	seek = pk.Read(buffer);

	my_id = pk.clientId;

	return seek;
}

const std::byte*
saga::ReceiveSignInFailurePacket(const std::byte* buffer
	, int32& error)
{
	auto seek = buffer;

	SC_FailedSignInPacket pk{};
	seek = pk.Read(buffer);

	error = pk.errCause;

	return seek;
}

const std::byte*
saga::ReceiveRoomCreatedPacket(const std::byte* buffer
	, int32& room_id)
{
	auto seek = buffer;

	SC_RoomCreatedPacket pk{};
	seek = pk.Read(buffer);

	room_id = pk.roomId;

	return seek;
}

const std::byte*
saga::ReceiveRoomCreationFailedPacket(const std::byte* buffer
	, ERoomContract& error)
{
	auto seek = buffer;

	SC_RoomCreationFailedPacket pk{};
	seek = pk.Read(buffer);

	error = pk.errCause;

	return seek;
}

const std::byte*
saga::ReceiveRoomJoinedPacket(const std::byte* buffer
	, int32& client_id
	, int32& room_id)
{
	auto seek = buffer;

	SC_RoomJoinedPacket pk{};
	seek = pk.Read(buffer);

	client_id = pk.clientId;
	room_id = pk.roomId;

	return seek;
}

const std::byte*
saga::ReceiveRoomJoinFailedPacket(const std::byte* buffer
	, ERoomContract& error)
{
	auto seek = buffer;

	SC_RoomJoinFailedPacket pk{};
	seek = pk.Read(buffer);

	error = pk.errCause;

	return seek;
}

const std::byte*
saga::ReceiveRoomLeftPacket(const std::byte* buffer
	, int32& client_id)
{
	auto seek = buffer;

	SC_RoomLeftPacket pk{};
	seek = pk.Read(buffer);

	client_id = pk.clientId;

	return seek;
}

const std::byte*
saga::ReceiveRespondVersionPacket(const std::byte* buffer
	, wchar_t* version_str_buffer, const size_t& buffer_length)
{
	auto seek = buffer;

	SC_RespondVersionPacket pk{};
	seek = pk.Read(buffer);

	std::copy(std::cbegin(pk.gameVersion), std::cend(pk.gameVersion), version_str_buffer);

	return seek;
}

const std::byte*
saga::ReceiveRespondRoomsPacket(const std::byte* buffer
	, std::vector<datagrams::SerializedRoom>& rooms)
{
	auto seek = buffer;

	SC_RespondRoomsPacket pk{};
	seek = pk.Read(buffer);

	rooms = std::move(pk.serializedRooms);

	return seek;
}

const std::byte*
saga::ReceiveRespondUsersPacket(const std::byte* buffer
	, std::vector<datagrams::SerializedMember>& users)
{
	auto seek = buffer;

	SC_RespondMembersPacket pk{};
	seek = pk.Read(buffer);

	users = std::move(pk.serializedMembers);

	return seek;
}

const std::byte*
saga::ReceivePositionPacket(const std::byte* buffer
	, int32& client_id
	, float& x, float& y, float& z)
{
	auto seek = buffer;

	SC_UpdatePositionPacket pk{};
	seek = pk.Read(buffer);

	client_id = pk.clientId;
	x = pk.x;
	y = pk.y;
	z = pk.z;

	return seek;
}

const std::byte*
saga::ReceiveRpcPacket(const std::byte* buffer
	, int32& client_id, wchar_t(&contents)[10], long long& argument)
{
	auto seek = buffer;

	SC_RpcPacket pk{};
	seek = pk.Read(buffer);

	client_id = pk.clientId;
	std::copy(std::cbegin(pk.rpcScript), std::cend(pk.rpcScript), std::begin(contents));
	argument = pk.rpcArgument;

	return seek;
}

const std::byte*
saga::ReceiveRpcPacket(const std::byte* buffer
	, int32& client_id, wchar_t(&contents)[10])
{
	auto seek = buffer;

	SC_RpcPacket pk{};
	seek = pk.Read(buffer);

	client_id = pk.clientId;
	std::copy(std::cbegin(pk.rpcScript), std::cend(pk.rpcScript), std::begin(contents));

	return seek;
}
