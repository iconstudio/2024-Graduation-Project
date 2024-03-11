#pragma once
#include "CoreTypes.h"
#include "Containers/UnrealString.h"

#include "SagaRoomContract.h"

namespace saga
{
	const std::byte* ReceiveSignInSucceedPacket(const std::byte* buffer, int32& my_id);
	const std::byte* ReceiveSignInFailurePacket(const std::byte* buffer, int32& error);
	const std::byte* ReceiveRoomCreatedPacket(const std::byte* buffer, int32& room_id);
	const std::byte* ReceiveRoomCreationFailedPacket(const std::byte* buffer, RoomContract& error);
	const std::byte* ReceiveRoomJoinedPacket(const std::byte* buffer, int32& client_id, int32& room_id);
	const std::byte* ReceiveRoomJoinFailedPacket(const std::byte* buffer, RoomContract& error);
	const std::byte* ReceiveRoomLeftPacket(const std::byte* buffer, int32& client_id);

}
