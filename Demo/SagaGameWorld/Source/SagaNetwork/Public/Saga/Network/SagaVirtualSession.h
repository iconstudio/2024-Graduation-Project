#pragma once
#include "SagaNetwork.h"

#include "SagaVirtualSession.generated.h"

USTRUCT(BlueprintType, Atomic, Category = "CandyLandSaga|Level|UI|Element")
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
	
	FSagaVirtualSession(int32 id, const FString& name)
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (NoResetToDefault, NoSpinbox = true, ClampMin = 2, UIMin = 2, ClampMax = 21, UIMax = 21))
	int32 MyID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MyName;
};

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
