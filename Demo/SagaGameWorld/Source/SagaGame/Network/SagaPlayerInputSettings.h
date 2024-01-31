#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SagaPlayerInputSettings.generated.h"

UCLASS(Category = "CandyLandSaga/Network")
class SAGAGAME_API USagaPlayerInputSettings : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static FKey GetMoveForwardKey() noexcept
	{
		return "W";
	}

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static FKey GetMoveBackwardKey() noexcept
	{
		return "S";
	}

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static FKey GetMoveLeftKey() noexcept
	{
		return "A";
	}

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static FKey GetMoveRightKey() noexcept
	{
		return "D";
	}

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static FKey GetJumpKey() noexcept
	{
		return "SpaceBar";
	}
};
