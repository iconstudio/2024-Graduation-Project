export module Iconer.Application.Packet;
export import Iconer.Application.BasicPacket;
import Iconer.Utility.Serializer;
import <cstddef>;
import <utility>;
import <algorithm>;

export namespace iconer::app::packets
{
#pragma pack(push, 1)
	/// <summary>
	/// Position packet for client
	/// </summary>
	/// <param name="x"/>
	/// <param name="y"/>
	/// <param name="z"/>
	/// <remarks>Client would send it to the server</remarks>
	struct [[nodiscard]] CS_UpdatePositionPacket : public BasicPacket
	{
		using Super = BasicPacket;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(float) * 3;
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(float) * 3);
		}

		constexpr CS_UpdatePositionPacket(float px, float py, float pz) noexcept
			: Super(PacketProtocol::CS_MY_POSITION, SignedWannabeSize())
			, x(px), y(py), z(pz)
		{
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			return iconer::util::Serializes(myProtocol, mySize, x, y, z);
		}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			return iconer::util::Serializes(Super::Write(buffer), x, y, z);
		}

		constexpr const std::byte* Read(const std::byte* buffer)
		{
			return iconer::util::Deserialize(iconer::util::Deserialize(iconer::util::Deserialize(Super::Read(buffer), x), y), z);
		}

		float x, y, z;
	};
	/// <summary>
	/// Login packet for client
	/// </summary>
	/// <param name="userName">Nickname of client</param>
	/// <remarks>Client would send it to the server</remarks>
	struct [[nodiscard]] CS_SignInPacket : public BasicPacket
	{
		using Super = BasicPacket;

		static inline constexpr size_t nickNameLength = 16;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(userName);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(userName));
		}

		constexpr CS_SignInPacket() noexcept
			: Super(PacketProtocol::CS_SIGNIN, CS_SignInPacket::SignedWannabeSize())
			, userName()
		{
		}

		explicit constexpr CS_SignInPacket(const wchar_t* begin, const wchar_t* end)
			: Super(PacketProtocol::CS_SIGNIN, CS_SignInPacket::SignedWannabeSize())
			, userName()
		{
			std::copy(begin, end, userName);
		}

		explicit constexpr CS_SignInPacket(const wchar_t* nts, const size_t length)
			: Super(PacketProtocol::CS_SIGNIN, CS_SignInPacket::SignedWannabeSize())
			, userName()
		{
			std::copy_n(nts, std::min(length, nickNameLength), userName);
		}

		template<size_t Length>
		explicit constexpr CS_SignInPacket(const wchar_t(&str)[Length])
			: Super(PacketProtocol::CS_SIGNIN, CS_SignInPacket::SignedWannabeSize())
			, userName()
		{
			std::copy_n(str, std::min(Length, nickNameLength), userName);
		}

		template<size_t Length>
		explicit constexpr CS_SignInPacket(wchar_t(&& str)[Length])
			: Super(PacketProtocol::CS_SIGNIN, CS_SignInPacket::SignedWannabeSize())
			, userName()
		{
			std::move(str, str + std::min(Length, nickNameLength), userName);
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			return iconer::util::Serializes(myProtocol, mySize, userName);
		}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			return iconer::util::Serialize(Super::Write(buffer), std::wstring_view{ userName });
		}

		constexpr const std::byte* Read(const std::byte* buffer, const size_t& buffer_length)
		{
			return iconer::util::Deserialize(Super::Read(buffer), buffer_length, userName);
		}

		wchar_t userName[nickNameLength];
	};
	/// <summary>
	/// Assigning ID to client packet for server
	/// </summary>
	/// <param name="userName">An id of client</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_SucceedSignInPacket : public BasicPacket
	{
		using Super = BasicPacket;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(clientId);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(clientId));
		}

		constexpr SC_SucceedSignInPacket() noexcept
			: SC_SucceedSignInPacket(-1)
		{
		}

		constexpr SC_SucceedSignInPacket(int id) noexcept
			: Super(PacketProtocol::SC_SIGNIN_SUCCESS, CS_SignInPacket::SignedWannabeSize())
			, clientId(id)
		{
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			return iconer::util::Serializes(myProtocol, mySize, clientId);
		}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			return iconer::util::Serialize(Super::Write(buffer), clientId);
		}

		constexpr const std::byte* Read(const std::byte* buffer)
		{
			return iconer::util::Deserialize(Super::Read(buffer), clientId);
		}

		int clientId;
	};
	/// <summary>
	/// Assigning ID to client packet for server
	/// </summary>
	/// <param name="errCause">Cause of the failure</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_FailedSignInPacket : public BasicPacket
	{
		using Super = BasicPacket;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize();
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize());
		}

		constexpr SC_FailedSignInPacket() noexcept
			: Super(PacketProtocol::SC_SIGNIN_SUCCESS, CS_SignInPacket::SignedWannabeSize())
		{
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			return iconer::util::Serializes(myProtocol, mySize, errCause);
		}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			return iconer::util::Serialize(Super::Write(buffer), errCause);
		}

		constexpr const std::byte* Read(const std::byte* buffer)
		{
			return iconer::util::Deserialize(Super::Read(buffer), errCause);
		}

		int errCause;
	};
	/// <summary>
	/// Position packet for server
	/// </summary>
	/// <param name="clientId">- Target player's id</param>
	/// <param name="x"/>
	/// <param name="y"/>
	/// <param name="z"/>
	/// <remarks>Server would broadcast it to clients</remarks>
	struct [[nodiscard]] SC_UpdatePositionPacket : public BasicPacket
	{
		using Super = BasicPacket;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(int) + sizeof(float) * 3;
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(int) + sizeof(float) * 3);
		}

		constexpr SC_UpdatePositionPacket(int id, float px, float py, float pz) noexcept
			: Super(PacketProtocol::SC_MOVE_CHARACTER, SignedWannabeSize())
			, clientId(id), x(px), y(py), z(pz)
		{
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			return iconer::util::Serializes(myProtocol, mySize, clientId, x, y, z);
		}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			return iconer::util::Serializes(Super::Write(buffer), clientId, x, y, z);
		}

		constexpr const std::byte* Read(const std::byte* buffer)
		{
			return iconer::util::Deserialize(iconer::util::Deserialize(iconer::util::Deserialize(iconer::util::Deserialize(Super::Read(buffer), clientId), x), y), z);
		}

		int clientId;
		float x, y, z;
	};
#pragma pack(pop)
}
