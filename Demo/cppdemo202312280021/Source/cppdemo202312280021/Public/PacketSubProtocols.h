#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class [[nodiscard]] EUserInputCategory : uint8
{
	MOVE_PRESS,
	MOVE_RELEASE,
	ATTACK_PRESS,
	ATTACK_RELEASE,
	JUMP,
	ACTION,
	RELOAD,
	RIDE,
	INVENTORY,
};

namespace net
{
	using UserInputCategory = ::EUserInputCategory;
}
