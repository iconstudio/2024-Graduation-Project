export module Iconer.Application.Packet:ServerToClientPackets;
import Iconer.Application.BasicPacket;
import Iconer.Utility.Serializer;
import <cstddef>;
import <utility>;
import <algorithm>;

export namespace iconer::app::packets
{
#pragma pack(push, 1)
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
			: Super(PacketProtocol::SC_SIGNIN_SUCCESS, SignedWannabeSize())
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
			: Super(PacketProtocol::SC_SIGNIN_SUCCESS, SignedWannabeSize())
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

		constexpr SC_UpdatePositionPacket()
			: SC_UpdatePositionPacket(-1, 0, 0, 0)
		{
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
