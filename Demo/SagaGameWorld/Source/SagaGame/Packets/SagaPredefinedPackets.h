#pragma once
#include "CoreMinimal.h"
#include "SagaPacketProtocol.h"
#include "SagaBasicPacket.h"

/// <summary>
/// Login packet for client
/// </summary>
/// <param name="userName">Nickname of client</param>
/// <remarks>Client would send it to the server</remarks>
struct [[nodiscard]] FSagaPacket_CS_SignIn final : public FSagaBasicPacket
{
	using Super = FSagaBasicPacket;

	static inline constexpr size_t nickNameLength = 16;

	[[nodiscard]] static consteval size_t WannabeSize() noexcept
	{
		return Super::MinSize() + sizeof(userName);
	}

	[[nodiscard]] static consteval ptrdiff_t SignedWannabeSize() noexcept
	{
		return static_cast<ptrdiff_t>(Super::SignedMinSize() + sizeof(userName));
	}

	constexpr FSagaPacket_CS_SignIn() noexcept
		: Super(EPacketProtocol::CS_SIGNIN, FSagaPacket_CS_SignIn::SignedWannabeSize()), userName()
	{
	}

	explicit constexpr FSagaPacket_CS_SignIn(const wchar_t* begin, const wchar_t* end)
		: Super(EPacketProtocol::CS_SIGNIN, FSagaPacket_CS_SignIn::SignedWannabeSize()), userName()
	{
		std::copy(begin, end, userName);
	}

	explicit constexpr FSagaPacket_CS_SignIn(const wchar_t* nts, const size_t length)
		: Super(EPacketProtocol::CS_SIGNIN, FSagaPacket_CS_SignIn::SignedWannabeSize()), userName()
	{
		std::copy_n(nts, std::min(length, nickNameLength), userName);
	}

	template <size_t Length>
	explicit constexpr FSagaPacket_CS_SignIn(const wchar_t (&str)[Length])
		: Super(EPacketProtocol::CS_SIGNIN, FSagaPacket_CS_SignIn::SignedWannabeSize()), userName()
	{
		std::copy_n(str, std::min(Length, nickNameLength), userName);
	}

	template <size_t Length>
	explicit constexpr FSagaPacket_CS_SignIn(wchar_t (&&str)[Length])
		: Super(EPacketProtocol::CS_SIGNIN, FSagaPacket_CS_SignIn::SignedWannabeSize()), userName()
	{
		std::move(str, str + std::min(Length, nickNameLength), userName);
	}

	///<inheritdoc/>
	[[nodiscard]] virtual TUniquePtr<uint8[]> Serialize() const override
	{
		return FSerializer::Serializes(static_cast<uint8>(myProtocol), mySize, std::wstring_view{userName});
	}

	virtual uint8* Write(uint8* buffer) const override
	{
		return FSerializer::Serialize(Super::Write(buffer), std::wstring_view{userName});
	}

	virtual const uint8* Read(const uint8* buffer) override
	{
		return FDeserializer::Deserialize(Super::Read(buffer), nickNameLength, userName);
	}

	wchar_t userName[nickNameLength];
};

/// <summary>
/// Position packet for client
/// </summary>
/// <remarks>Client would send it to the server</remarks>
struct [[nodiscard]] FSagaPacket_CS_ClientPosition final : public FSagaBasicPacket
{
	using Super = FSagaBasicPacket;

	static inline constexpr size_t nickNameLength = 16;

	[[nodiscard]] static consteval size_t WannabeSize() noexcept
	{
		return Super::MinSize() + sizeof(float) * 3;
	}

	[[nodiscard]] static consteval ptrdiff_t SignedWannabeSize() noexcept
	{
		return static_cast<ptrdiff_t>(Super::SignedMinSize() + sizeof(float) * 3);
	}

	constexpr FSagaPacket_CS_ClientPosition() noexcept
		: Super(EPacketProtocol::CS_SIGNIN, FSagaPacket_CS_SignIn::SignedWannabeSize()), ox(), oy(), oz()
	{
	}

	explicit constexpr FSagaPacket_CS_ClientPosition(const float x, const float y, const float z)
		: Super(EPacketProtocol::CS_SIGNIN, FSagaPacket_CS_SignIn::SignedWannabeSize()), ox(x), oy(y), oz(z)
	{
	}

	///<inheritdoc/>
	[[nodiscard]] virtual TUniquePtr<uint8[]> Serialize() const override
	{
		return FSerializer::Serializes(static_cast<uint8>(myProtocol), mySize, ox, oy, oz);
	}

	virtual uint8* Write(uint8* buffer) const override
	{
		return FSerializer::Serialize(FSerializer::Serialize(FSerializer::Serialize(Super::Write(buffer), ox), oy), oz);
	}

	virtual const uint8* Read(const uint8* buffer) override
	{
		return FDeserializer::Deserialize(FDeserializer::Deserialize(FDeserializer::Deserialize(Super::Read(buffer), ox), oy), oz);
	}

	float ox, oy, oz;
};

struct SAGAGAME_API FSagaPacket_SC_SucceedSignIn final : public FSagaBasicPacket
{
	using Super = FSagaBasicPacket;

	[[nodiscard]] static consteval size_t WannabeSize() noexcept
	{
		return Super::MinSize() + sizeof(clientId);
	}

	[[nodiscard]] static consteval ptrdiff_t SignedWannabeSize() noexcept
	{
		return static_cast<ptrdiff_t>(Super::SignedMinSize() + sizeof(clientId));
	}

	constexpr FSagaPacket_SC_SucceedSignIn() noexcept
		: FSagaPacket_SC_SucceedSignIn(-1)
	{
	}

	constexpr FSagaPacket_SC_SucceedSignIn(int id) noexcept
		: Super(EPacketProtocol::SC_SIGNIN_SUCCESS, FSagaPacket_SC_SucceedSignIn::SignedWannabeSize()), clientId(id)
	{
	}

	///<inheritdoc/>
	[[nodiscard]] virtual TUniquePtr<uint8[]> Serialize() const override
	{
		return FSerializer::Serializes(static_cast<uint8>(myProtocol), mySize, clientId);
	}

	///<inheritdoc/>
	virtual uint8* Write(uint8* buffer) const override
	{
		return FSerializer::Serialize(Super::Write(buffer), clientId);
	}

	///<inheritdoc/>
	virtual const uint8* Read(const uint8* buffer) override
	{
		return FDeserializer::Deserialize(Super::Read(buffer), clientId);
	}

	int clientId;
};
