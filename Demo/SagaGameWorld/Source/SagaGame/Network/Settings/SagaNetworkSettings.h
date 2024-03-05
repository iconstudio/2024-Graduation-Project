#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Network/SagaNetworkConnectionCategory.h"
#include "SagaNetworkSettings.generated.h"

UCLASS(Category = "CandyLandSaga/Network")
class SAGAGAME_API USagaNetworkSettings : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static inline constexpr ESagaNetworkConnectionCategory ConnectionCategory = ESagaNetworkConnectionCategory::Host;
	static inline const FString RemoteAddress                                 = TEXT("127.0.0.1");
	static inline constexpr int32 RemotePort                                  = 40000U;
	static inline constexpr int32 LocalPort                                   = 40001U;

	/* Utilities */

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static TSharedRef<FInternetAddr> CreateRemoteEndPoint();

	/* Property Getters */

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static consteval ESagaNetworkConnectionCategory GetConnectionCategory() noexcept
	{
		return ConnectionCategory;
	}

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static consteval const FString& GetRemoteAddress() noexcept
	{
		return RemoteAddress;
	}

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static consteval int32 GetRemotePort() noexcept
	{
		return RemotePort;
	}

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static consteval int32 GetLocalPort() noexcept
	{
		return LocalPort;
	}
};
