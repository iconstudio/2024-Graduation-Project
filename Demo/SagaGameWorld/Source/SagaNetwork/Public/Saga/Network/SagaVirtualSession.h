#pragma once
#include "CoreMinimal.h"
#include "Containers/UnrealString.h"
#include "Templates/UnrealTemplate.h"

#include "SagaVirtualSession.generated.h"

USTRUCT(BlueprintType, Atomic, Category = "CandyLandSaga|Network|Session")
struct SAGANETWORK_API FSagaVirtualSession
{
	GENERATED_BODY()

public:
	FSagaVirtualSession() noexcept
		: MyID(-1), MyName(TEXT("Empty Client"))
	{
	}

	FSagaVirtualSession(int32 id) noexcept
		: MyID(id), MyName(TEXT("Empty Client"))
	{
	}
	
	FSagaVirtualSession(int32 id, FStringView name) noexcept
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CandyLandSaga|Network|Session")
	int32 MyID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CandyLandSaga|Network|Session")
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

namespace saga
{
	using ::FSagaVirtualSession;
}
