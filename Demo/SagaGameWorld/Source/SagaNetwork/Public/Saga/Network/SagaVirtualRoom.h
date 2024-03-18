#pragma once
#include "CoreMinimal.h"

#include "Saga/Network/SagaVirtualSession.h"
#include "SagaVirtualRoom.generated.h"

USTRUCT(BlueprintType, Atomic, Category = "CandyLandSaga|Network|Session")
struct SAGANETWORK_API FSagaVirtualRoom : public FSagaVirtualSession
{
	GENERATED_BODY()

public:
	FSagaVirtualRoom() noexcept
		: Super()
		, MembersCount(0)
	{}

	FSagaVirtualRoom(int32 id, FStringView title, int32 member_count) noexcept
		: Super(id, title)
		, MembersCount(member_count)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CandyLandSaga|Network|Session")
	int32 MembersCount;
};
