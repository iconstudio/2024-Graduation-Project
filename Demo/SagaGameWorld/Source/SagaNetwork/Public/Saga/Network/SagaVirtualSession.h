#pragma once
#include "UObject/ObjectMacros.h"
#include "CoreTypes.h"
#include "Containers/UnrealString.h"
#include "Templates/UnrealTemplate.h"

#include "SagaVirtualSession.generated.h"

USTRUCT(BlueprintType, Category = "CandyLandSaga|Network|Session")
struct SAGANETWORK_API FSagaVirtualSession
{
	GENERATED_BODY()

public:
	FSagaVirtualSession()
		: MyID(-1), MyName(TEXT("Empty Client"))
	{
	}

	FSagaVirtualSession(int32 id)
		: MyID(id), MyName(TEXT("Empty Client"))
	{
	}
	
	FSagaVirtualSession(int32 id, FStringView name)
		: MyID(id), MyName(name)
	{
	}

	void Name(const FString& name)
	{
		if (name.Len() == 0)
		{
			MyName.Reset();
		}
		else
		{
			MyName = name;
		}
	}
	
	void Name(FStringView name)
	{
		if (name.Len() == 0)
		{
			MyName.Reset();
		}
		else
		{
			MyName = name;
		}
	}

	[[nodiscard]]
	constexpr int32 ID() const noexcept
	{
		return MyID;
	}

	[[nodiscard]]
	const FString& Name() const noexcept
	{
		return MyName;
	}

	UPROPERTY(VisibleAnywhere, meta = (NoResetToDefault, NoSpinbox = true, ClampMin = 2, UIMin = 2, ClampMax = 21, UIMax = 21))
	int32 MyID;
	UPROPERTY(VisibleAnywhere)
	FString MyName;
};

[[nodiscard]]
UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network|Session")
int32 GetID(const FSagaVirtualSession& session) noexcept;

[[nodiscard]]
UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network|Session")
const FString& GetName(const FSagaVirtualSession& session) noexcept;

namespace saga
{
	using ::FSagaVirtualSession;

	struct SAGANETWORK_API FSagaSessionComparator final
	{
		[[nodiscard]]
		constexpr bool
			operator()(const FSagaVirtualSession& lhs, const FSagaVirtualSession& rhs)
			const noexcept
		{
			return lhs.MyID == rhs.MyID;
		}

		[[nodiscard]]
		constexpr bool
			operator()(const FSagaVirtualSession& lhs, const int32& id)
			const noexcept
		{
			return lhs.MyID == id;
		}
	};

	struct SAGANETWORK_API FSagaSessionIdComparator final
	{
		explicit constexpr FSagaSessionIdComparator(int32 another_id) noexcept
			: cmpId(another_id)
		{}

		[[nodiscard]]
		constexpr bool
			operator()(const FSagaVirtualSession& lhs)
			const noexcept
		{
			return lhs.MyID == cmpId;
		}

		int32 cmpId;
	};
}
