#pragma once
#include "CoreMinimal.h"
#include "PacketType.h"
#include "BasicPacket.generated.h"

USTRUCT(Atomic, BlueprintType, Blueprintable, meta = (DisplayName = "Basic Packet"))
struct CPPDEMO202312280021_API FBasicPacket
{
	GENERATED_BODY()

public:
	constexpr FBasicPacket() noexcept = default;
	constexpr ~FBasicPacket() noexcept = default;

	[[nodiscard]]
	virtual size_t GetByteSize() const noexcept
	{
		return sizeof(myType);
	}
	
	[[nodiscard]]
	virtual TSharedPtr<uint8> Serialize() const
	{
		return nullptr;
	}

	[[nodiscard]]
	virtual TSharedPtr<uint8> Serialize(TSharedPtr<uint8> buffer) const
	{
		return buffer;
	}

protected:
	UPROPERTY(NoClear, VisibleAnywhere, BlueprintEditable, meta = (DisplayName = "Internet Protocol"))
	EPacketType myType;
};
