#pragma once
#ifndef SAGAFRAMEWORK_NET_ROUTER_H
#define SAGAFRAMEWORK_NET_ROUTER_H

#include <cstddef>
#include <cstdint>

#include "Saga/Network/SagaPacketProtocol.h"

namespace saga
{
	void EventRouter(const std::byte* packet_buffer, EPacketProtocol protocol, std::int16_t packet_size);
}

#endif // !SAGAFRAMEWORK_NET_ROUTER_H
