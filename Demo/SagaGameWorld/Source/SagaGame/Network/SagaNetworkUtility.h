#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Interfaces/IPv4/IPv4Address.h"

#include "SagaNetworkUtility.generated.h"

UCLASS(Blueprintable, BlueprintType, Category = "CandyLandSaga/Network")
class SAGAGAME_API USagaNetworkUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static FSocket* CreateTcpSocket();
	
	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static TSharedRef<FInternetAddr> MakeEndPoint(const FIPv4Address IpAddress, const int32 Port);

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static TSharedRef<FInternetAddr> MakeEndPointFrom(const FString String, const int32 Port);

	[[nodiscard]] UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static FIPv4Address MakeIpAddress(const FString String);
};
