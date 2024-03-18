#pragma once
#include "CoreMinimal.h"
#include <optional>

#include "Saga/Network/SagaNetworkSubSystem.h"
#include "Saga/Network/SagaConnectionContract.h"

namespace saga
{
	class SAGANETWORK_API USagaNetwork final
		: public TSharedFromThis<USagaNetwork>
	{
	public:
		using Super = TSharedFromThis<USagaNetwork>;

	};
}
