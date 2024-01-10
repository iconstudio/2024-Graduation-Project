#pragma once
#include "CoreMinimal.h"
#include "Containers/UnrealString.h"
#include "IpAddressFamily.h"
#include "InternetProtocolAddress.generated.h"

struct FSerializedIpAddress;

USTRUCT(BlueprintType, Blueprintable, meta = (DisplayName = "Internal Protocol Address"))
struct CPPDEMO202312280021_API FIpAddress final
{
	GENERATED_BODY()

public:
	FIpAddress() noexcept = default;
	~FIpAddress() noexcept = default;

	FIpAddress(const EIpAddressFamily& family, const FString& address) noexcept;
	FIpAddress(const EIpAddressFamily& family, FString&& address) noexcept;

	[[nodiscard]]
	FSerializedIpAddress Serialize() const;
	bool TrySerialize(FSerializedIpAddress& out) const noexcept;

	[[nodiscard]]
	constexpr FString& GetAddress() & noexcept
	{
		return ipAddress;
	}

	[[nodiscard]]
	constexpr const FString& GetAddress() const& noexcept
	{
		return ipAddress;
	}

	[[nodiscard]]
	constexpr FString&& GetAddress() && noexcept
	{
		return static_cast<FString&&>(ipAddress);
	}

	[[nodiscard]]
	constexpr const FString&& GetAddress() const&& noexcept
	{
		return static_cast<const FString&&>(ipAddress);
	}

	[[nodiscard]]
	constexpr const EIpAddressFamily& GetFamily() const& noexcept
	{
		return addressFamily;
	}

	[[nodiscard]]
	constexpr EIpAddressFamily&& GetFamily() && noexcept
	{
		return static_cast<EIpAddressFamily&&>(addressFamily);
	}

	[[nodiscard]]
	bool operator==(const FIpAddress&) const noexcept = default;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EIpAddressFamily addressFamily;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, NoClear)
	FString ipAddress;

protected:
	//UPROPERTY(NoClear, VisibleAnywhere, BlueprintReadOnly, meta = (GetByRef))
};


USTRUCT(BlueprintType, Blueprintable, meta = (DisplayName = "Serialized Internal Protocol Address"))
struct [[nodiscard]] CPPDEMO202312280021_API FSerializedIpAddress final
{
	GENERATED_BODY()

public:
	constexpr FSerializedIpAddress() noexcept = default;
	constexpr ~FSerializedIpAddress() noexcept = default;

	char data[64];
};

namespace net
{
	using IpAddress = ::FIpAddress;
}