#pragma once
#include "CoreMinimal.h"

#include "Saga/Network/SagaVirtualSession.h"
#include "SagaVirtualRoom.generated.h"

USTRUCT(BlueprintType, Atomic, Category = "CandyLandSaga|Level|UI|Element")
struct SAGANETWORK_API FSagaVirtualRoom : public FSagaVirtualSession
{
	GENERATED_BODY()

public:
	FSagaVirtualRoom()
		: FSagaVirtualSession()
	{
	}

	FSagaVirtualRoom(int32 id)
		: FSagaVirtualSession(id)
	{
	}

	FSagaVirtualRoom(int32 id, const FString& title)
		: FSagaVirtualSession(id, title)
		, MembersCount(0)
	{
	}

	FSagaVirtualRoom(int32 id, const FString& title, int32 member_count)
		: FSagaVirtualSession(id, title)
		, MembersCount(member_count)
	{}

	UPROPERTY(VisibleAnywhere, meta = (NoResetToDefault, NoSpinbox = true, ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 MembersCount;
};
