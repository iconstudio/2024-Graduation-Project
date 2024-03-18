#pragma once
#include "Saga/Network/SagaVirtualSession.h"
#include "SagaVirtualUser.generated.h"

USTRUCT(BlueprintType, Category = "CandyLandSaga|Network|Session")
struct SAGAFRAMEWORK_API FSagaVirtualUser : public FSagaVirtualSession
{
	GENERATED_BODY()

public:
	using FSagaVirtualSession::FSagaVirtualSession;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CandyLandSaga|Network|Session")
	AActor* ownedCharacter;
};
