#pragma once
#include "CoreTypes.h"

#include <optional>
#include "SagaRoomContract.h"

namespace saga
{
	std::optional<int32> SendSignInPacket();
	std::optional<int32> SendCreateRoomPacket(std::wstring_view title);
	std::optional<int32> SendJoinRoomPacket(int32 room_id);
	std::optional<int32> SendLeaveRoomPacket();
	std::optional<int32> SendRequestVersionPacket();
	std::optional<int32> SendRequestRoomsPacket();
	std::optional<int32> SendRequestMembersPacket();
	std::optional<int32> SendGameStartPacket();
	std::optional<int32> SendGameIsLoadedPacket();
	std::optional<int32> SendPositionPacket();

	const std::byte* ReceiveSignInSucceedPacket(const std::byte* buffer, int32& my_id);
	const std::byte* ReceiveSignInFailurePacket(const std::byte* buffer, int32& error);
	const std::byte* ReceiveRoomCreatedPacket(const std::byte* buffer, int32& room_id);
	const std::byte* ReceiveRoomCreationFailedPacket(const std::byte* buffer, RoomContract& error);
	const std::byte* ReceiveRoomJoinedPacket(const std::byte* buffer, int32& client_id, int32& room_id);
	const std::byte* ReceiveRoomJoinFailedPacket(const std::byte* buffer, RoomContract& error);
	const std::byte* ReceiveRoomLeftPacket(const std::byte* buffer, int32& client_id);

}
