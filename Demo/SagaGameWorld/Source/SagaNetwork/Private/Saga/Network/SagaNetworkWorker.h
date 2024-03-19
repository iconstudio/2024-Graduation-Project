#pragma once
#ifndef SAGAFRAMEWORK_NET_WORKER_H
#define SAGAFRAMEWORK_NET_WORKER_H

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"

class USagaNetworkSubSystem;

class SAGANETWORK_API FSagaNetworkWorker final : public FRunnable
{
public:
	FSagaNetworkWorker(USagaNetworkSubSystem* instance);
	~FSagaNetworkWorker();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
	virtual void Stop() override;

private:
	void RouteEvents(const std::byte* packet_buffer, EPacketProtocol protocol, int16 packet_size);

	FRunnableThread* MyThread;
	USagaNetworkSubSystem* SubSystemInstance;
};

#endif // !SAGAFRAMEWORK_NET_WORKER_H
