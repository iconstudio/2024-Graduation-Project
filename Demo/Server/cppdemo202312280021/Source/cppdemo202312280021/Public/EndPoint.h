#pragma once
#include "CoreMinimal.h"
#include <type_traits>
#include "InternetProtocolAddress.h"
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
	constexpr const EIpAddressFamily& GetAddressFamily() const& noexcept
	{
		return myAddress.GetFamily();
	}

	[[nodiscard]]
	constexpr EIpAddressFamily&& GetAddressFamily() && noexcept
	{
		return std::move(myAddress).GetFamily();
	}

	[[nodiscard]]
	constexpr const FIpAddress& GetIpAddress() const& noexcept
	{
		return myAddress;
	}

	[[nodiscard]]
	constexpr FIpAddress&& GetIpAddress() && noexcept
	{
		return std::move(myAddress);
	}

	[[nodiscard]]
	constexpr const uint16& GetPort() const& noexcept
	{
		return myPort;
	}

	[[nodiscard]]
	constexpr uint16&& GetPort() && noexcept
	{
		return std::move(myPort);
	}

	[[nodiscard]]
	FString& GetAddressString() & noexcept
	{
		return myAddress.GetAddress();
	}

	[[nodiscard]]
	const FString& GetAddressString() const& noexcept
	{
		return myAddress.GetAddress();
	}

	FEndpoint(const FEndpoint&) noexcept = default;
	FEndpoint& operator=(const FEndpoint&) noexcept = default;
	FEndpoint(FEndpoint&&) noexcept = default;
	FEndpoint& operator=(FEndpoint&&) noexcept = default;

private:
	FIpAddress myAddress;
	uint16 myPort;
};

namespace net
{
	using EndPoint = ::FEndpoint;
}
