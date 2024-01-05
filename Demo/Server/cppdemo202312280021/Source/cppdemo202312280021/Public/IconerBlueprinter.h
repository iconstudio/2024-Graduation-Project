#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ErrorCode.h"
#include "IconerBlueprinter.generated.h"

UCLASS(ClassGroup = (Iconer))
class CPPDEMO202312280021_API UIconerBlueprinter : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};

UCLASS(ClassGroup = (Iconer))
class CPPDEMO202312280021_API UNetworkUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Iconer")
	static uint32 AcquireNetworkErrorByInteger() noexcept;
	UFUNCTION(BlueprintCallable, Category = "Iconer")
	static EErrorCode AcquireNetworkError() noexcept;
}
