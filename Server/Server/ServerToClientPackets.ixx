export module Iconer.Application.Packet:ServerToClientPackets;
import Iconer.Utility.Serializer;
export import Iconer.Application.BasicPacket;
export import Iconer.Application.RoomContract;
import <cstddef>;
import <utility>;
import <algorithm>;

export namespace iconer::app::packets::inline sc
{
#pragma pack(push, 1)
	/// <summary>
	/// Room created notification packet for server
	/// </summary>
	/// <param name="roomId">An id of the created room</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_RoomCreatedPacket : public BasicPacket
	{
		using Super = BasicPacket;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(roomId);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(roomId));
		}

		constexpr SC_RoomCreatedPacket() noexcept
			: SC_RoomCreatedPacket(-1)
		{
		}

		constexpr SC_RoomCreatedPacket(std::int32_t room_id) noexcept
			: Super(PacketProtocol::SC_ROOM_CREATED, SignedWannabeSize())
			, roomId(room_id)
		{
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			return iconer::util::Serializes(myProtocol, mySize, roomId);
		}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			return iconer::util::Serialize(Super::Write(buffer), roomId);
		}

		constexpr const std::byte* Read(const std::byte* buffer)
		{
			return iconer::util::Deserialize(Super::Read(buffer), roomId);
		}

		std::int32_t roomId;
	};
	/// <summary>
	/// Failed to join to a room packet for server
	/// </summary>
	/// <param name="errCause">Reason of couldn't join to the room</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_RoomCreationFailedPacket : public BasicPacket
	{
		using Super = BasicPacket;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(errCause);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(errCause));
		}

		constexpr SC_RoomCreationFailedPacket() noexcept
			: SC_RoomCreationFailedPacket(RoomContract::Success)
		{
		}

		constexpr SC_RoomCreationFailedPacket(RoomContract cause) noexcept
			: Super(PacketProtocol::SC_ROOM_CREATE_FAILED, SignedWannabeSize())
			, errCause(cause)
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

		RoomContract errCause;
	};
	/// <summary>
	/// Joined to a room packet for server
	/// </summary>
	/// <param name="clientId">An id of client</param>
	/// <param name="roomId">An id of the room</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_RoomJoinedPacket : public BasicPacket
	{
		using Super = BasicPacket;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(clientId) + sizeof(roomId);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(clientId) + sizeof(roomId));
		}

		constexpr SC_RoomJoinedPacket() noexcept
			: SC_RoomJoinedPacket(-1, -1)
		{
		}

		constexpr SC_RoomJoinedPacket(std::int32_t user_id, std::int32_t room_id) noexcept
			: Super(PacketProtocol::SC_ROOM_JOINED, SignedWannabeSize())
			, clientId(user_id), roomId(room_id)
		{
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			return iconer::util::Serializes(myProtocol, mySize, clientId, roomId);
		}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			return iconer::util::Serializes(Super::Write(buffer), clientId, roomId);
		}

		constexpr const std::byte* Read(const std::byte* buffer)
		{
			return iconer::util::Deserialize(iconer::util::Deserialize(Super::Read(buffer), clientId), roomId);
		}

		std::int32_t clientId;
		std::int32_t roomId;
	};
	/// <summary>
	/// Failed to join to a room packet for server
	/// </summary>
	/// <param name="errCause">Reason of couldn't join to the room</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_RoomJoinFailedPacket : public BasicPacket
	{
		using Super = BasicPacket;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(errCause);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(errCause));
		}

		constexpr SC_RoomJoinFailedPacket() noexcept
			: SC_RoomJoinFailedPacket(RoomContract::Success)
		{
		}

		constexpr SC_RoomJoinFailedPacket(RoomContract cause) noexcept
			: Super(PacketProtocol::SC_ROOM_JOIN_FAILED, SignedWannabeSize())
			, errCause(cause)
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

		RoomContract errCause;
	};
	/// <summary>
	/// Room left packet for server
	/// </summary>
	/// <param name="clientId">An id of client</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_RoomLeftPacket : public BasicPacket
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

		constexpr SC_RoomLeftPacket() noexcept
			: SC_RoomLeftPacket(-1)
		{
		}
		
		constexpr SC_RoomLeftPacket(std::int32_t user_id) noexcept
			: Super(PacketProtocol::SC_ROOM_LEFT, SignedWannabeSize())
			, clientId(user_id)
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

		std::int32_t clientId;
	};
	/// <summary>
	/// Creating a client packet for server
	/// </summary>
	/// <param name="clientId">An id of client</param>
	/// <param name="roomId"/>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_CreatePlayerPacket : public BasicPacket
	{
		using Super = BasicPacket;

		static inline constexpr size_t nickNameLength = 16;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(clientId) + sizeof(userName);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(clientId) + sizeof(userName));
		}

		constexpr SC_CreatePlayerPacket() noexcept
			: SC_CreatePlayerPacket(-1)
		{
		}

		constexpr SC_CreatePlayerPacket(std::int32_t id) noexcept
			: Super(PacketProtocol::SC_CREATE_PLAYER, SignedWannabeSize())
			, clientId(id), userName()
		{
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			return iconer::util::Serializes(myProtocol, mySize, clientId, userName);
		}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			return iconer::util::Serializes(Super::Write(buffer), clientId, userName);
		}

		constexpr const std::byte* Read(const std::byte* buffer)
		{
			return iconer::util::Deserialize(iconer::util::Deserialize(Super::Read(buffer), clientId), nickNameLength, userName);
		}

		std::int32_t clientId;
		wchar_t userName[nickNameLength];
	};
	/// <summary>
	/// Remove a certain client packet for server
	/// </summary>
	/// <param name="clientId">An id of client</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_DestroyPlayerPacket : public BasicPacket
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

		constexpr SC_DestroyPlayerPacket() noexcept
			: SC_DestroyPlayerPacket(-1)
		{
		}

		constexpr SC_DestroyPlayerPacket(std::int32_t id) noexcept
			: Super(PacketProtocol::SC_REMOVE_PLAYER, SignedWannabeSize())
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

		std::int32_t clientId;
	};
	/// <summary>
	/// Assigning ID to client packet for server
	/// </summary>
	/// <param name="clientId">An id of client</param>
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

		constexpr SC_SucceedSignInPacket(std::int32_t id) noexcept
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

		std::int32_t clientId;
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
			: SC_FailedSignInPacket(0)
		{
		}

		constexpr SC_FailedSignInPacket(int reason) noexcept
			: Super(PacketProtocol::SC_SIGNIN_SUCCESS, SignedWannabeSize())
			, errCause(reason)
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

		constexpr SC_UpdatePositionPacket(std::int32_t id, float px, float py, float pz) noexcept
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

		std::int32_t clientId;
		float x, y, z;
	};
#pragma pack(pop)
}
