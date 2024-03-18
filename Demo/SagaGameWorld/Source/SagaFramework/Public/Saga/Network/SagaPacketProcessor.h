#pragma once
#ifndef SAGAFRAMEWORK_NET_PACKET_PROCESSOR_H
#define SAGAFRAMEWORK_NET_PACKET_PROCESSOR_H

#include "SagaFramework.h"
#include <cstddef>

#include "Saga/Network/SagaRoomContract.h"
#include "Saga/Network/SagaServerPacketPrefabs.h"

const uint8* ReceiveSignInSucceedPacket(const uint8* buffer, int32& my_id);
const uint8* ReceiveSignInFailurePacket(const uint8* buffer, int32& error);

const uint8* ReceiveRoomCreatedPacket(const uint8* buffer, int32& room_id);
const uint8* ReceiveRoomCreationFailedPacket(const uint8* buffer, ERoomContract& error);
const uint8* ReceiveRoomJoinedPacket(const uint8* buffer, int32& client_id, int32& room_id);
const uint8* ReceiveRoomJoinFailedPacket(const uint8* buffer, ERoomContract& error);
const uint8* ReceiveRoomLeftPacket(const uint8* buffer, int32& client_id);

const uint8* ReceiveRespondVersionPacket(const uint8* buffer, wchar_t* version_str_buffer, const size_t& str_length);
const uint8* ReceiveRespondRoomsPacket(const uint8* buffer, std::vector<FSagaSerializedRoom>& rooms);
const uint8* ReceiveRespondUsersPacket(const uint8* buffer, std::vector<FSagaSerializedMember>& users);

const uint8* ReceivePositionPacket(const uint8* buffer, int32& client_id, float& x, float& y, float& z);

#endif // !SAGAFRAMEWORK_NET_PACKET_PROCESSOR_H
