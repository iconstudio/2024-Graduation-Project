#pragma once
#include "CoreMinimal.h"

#include "SagaVirtualSession.h"
#include "../Utility/MacroHelper.inl"
#include "SagaVirtualRoom.generated.h"

USTRUCT(BlueprintType, Category = "CandyLandSaga|Network|Session")
struct SAGAGAME_API FSagaVirtualRoom : public FSagaVirtualSession
{
	GENERATED_BODY()

public:
	using FSagaVirtualSession::FSagaVirtualSession;
};
