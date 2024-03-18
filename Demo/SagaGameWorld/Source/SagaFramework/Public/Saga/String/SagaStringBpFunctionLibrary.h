#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "SagaStringBpFunctionLibrary.generated.h"

UCLASS(Category = "CandyLandSaga|Utility|String")
class SAGAFRAMEWORK_API USagaStringBpFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	[[nodiscard]] UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CandyLandSaga|Utility|String")
	static FString SubString(const FString& string, int32 first_index, int32 last_index);
};
