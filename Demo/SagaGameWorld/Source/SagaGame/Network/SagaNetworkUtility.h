#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Templates/UnrealTemplate.h"
#include "Templates/SharedPointer.h"
#include "Templates/UniquePtr.h"

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

	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static int32 SendUniqueBuffer(UPARAM(ref) FSocket& socket, const TUniquePtr<uint8[]>& buffer, int32 size);
	
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static int32 SendMovedUniqueBuffer(UPARAM(ref) FSocket& socket,  UPARAM(ref) TUniquePtr<uint8[]>&& buffer, int32 size);
	
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static int32 SendSharedBuffer(UPARAM(ref) FSocket& socket, const TSharedPtr<uint8[]>& buffer, int32 size);
	
	UFUNCTION(BlueprintCallable, Category = "CandyLandSaga/Network")
	static int32 SendBufferFromSharedHandle(UPARAM(ref) FSocket& socket, const TSharedRef<uint8[]>& buffer, int32 size);
};
