#pragma once
#include "SagaFramework.h"

#include "SagaConnectionContract.generated.h"

UENUM(BlueprintType)
enum class [[nodiscard]] ESagaConnectionContract : uint8
{
	Success = 0
	, Error
};

namespace saga
{
	using ConnectionContract = ::ESagaConnectionContract;
}