#pragma once
#include "CoreMinimal.h"

#include "SagaVirtualSession.h"
#include "../Character/SagaCharacterPlayer.h"
#include "../Utility/MacroHelper.inl"
#include "SagaVirtualUser.generated.h"

UCLASS(BlueprintType, Blueprintable, Category = "CandyLandSaga|Network|Session")
class SAGAGAME_API USagaVirtualUser : public USagaVirtualSession
{
	GENERATED_BODY()

public:
	USagaVirtualUser()
		: USagaVirtualSession()
		, ownedCharacter(0)
	{}

	USagaVirtualUser(int32 id, FStringView name)
		: USagaVirtualSession(id, name)
		, ownedCharacter(0)
	{}


	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Session")
	void SetCharacter(ASagaCharacterPlayer* character) noexcept
	{
		ownedCharacter = character;
	}

	[[nodiscard]]
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Network|Session")
	ASagaCharacterPlayer* GetCharacter() const noexcept
	{
		return ownedCharacter;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CandyLandSaga|Network|Session")
	ASagaCharacterPlayer* ownedCharacter;
};
