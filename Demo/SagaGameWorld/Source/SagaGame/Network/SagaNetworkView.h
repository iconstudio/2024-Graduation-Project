#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "SagaNetworkView.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI, Category = "CandyLandSaga|Network")
class USagaNetworkView : public UInterface
{
	GENERATED_BODY()
};

class SAGAGAME_API ISagaNetworkView
{
	GENERATED_BODY()

public:
	ISagaNetworkView() noexcept
		: MyID(-1), MyName(TEXT("Empty Client"))
	{}

	ISagaNetworkView(int32 id, FStringView name) noexcept
		: MyID(id), MyName(name)
	{}

	/// <summary>로컬 플레이어 접속 성공</summary>
	/// <param name="local_id">부여된 나의 ID</param>
	UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnConnected(const int32 local_id);
	/// <summary>원격 플레이어 접속</summary>
	/// <param name="newbie_id">들어온 플레이어의 ID</param>
	UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnPlayerConnected(const int32 newbie_id);
	/// <summary>플레이어 종료</summary>
	/// <param name="user_id">나간 플레이어의 ID</param>
	UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga|Network|Event")
	void OnPlayerDisconnected(const int32 user_id);

	void SetName(nullptr_t) noexcept
	{
		MyName.Reset();
	}

	void SetName(FStringView name)
	{
		MyName = name;
	}

	[[nodiscard]]
	constexpr int32 GetID() const noexcept
	{
		return MyID;
	}

	[[nodiscard]]
	const FString& GetName() const& noexcept
	{
		return MyName;
	}

	[[nodiscard]]
	FString&& GetName() && noexcept
	{
		return MoveTempIfPossible(MyName);
	}

	int32 MyID;
	FString MyName;
};
