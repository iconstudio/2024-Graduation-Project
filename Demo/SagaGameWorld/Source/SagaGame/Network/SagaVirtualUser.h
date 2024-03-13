#pragma once
#include "CoreMinimal.h"

#include "SagaVirtualSession.h"
#include "../Character/SagaCharacterPlayer.h"
#include "../Utility/MacroHelper.inl"
#include "SagaVirtualUser.generated.h"

USTRUCT(BlueprintType, Category = "CandyLandSaga|Network|Session")
struct SAGAGAME_API FSagaVirtualUser : public FSagaVirtualSession
{
	GENERATED_BODY()

public:
	using FSagaVirtualSession::FSagaVirtualSession;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CandyLandSaga|Network|Session")
	ASagaCharacterPlayer* ownedCharacter;
};
