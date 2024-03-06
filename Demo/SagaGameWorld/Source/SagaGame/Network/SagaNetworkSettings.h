#pragma once
#include "CoreMinimal.h"
#include "SagaNetworkConnectionCategory.h"

namespace saga
{
	inline constexpr ESagaNetworkConnectionCategory ConnectionCategory = ESagaNetworkConnectionCategory::Host;
	inline const FString RemoteAddress = TEXT("127.0.0.1");
	inline constexpr int RemotePort = 40000U;
	inline constexpr int LocalPort = 40001U;
	inline constexpr bool IsOfflineMode = false;
};
