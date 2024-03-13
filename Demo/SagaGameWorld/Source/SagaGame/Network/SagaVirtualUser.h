#pragma once
#include "CoreMinimal.h"
#include "SagaVirtualSession.h"

#include "SagaVirtualUser.generated.h"

class ASagaCharacterPlayer;

USTRUCT(BlueprintType, Category = "CandyLandSaga|Network|Session")
struct SAGAGAME_API FSagaVirtualUser : public FSagaVirtualSession
{
	GENERATED_BODY()

public:
	using FSagaVirtualSession::FSagaVirtualSession;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CandyLandSaga|Network|Session")
	ASagaCharacterPlayer* ownedCharacter;
};
