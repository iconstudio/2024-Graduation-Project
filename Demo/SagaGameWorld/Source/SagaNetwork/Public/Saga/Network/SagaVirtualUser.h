#pragma once
#include "CoreMinimal.h"

#include "Saga/Network/SagaVirtualSession.h"
#include "SagaVirtualUser.generated.h"

class ASagaCharacterPlayer;

USTRUCT(BlueprintType, Atomic, Category = "CandyLandSaga|Network|Session")
struct SAGANETWORK_API FSagaVirtualUser : public FSagaVirtualSession
{
	GENERATED_BODY()

public:
	using FSagaVirtualSession::FSagaVirtualSession;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CandyLandSaga|Network|Session")
	ASagaCharacterPlayer* ownedCharacter;
};
