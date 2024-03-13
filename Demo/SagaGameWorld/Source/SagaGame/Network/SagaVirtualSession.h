#pragma once
#include "CoreMinimal.h"
#include "Containers/UnrealString.h"
#include "Templates/UnrealTemplate.h"

#include "../Utility/MacroHelper.inl"
#include "SagaVirtualSession.generated.h"

UCLASS(BlueprintType, Blueprintable, Abstract, NotPlaceable, Category = "CandyLandSaga|Network|Session")
class SAGAGAME_API USagaVirtualSession : public UObject
{
	GENERATED_BODY()

public:
	USagaVirtualSession()
		: UObject()
		, MyID(-1), MyName(TEXT("Empty Client"))
	{}

	USagaVirtualSession(int32 id)
		: UObject()
		, MyID(id), MyName(TEXT("Empty Client"))
	{}

	USagaVirtualSession(int32 id, FStringView name)
		: UObject()
		, MyID(id), MyName(name)
	{}

	[[nodiscard]]
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network|Session")
	constexpr int32 GetID() const noexcept
	{
		return MyID;
	}

	[[nodiscard]]
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network|Session")
	constexpr const FString& GetName() const noexcept
	{
		return MyName;
	}

	UPROPERTY(VisibleAnywhere, meta = (NoResetToDefault, NoSpinbox = true, ClampMin = 2, UIMin = 2, ClampMax = 21, UIMax = 21))
	int32 MyID;
	UPROPERTY(VisibleAnywhere)
	FString MyName;
};

namespace saga
{
	using ::USagaVirtualSession;

	struct SAGAGAME_API FSagaSessionComparator final
	{
		[[nodiscard]]
		constexpr bool
			operator()(const USagaVirtualSession& lhs, const USagaVirtualSession& rhs)
			const noexcept
		{
			return lhs.MyID == rhs.MyID;
		}

		[[nodiscard]]
		constexpr bool
			operator()(const USagaVirtualSession& lhs, const int32& id)
			const noexcept
		{
			return lhs.MyID == id;
		}
	};

	struct SAGAGAME_API FSagaSessionIdComparator final
	{
		explicit constexpr FSagaSessionIdComparator(int32 another_id) noexcept
			: cmpId(another_id)
		{}

		[[nodiscard]]
		constexpr bool
			operator()(const USagaVirtualSession& lhs)
			const noexcept
		{
			return lhs.MyID == cmpId;
		}

		int32 cmpId;
	};
}
