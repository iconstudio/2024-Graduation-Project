#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "SagaNetworkView.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI, Category = "CandyLandSaga/Network")
class USagaNetworkView : public UInterface
{
	GENERATED_BODY()
};

class SAGAGAME_API ISagaNetworkView
{
	GENERATED_BODY()

public:
	/// <summary>원격 플레이어 접속</summary>
	/// <param name="NewbieID">들어온 플레이어의 ID</param>
	UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga/Network/Event")
	void OnPlayerConnected(const int32 NewbieID);
	/// <summary>원격 플레이어 종료</summary>
	/// <param name="PlayerID">나간 플레이어의 ID</param>
	UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga/Network/Event")
	void OnPlayerDisconnected(const int32 PlayerID);

	/// <summary>플레이어 접속 성공</summary>
	/// <param name="LocalID">부여된 나의 ID</param>
	UFUNCTION(BlueprintNativeEvent, Category = "CandyLandSaga/Network/Event")
	void OnConnected(const int32 LocalID);

	[[nodiscard]]
	constexpr int32 GetID() const noexcept
	{
		return MyID;
	}

	int32 MyID;
};
