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

	FSagaVirtualRoom(int32 id, FStringView title, int32 member_count)
		: FSagaVirtualSession(id, title)
		, MembersCount(member_count)
	{}

	UPROPERTY(VisibleAnywhere, meta = (NoResetToDefault, NoSpinbox = true, ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 MembersCount;
};
