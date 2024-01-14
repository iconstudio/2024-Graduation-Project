#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class [[nodiscard]] EUserInputCategory : uint8
{
	MOVE_PRESS,
	INPUT_MOVE_RELEASE,
	INPUT_ATTACK_PRESS,
	INPUT_ATTACK_RELEASE,
	INPUT_JUMP,
	INPUT_ACTION,
	INPUT_RELOAD,
	INPUT_RIDE,
	INPUT_INVENTORY,
};

namespace net
{
	using UserInputCategory = ::EUserInputCategory;
}
