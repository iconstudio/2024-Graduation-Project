#include "SagaPacketSenders.h"

#include "SagaNetworkUtility.h"
#include "SagaClientPacketPrefabs.h"
#include "SagaNetwork.h"

std::optional<int32>
saga::SendSignInPacket(FStringView nickname)
{
	auto& socket = USagaNetwork::GetLocalSocket();

	const saga::CS_SignInPacket pk{ nickname.GetData(), static_cast<size_t>(nickname.Len()) };
	auto ptr = pk.Serialize();

	const int32 sent_bytes = saga::RawSend(socket, ptr.get(), pk.WannabeSize());
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

	const saga::CS_CreateRoomPacket pk{ title.GetData(), static_cast<size_t>(title.Len()) };
	auto ptr = pk.Serialize();

	const int32 sent_bytes = saga::RawSend(socket, ptr.get(), pk.WannabeSize());
	if (sent_bytes <= 0)
	{
		return std::nullopt;
	}

	return sent_bytes;
}

std::optional<int32>
saga::SendJoinRoomPacket(int32 room_id)
{
	auto& socket = USagaNetwork::GetLocalSocket();
	const saga::CS_EnterRoomPacket pk{ room_id };
	auto ptr = pk.Serialize();

	const int32 sent_bytes = saga::RawSend(socket, ptr.get(), pk.WannabeSize());
	if (sent_bytes <= 0)
	{
		return std::nullopt;
	}

	return sent_bytes;
}

std::optional<int32>
saga::SendLeaveRoomPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();
	static constexpr saga::CS_LeaveRoomPacket pk{};
	static auto ptr = pk.Serialize();

	const int32 sent_bytes = saga::RawSend(socket, ptr.get(), pk.WannabeSize());
	if (sent_bytes <= 0)
	{
		return std::nullopt;
	}

	return sent_bytes;
}

std::optional<int32>
saga::SendRequestVersionPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();
	static constexpr saga::CS_RequestVersionPacket pk{};
	static auto ptr = pk.Serialize();

	const int32 sent_bytes = saga::RawSend(socket, ptr.get(), pk.WannabeSize());
	if (sent_bytes <= 0)
	{
		return std::nullopt;
	}

	return sent_bytes;
}

std::optional<int32>
saga::SendRequestRoomsPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();
	static constexpr saga::CS_RequestRoomsPacket pk{};
	static auto ptr = pk.Serialize();

	const int32 sent_bytes = saga::RawSend(socket, ptr.get(), pk.WannabeSize());
	if (sent_bytes <= 0)
	{
		return std::nullopt;
	}

	return sent_bytes;
}

std::optional<int32>
saga::SendRequestMembersPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();
	static constexpr saga::CS_RequestMembersPacket pk{};
	static auto ptr = pk.Serialize();

	const int32 sent_bytes = saga::RawSend(socket, ptr.get(), pk.WannabeSize());
	if (sent_bytes <= 0)
	{
		return std::nullopt;
	}

	return sent_bytes;
}

std::optional<int32>
saga::SendGameStartPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();
	static constexpr saga::CS_GameStartPacket pk{};
	static auto ptr = pk.Serialize();

	const int32 sent_bytes = saga::RawSend(socket, ptr.get(), pk.WannabeSize());
	if (sent_bytes <= 0)
	{
		return std::nullopt;
	}

	return std::nullopt;
}

std::optional<int32>
saga::SendGameIsLoadedPacket()
{
	auto& socket = USagaNetwork::GetLocalSocket();

	static constexpr saga::CS_GameLoadedPacket pk{};
	static auto ptr = pk.Serialize();

	const int32 sent_bytes = saga::RawSend(socket, ptr.get(), pk.WannabeSize());
	if (sent_bytes <= 0)
	{
		return std::nullopt;
	}

	return sent_bytes;
}

std::optional<int32>
saga::SendPositionPacket(float x, float y, float z)
{
	auto& socket = USagaNetwork::GetLocalSocket();

	saga::CS_UpdatePositionPacket pk{ x, y, z };
	auto ptr = pk.Serialize();

	const int32 sent_bytes = saga::RawSend(socket, ptr.get(), pk.WannabeSize());
	if (sent_bytes <= 0)
	{
		return std::nullopt;
	}

	return sent_bytes;
}
