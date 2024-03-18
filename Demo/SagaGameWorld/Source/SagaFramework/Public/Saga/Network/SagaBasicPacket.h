#pragma once
#include "SagaFramework.h"
#include "Saga/Network/SagaPacketProtocol.h"

#include "SagaBasicPacket.generated.h"

USTRUCT(BlueprintType)
struct SAGAFRAMEWORK_API FSagaBasicPacket
{
	GENERATED_BODY()

public:
	[[nodiscard]] static consteval size_t MinSize() noexcept
	{
		return sizeof(EPacketProtocol) + sizeof(int16);
	}

	[[nodiscard]] static consteval ptrdiff_t SignedMinSize() noexcept
	{
		return static_cast<ptrdiff_t>(MinSize());
	}

	constexpr FSagaBasicPacket() noexcept
		: FSagaBasicPacket(EPacketProtocol::UNKNOWN, SignedMinSize())
	{
	}

	explicit constexpr FSagaBasicPacket(const EPacketProtocol& protocol) noexcept
		: FSagaBasicPacket(protocol, SignedMinSize())
	{
	}

	explicit constexpr FSagaBasicPacket(EPacketProtocol&& protocol) noexcept
		: FSagaBasicPacket(std::move(protocol), SignedMinSize())
	{
	}

	explicit constexpr FSagaBasicPacket(const EPacketProtocol& protocol, int16 size) noexcept
		: myProtocol(protocol), mySize(size)
	{
	}

	explicit constexpr FSagaBasicPacket(EPacketProtocol&& protocol, int16 size) noexcept
		: myProtocol(std::move(protocol)), mySize(size)
	{
	}

	virtual constexpr ~FSagaBasicPacket() noexcept = default;

	/// <summary>패킷을 직렬화합니다</summary>
	/// <returns>할당된 포인터</returns>
	/// <exception cref="bad_alloc">메모리 할당 실패</exception>
	[[nodiscard]]
	virtual TUniquePtr<uint8[]> Serialize() const;

	/// <summary>패킷을 직렬화하고 버퍼에 씁니다</summary>
	/// <returns>마지막으로 쓴 포인터 위치</returns>
	/// <exception cref="bad_alloc">메모리 할당 실패</exception>
	/// <exception cref="out_of_range">메모리 접근 위반</exception>
	virtual uint8* Write(uint8* buffer) const;

	/// <summary>버퍼를 읽어서 패킷을 역직렬화합니다</summary>
	/// <returns>마지막으로 읽은 포인터 위치</returns>
	/// <exception cref="out_of_range">메모리 접근 위반</exception>
	virtual const uint8* Read(const uint8* buffer);

	UPROPERTY(VisibleAnywhere)
	EPacketProtocol myProtocol;
	UPROPERTY(VisibleAnywhere)
	int16 mySize;
};
