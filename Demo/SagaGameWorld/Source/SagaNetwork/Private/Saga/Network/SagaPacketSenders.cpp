#include "Saga/Network/SagaPacketSenders.h"

#include "Saga/Network/SagaNetworkUtility.h"
#include "Saga/Network/SagaClientPacketPrefabs.h"

std::optional<int32>
saga::SendSignInPacket(FSocket* socket, FStringView nickname)
{
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
saga::SendCreateRoomPacket(FSocket* socket, FStringView title)
{
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
saga::SendJoinRoomPacket(FSocket* socket, int32 room_id)
{
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
saga::SendLeaveRoomPacket(FSocket* socket)
{
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
saga::SendRequestVersionPacket(FSocket* socket)
{
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
saga::SendRequestRoomsPacket(FSocket* socket)
{
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
saga::SendRequestMembersPacket(FSocket* socket)
{
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
saga::SendGameStartPacket(FSocket* socket)
{
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
saga::SendGameIsLoadedPacket(FSocket* socket)
{
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
saga::SendPositionPacket(FSocket* socket, float x, float y, float z)
{
	saga::CS_UpdatePositionPacket pk{ x, y, z };
	auto ptr = pk.Serialize();

	const int32 sent_bytes = saga::RawSend(socket, ptr.get(), pk.WannabeSize());
	if (sent_bytes <= 0)
	{
		return std::nullopt;
	}

	return sent_bytes;
}
