#pragma once
#include "CoreMinimal.h"
#include <cstddef>
#include <cstdint>
#include "SagaPacketProtocol.h"

namespace saga
{
	class USagaNetwork;

	void EventRouter(USagaNetwork& system, std::byte* packet_buffer, EPacketProtocol protocol, std::int16_t packet_size);
}
