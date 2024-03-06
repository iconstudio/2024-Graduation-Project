#pragma once
#include "CoreMinimal.h"
#include "../SagaNetworkConnectionCategory.h"

namespace saga
{
	inline constexpr ESagaNetworkConnectionCategory ConnectionCategory = ESagaNetworkConnectionCategory::Host;
	inline const FString RemoteAddress                                 = TEXT("127.0.0.1");
	inline constexpr int32 RemotePort                                  = 40000U;
	inline constexpr int32 LocalPort                                   = 40001U;

	/* Utilities */

	[[nodiscard]]
	static TSharedRef<FInternetAddr> CreateRemoteEndPoint();

	/* Property Getters */

	[[nodiscard]]
	static consteval ESagaNetworkConnectionCategory GetConnectionCategory() noexcept
	{
		return ConnectionCategory;
	}

	[[nodiscard]]
	static consteval const FString& GetRemoteAddress() noexcept
	{
		return RemoteAddress;
	}

	[[nodiscard]]
	static consteval int32 GetRemotePort() noexcept
	{
		return RemotePort;
	}

	[[nodiscard]]
	static consteval int32 GetLocalPort() noexcept
	{
		return LocalPort;
	}
};
