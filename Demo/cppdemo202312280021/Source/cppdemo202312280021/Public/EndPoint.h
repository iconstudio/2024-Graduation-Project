#pragma once
#include "CoreMinimal.h"
#include <type_traits>
#include "IPAddress.h"
#include "Endpoint.generated.h"

USTRUCT(BlueprintType, Blueprintable, meta = (DisplayName = "Endpoint"))
struct [[nodiscard]] CPPDEMO202312280021_API FEndpoint final
{
	GENERATED_BODY()

public:
	FEndpoint() noexcept = default;
	~FEndpoint() noexcept = default;

	FEndpoint(const FIpAddress& ip, const uint16& port) noexcept;
	FEndpoint(FIpAddress&& ip, const uint16& port) noexcept;

	[[nodiscard]]
	constexpr const EIpAddressFamily& GetAddressFamily() const & noexcept
	{
		return myAddress.GetFamily();
	}

	[[nodiscard]]
	constexpr EIpAddressFamily&& GetAddressFamily() && noexcept
	{
		return std::move(myAddress).GetFamily();
	}

	[[nodiscard]]
	constexpr const FIpAddress& GetIpAddress() const & noexcept
	{
		return myAddress;
	}

	[[nodiscard]]
	constexpr FIpAddress&& GetIpAddress() && noexcept
	{
		return std::move(myAddress);
	}

	[[nodiscard]]
	constexpr uint16 GetPort() const noexcept
	{
		return static_cast<uint16>(myPort);
	}

	[[nodiscard]]
	FString& GetAddressString() & noexcept
	{
		return myAddress.GetAddress();
	}

	[[nodiscard]]
	const FString& GetAddressString() const & noexcept
	{
		return myAddress.GetAddress();
	}

	FEndpoint(const FEndpoint&) noexcept = default;
	FEndpoint& operator=(const FEndpoint&) noexcept = default;
	FEndpoint(FEndpoint&&) noexcept = default;
	FEndpoint& operator=(FEndpoint&&) noexcept = default;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "IP Address"))
	FIpAddress myAddress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Port"))
	int32 myPort;
};

UCLASS(ClassGroup = (Iconer))
class CPPDEMO202312280021_API UFEndpointFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Iconer")
	static FEndpoint CreateEndPoint(FString address, EIpAddressFamily family, int32 port) noexcept;

	UFUNCTION(BlueprintCallable, Category = "Iconer")
	static FEndpoint CreateEndPointBy(const FIpAddress& ip_address, int32 port) noexcept;
};

namespace net
{
	using EndPoint = ::FEndpoint;
}