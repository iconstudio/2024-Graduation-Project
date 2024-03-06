#pragma once
#include "CoreMinimal.h"
#include "SagaNetworkConnectionCategory.h"

namespace saga
{
	inline constexpr ESagaNetworkConnectionCategory ConnectionCategory = ESagaNetworkConnectionCategory::Host;
	inline const FString RemoteAddress                               = TEXT("127.0.0.1");
	inline constexpr int RemotePort                                  = 40000U;
	inline constexpr int LocalPort                                   = 40001U;

	/* Utilities */

	[[nodiscard]]
	TSharedRef<FInternetAddr> CreateRemoteEndPoint();

	/* Property Getters */

	[[nodiscard]]
	consteval ESagaNetworkConnectionCategory GetConnectionCategory() noexcept
	{
		return ConnectionCategory;
	}

	[[nodiscard]]
	consteval const FString& GetRemoteAddress() noexcept
	{
		return RemoteAddress;
	}

	[[nodiscard]]
	consteval int GetRemotePort() noexcept
	{
		return RemotePort;
	}

	[[nodiscard]]
	consteval int GetLocalPort() noexcept
	{
		return LocalPort;
	}
};
