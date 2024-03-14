#include "SagaPacketSenders.h"
#include "CoreMinimal.h"
#include <algorithm>

#include "SagaClientPacketPrefabs.h"
#include "SagaNetwork.h"

std::optional<int32>
saga::SendSignInPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendCreateRoomPacket(FString title)
{
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendJoinRoomPacket(int32 room_id)
{
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendLeaveRoomPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendRequestVersionPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendRequestRoomsPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendRequestMembersPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendGameStartPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendGameIsLoadedPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}

std::optional<int32>
saga::SendPositionPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();

	return std::nullopt;
}
