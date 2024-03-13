#pragma once
#include "CoreMinimal.h"

#include "SagaVirtualSession.h"
#include "../Character/SagaCharacterPlayer.h"
#include "../Utility/MacroHelper.inl"
#include "SagaVirtualUser.generated.h"

UCLASS(BlueprintType, Blueprintable, Category = "CandyLandSaga|Network|Session")
class SAGAGAME_API FSagaVirtualUser : public FSagaVirtualSession
{
	GENERATED_BODY()

public:
	using FSagaVirtualSession::FSagaVirtualSession;

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Session")
	void SetCharacter(ASagaCharacterPlayer& character) noexcept
	{
		ownedCharacter = &character;
	}

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga|Network|Session")
	void SetCharacterByPtr(ASagaCharacterPlayer* character) noexcept
	{
		ownedCharacter = character;
	}

	[[nodiscard]]
	UFUNCTION(BlueprintCallable, BlueprintGetter, Category = "CandyLandSaga|Network|Session")
	ASagaCharacterPlayer* GetCharacter() const noexcept
	{
		return ownedCharacter;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetCharacters, Category = "CandyLandSaga|Network|Session")
	ASagaCharacterPlayer* ownedCharacter;
};
