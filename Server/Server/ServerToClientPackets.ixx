module;
#include <cstddef>
#include <memory>
#include <utility>
#include <algorithm>
#include <vector>

export module Iconer.Application.Packet:ServerToClientPackets;
import Iconer.Utility.Serializer;
export import Iconer.Application.BasicPacket;
export import Iconer.Application.RoomContract;

export namespace iconer::app::packets::datagrams
{
#pragma pack(push, 1)
	struct SerializedRoom
	{
		static inline constexpr size_t nameLength = 16;

		std::int32_t id;
		wchar_t title[nameLength];
		size_t members;
	};
	struct [[nodiscard]] SerializedMember
	{
		static inline constexpr size_t nameLength = 16;

		std::int32_t id;
		wchar_t nickname[nameLength];
	};
#pragma pack(pop)
}

export namespace iconer::app::packets::inline sc
{
#pragma pack(push, 1)
	/// <summary>
	/// Getting game ready notification packet for server
	/// </summary>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_ReadyForGamePacket : public BasicPacket
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
			return Super::SignedMinSize();
		}

		constexpr SC_ReadyForGamePacket() noexcept
			: Super(PacketProtocol::SC_GAME_GETTING_READY, SignedWannabeSize())
		{
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			return iconer::util::Serializes(myProtocol, mySize);
		}
	};
	/// <summary>
	/// Game starting notification packet for server
	/// </summary>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_GameStartPacket : public BasicPacket
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
			return Super::SignedMinSize();
		}

		constexpr SC_GameStartPacket() noexcept
			: Super(PacketProtocol::SC_GAME_START, SignedWannabeSize())
		{
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			return iconer::util::Serializes(myProtocol, mySize);
		}
	};
	/// <summary>
	/// Failed to start game notification packet for server
	/// </summary>
	/// <param name="errCause">Cause of the failure</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_FailedGameStartingPacket : public BasicPacket
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

		constexpr SC_FailedGameStartingPacket() noexcept
			: SC_FailedGameStartingPacket(0)
		{
		}

		constexpr SC_FailedGameStartingPacket(int reason) noexcept
			: Super(PacketProtocol::SC_FAILED_GAME_START, SignedWannabeSize())
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
	/// Show rooms response packet for server
	/// </summary>
	/// <param name="serializedRooms">Serialized every room</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_RespondRoomsPacket : public BasicPacket
	{
		using Super = BasicPacket;

		[[nodiscard]]
		static consteval size_t MaxSize() noexcept
		{
			return Super::MinSize() + sizeof(datagrams::SerializedRoom) * 20 + sizeof(std::vector<datagrams::SerializedRoom>::size_type);
		}

		[[nodiscard]]
		constexpr size_t WannabeSize() const noexcept
		{
			return Super::MinSize() + sizeof(datagrams::SerializedRoom) * serializedRooms.size() + sizeof(std::vector<datagrams::SerializedRoom>::size_type);
		}

		[[nodiscard]]
		constexpr ptrdiff_t SignedWannabeSize() const noexcept
		{
			return static_cast<ptrdiff_t>(WannabeSize());
		}

		constexpr SC_RespondRoomsPacket() noexcept
			: Super(PacketProtocol::SC_RESPOND_ROOMS, SignedWannabeSize())
			, serializedRooms()
		{
		}

		constexpr void AddMember(std::int32_t room_id, std::wstring_view title, size_t members_count)
		{
			datagrams::SerializedRoom room{ room_id };

			auto it = room.title;
			for (auto ch : title)
			{
				*it = ch;

				if (++it == room.title + sizeof(room.title)) break;
			}
			room.members = members_count;

			serializedRooms.emplace_back(std::move(room));
			mySize = static_cast<std::int16_t>(WannabeSize());
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			std::unique_ptr<std::byte[]> buffer = std::make_unique<std::byte[]>(WannabeSize());
			auto seek = Super::Write(buffer.get());

			seek = iconer::util::Serialize(seek, serializedRooms.size());
			for (auto& room : serializedRooms)
			{
				seek = iconer::util::Serialize(seek, room.id);
				seek = iconer::util::Serialize(seek, std::wstring_view{ room.title, room.nameLength });
				seek = iconer::util::Serialize(seek, room.members);
			}

			return std::move(buffer);
		}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			auto seek = iconer::util::Serialize(Super::Write(buffer), serializedRooms.size());

			for (auto& room : serializedRooms)
			{
				seek = iconer::util::Serialize(seek, room.id);
				seek = iconer::util::Serialize(seek, std::wstring_view{ room.title, room.nameLength });
				seek = iconer::util::Serialize(seek, room.members);
			}

			return seek;
		}

		constexpr const std::byte* Read(const std::byte* buffer)
		{
			auto seek = Super::Read(buffer);

			size_t size{};
			seek = iconer::util::Deserialize(seek, size);

			if (0 < size)
			{
				serializedRooms.clear();
				serializedRooms.resize(size);

				for (auto& room : serializedRooms)
				{
					seek = iconer::util::Deserialize(seek, room.id);
					seek = iconer::util::Deserialize(seek, room.nameLength, room.title);
					seek = iconer::util::Deserialize(seek, room.members);
				}
			}

			return seek;
		}

		std::vector<datagrams::SerializedRoom> serializedRooms;
	};
	/// <summary>
	/// Room members response packet for server
	/// </summary>
	/// <param name="serializedMembers">Serialized members in the room</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_RespondMembersPacket : public BasicPacket
	{
		using Super = BasicPacket;

		[[nodiscard]]
		static consteval size_t MaxSize() noexcept
		{
			return Super::MinSize() + sizeof(datagrams::SerializedMember) * 6 + sizeof(std::vector<datagrams::SerializedMember>::size_type);
		}
		
		[[nodiscard]]
		constexpr size_t WannabeSize() const noexcept
		{
			return Super::MinSize() + sizeof(datagrams::SerializedMember) * serializedMembers.size() + sizeof(std::vector<datagrams::SerializedMember>::size_type);
		}

		[[nodiscard]]
		constexpr ptrdiff_t SignedWannabeSize() const noexcept
		{
			return static_cast<ptrdiff_t>(WannabeSize());
		}

		constexpr SC_RespondMembersPacket() noexcept
			: Super(PacketProtocol::SC_RESPOND_USERS, SignedWannabeSize())
			, serializedMembers()
		{
		}

		constexpr void AddMember(std::int32_t id, std::wstring_view name)
		{
			datagrams::SerializedMember member{ id };

			auto it = member.nickname;
			for (auto ch : name)
			{
				*it = ch;

				if (++it == member.nickname + sizeof(member.nickname)) break;
			}

			serializedMembers.emplace_back(std::move(member));
			mySize = static_cast<std::int16_t>(WannabeSize());
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			std::unique_ptr<std::byte[]> buffer = std::make_unique<std::byte[]>(WannabeSize());
			auto seek = Super::Write(buffer.get());

			seek = iconer::util::Serialize(seek, serializedMembers.size());
			for (auto& member : serializedMembers)
			{
				seek = iconer::util::Serialize(seek, member.id);
				seek = iconer::util::Serialize(seek, std::wstring_view{ member.nickname, member.nameLength });
			}

			return std::move(buffer);
		}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			auto seek = iconer::util::Serialize(Super::Write(buffer), serializedMembers.size());

			for (auto& member : serializedMembers)
			{
				seek = iconer::util::Serialize(seek, member.id);
				seek = iconer::util::Serialize(seek, std::wstring_view{ member.nickname, member.nameLength });
			}

			return seek;
		}

		constexpr const std::byte* Read(const std::byte* buffer)
		{
			auto seek = Super::Read(buffer);

			size_t size{};
			seek = iconer::util::Deserialize(seek, size);

			if (0 < size)
			{
				serializedMembers.clear();
				serializedMembers.resize(size);

				for (auto& member : serializedMembers)
				{
					seek = iconer::util::Deserialize(seek, member.id);
					seek = iconer::util::Deserialize(seek, member.nameLength, member.nickname);
				}
			}

			return seek;
		}

		std::vector<datagrams::SerializedMember> serializedMembers;
	};
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
			return Super::MinSize() + sizeof(errCause);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(errCause));
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
