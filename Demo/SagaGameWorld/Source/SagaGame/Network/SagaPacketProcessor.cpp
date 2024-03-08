#include "SagaPacketProcessor.h"
#include "SagaNetwork.h"
#include "SagaNetworkUtility.h"
#include "SagaServerPacketPrefabs.h"

std::optional<int32>
saga::SendSignInPacket()
{
	auto instance = USagaNetwork::Instance();
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendCreateRoomPacket(std::wstring_view title)
{
	auto instance = USagaNetwork::Instance();
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendJoinRoomPacket(int32 room_id)
{
	auto instance = USagaNetwork::Instance();
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendLeaveRoomPacket()
{
	auto instance = USagaNetwork::Instance();
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendRequestVersionPacket()
{
	auto instance = USagaNetwork::Instance();
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendRequestRoomsPacket()
{
	auto instance = USagaNetwork::Instance();
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendRequestMembersPacket()
{
	auto instance = USagaNetwork::Instance();
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendGameStartPacket()
{
	auto instance = USagaNetwork::Instance();
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendGameIsLoadedPacket()
{
	auto instance = USagaNetwork::Instance();
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendPositionPacket()
{
	auto instance = USagaNetwork::Instance();
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

const std::byte*
saga::ReceiveSignInSucceedPacket(const std::byte* buffer, int32& my_id)
{
	auto seek = buffer;

	SC_SucceedSignInPacket pk{};
	pk.Read(buffer);

	my_id = pk.clientId;

	return seek;
}

const std::byte*
saga::ReceiveSignInFailurePacket(const std::byte* buffer, int32& error)
{
	auto seek = buffer;

	SC_FailedSignInPacket pk{};
	pk.Read(buffer);

	error = pk.errCause;

	return seek;
}

const std::byte*
saga::ReceiveRoomCreatedPacket(const std::byte* buffer, int32& c)
{
	auto seek = buffer;

	SC_RoomCreatedPacket pk{};
	pk.Read(buffer);

	room_id = pk.roomId;

	return seek;
}

const std::byte*
saga::ReceiveRoomCreationFailedPacket(const std::byte* buffer, saga::
RoomContract& error)
{
	auto seek = buffer;

	SC_RoomCreationFailedPacket pk{};
	pk.Read(buffer);

	error = pk.errCause;

	return seek;
}

const std::byte*
saga::ReceiveRoomJoinedPacket(const std::byte* buffer, int32& client_id, int32& room_id)
{
	auto seek = buffer;

	SC_RoomJoinedPacket pk{};
	pk.Read(buffer);

	client_id = pk.clientId;
	room_id = pk.roomId;

	return seek;
}

const std::byte*
saga::ReceiveRoomJoinFailedPacket(const std::byte* buffer, saga::RoomContract& error)
{
	auto seek = buffer;

	SC_RoomJoinFailedPacket pk{};
	pk.Read(buffer);

	error = pk.errCause;

	return seek;
}

const std::byte*
saga::ReceiveRoomLeftPacket(const std::byte* buffer, int32& client_id)
{
	auto seek = buffer;

	SC_RoomLeftPacket pk{};
	pk.Read(buffer);

	client_id = pk.clientId;

	return seek;
}