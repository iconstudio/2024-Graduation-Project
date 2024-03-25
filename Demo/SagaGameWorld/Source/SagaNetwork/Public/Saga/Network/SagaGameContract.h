#pragma once
#include "CoreMinimal.h"

#include "SagaGameContract.generated.h"

UENUM(BlueprintType)
enum class [[nodiscard]] ESagaGameContract : uint8
{
	Success = 0
	, NotInRoom
	, ClientIsBusy // The client's state is unmatched
	, LackOfMember
	, InvalidRoom
	, InvalidOperation // Room task is invalid
	, UnstableRoom // Room's state is changed at time
	, ServerError // Unknown internal error
};
