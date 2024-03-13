#pragma once
#include "CoreMinimal.h"

#include "SagaVirtualSession.h"
#include "../Utility/MacroHelper.inl"
#include "SagaVirtualRoom.generated.h"

UCLASS(BlueprintType, Blueprintable, Category = "CandyLandSaga|Network|Session")
class SAGAGAME_API USagaVirtualRoom : public USagaVirtualSession
{
	GENERATED_BODY()

public:
	USagaVirtualRoom()
		: USagaVirtualSession()
		, MembersCount(0)
	{}

	USagaVirtualRoom(int32 id, FStringView title)
		: USagaVirtualSession(id, title)
		, MembersCount(0)
	{}

	USagaVirtualRoom(int32 id, FStringView title, int32 members_count)
		: USagaVirtualSession(id, title)
		, MembersCount(members_count)
	{}

	[[nodiscard]]
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network|Session")
	constexpr int32 GetNumberOfMember() const noexcept
	{
		return MembersCount;
	}

	UPROPERTY(VisibleAnywhere, meta = (NoResetToDefault, NoSpinbox = true, ClampMin = 0, UIMin = 0, ClampMax = 4, UIMax = 4))
	int32 MembersCount;
};
