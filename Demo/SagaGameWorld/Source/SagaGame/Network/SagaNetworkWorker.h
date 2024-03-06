#pragma once
#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"

namespace saga
{
	class SAGAGAME_API FSagaNetworkWorker final : public FRunnable
	{
	public:
		FSagaNetworkWorker();
		~FSagaNetworkWorker();

		virtual bool Init() override;
		virtual uint32 Run() override;
		virtual void Exit() override;
		virtual void Stop() override;

	private:
		FRunnableThread* MyThread;
	};
}
