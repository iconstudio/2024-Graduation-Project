#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../NativeSocket.h"
#include "IconerBlueprinter.generated.h"

UCLASS(ClassGroup = (Iconer))
class CPPDEMO202312280021_API UIconerBlueprinter : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Iconer")
	static FNativeSocket CreateNativeSocket(EIoSynchronousType type, const EInternetProtocol& protocol, const EIpAddressFamily& family) noexcept;

	UFUNCTION(BlueprintCallable, Category = "Iconer")
	static bool TryCreateNativeSocket(EIoSynchronousType type, const EInternetProtocol& protocol, const EIpAddressFamily& family, FAttentSocket& out, EErrorCode& error_code) noexcept;
};
