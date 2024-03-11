#include "SagaPacketSenders.h"

#include "SagaNetworkUtility.h"
#include "SagaClientPacketPrefabs.h"
#include "SagaNetwork.h"

std::optional<int32>
saga::SendSignInPacket(FStringView nickname)
{
	auto& socket = USagaNetwork::GetLocalSocket();

	const saga::CS_SignInPacket packet{ nickname.GetData(), static_cast<size_t>(nickname.Len()) };
	auto ptr = packet.Serialize();
	const int32 sent_bytes = saga::RawSend(socket, ptr.get(), packet.WannabeSize());
	if (sent_bytes <= 0)
	{
		return std::nullopt;
	}

	return sent_bytes;
}

std::optional<int32>
saga::SendCreateRoomPacket(FStringView title)
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
