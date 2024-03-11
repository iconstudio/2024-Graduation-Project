#pragma once
#include "CoreTypes.h"
#include "Containers/UnrealString.h"
#include <optional>

namespace saga
{
	std::optional<int32> SendSignInPacket(FStringView nickname);
	std::optional<int32> SendCreateRoomPacket(FStringView title);
	std::optional<int32> SendJoinRoomPacket(int32 room_id);
	std::optional<int32> SendLeaveRoomPacket();
	std::optional<int32> SendRequestVersionPacket();
	std::optional<int32> SendRequestRoomsPacket();
	std::optional<int32> SendRequestMembersPacket();
	std::optional<int32> SendGameStartPacket();
	std::optional<int32> SendGameIsLoadedPacket();
	std::optional<int32> SendPositionPacket();
}
