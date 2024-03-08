#pragma once
#include <cstddef>
#include <cstdint>
#include "SagaPacketProtocol.h"

namespace saga
{
	void EventRouter(const std::byte* packet_buffer, EPacketProtocol protocol, std::int16_t packet_size);
}
