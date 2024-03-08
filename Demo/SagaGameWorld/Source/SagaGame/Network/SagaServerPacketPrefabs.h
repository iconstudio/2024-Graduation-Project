#pragma once
#include "SagaBasicPacket.h"
#include "SagaPacketProtocol.h"
#include "SagaRoomContract.h"
#include "SagaSerializer.h"
#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>
#include "SagaPacketHelper.inl"

namespace saga::datagrams
{
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
}

namespace saga::inline sc
{
	/// <summary>
	/// Getting game ready notification packet for server
	/// </summary>
	/// <remarks>Server would send it to the client</remarks>
	MAKE_EMPTY_PACKET(SC_ReadyForGamePacket, EPacketProtocol::SC_GAME_GETTING_READY);
	/// <summary>
	/// Game starting notification packet for server
	/// </summary>
	/// <remarks>Server would send it to the client</remarks>
	MAKE_EMPTY_PACKET(SC_GameStartPacket, EPacketProtocol::SC_GAME_START);
	/// <summary>
	/// Failed to start game notification packet for server
	/// </summary>
	/// <param name="errCause">- Cause of the failure</param>
	/// <remarks>Server would send it to the client</remarks>
	MAKE_EMPTY_PACKET_1VAR(SC_FailedGameStartingPacket, EPacketProtocol::SC_FAILED_GAME_START, int, errCause, error, true);
	/// <summary>
	/// Creating a client packet for server
	/// </summary>
	/// <param name="clientId">- An id of client</param>
	/// <param name="roomId"/>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_RespondVersionPacket : public FSagaBasicPacket
	{
		using Super = FSagaBasicPacket;

		static inline constexpr size_t versionLength = 10;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(gameVersion);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(WannabeSize());
		}

		constexpr SC_RespondVersionPacket() noexcept
			: Super(EPacketProtocol::CS_SIGNIN, SignedWannabeSize())
			, gameVersion()
		{
		}

		explicit constexpr SC_RespondVersionPacket(const wchar_t* begin, const wchar_t* end)
			: Super(EPacketProtocol::CS_SIGNIN, SignedWannabeSize())
			, gameVersion()
		{
			std::copy(begin, end, gameVersion);
		}

		explicit constexpr SC_RespondVersionPacket(const wchar_t* nts, const size_t length)
			: Super(EPacketProtocol::CS_SIGNIN, SignedWannabeSize())
			, gameVersion()
		{
			std::copy_n(nts, std::min(length, versionLength), gameVersion);
		}

		template<size_t Length>
		explicit constexpr SC_RespondVersionPacket(const wchar_t(&str)[Length])
			: Super(EPacketProtocol::CS_SIGNIN, SignedWannabeSize())
			, gameVersion()
		{
			std::copy_n(str, std::min(Length, versionLength), gameVersion);
		}

		template<size_t Length>
		explicit constexpr SC_RespondVersionPacket(wchar_t(&& str)[Length])
			: Super(EPacketProtocol::CS_SIGNIN, SignedWannabeSize())
			, gameVersion()
		{
			std::move(str, str + std::min(Length, versionLength), gameVersion);
		}

		[[nodiscard]]
		std::unique_ptr<std::byte[]> Serialize() const override
		{
			return saga::Serializes(myProtocol, mySize, std::wstring_view{ gameVersion, versionLength });
		}

		std::byte* Write(std::byte* buffer) const override
		{
			return saga::Serialize(Super::Write(buffer), std::wstring_view{ gameVersion, versionLength });
		}

		const std::byte* Read(const std::byte* buffer) override
		{
			return saga::Deserialize(Super::Read(buffer), versionLength, gameVersion);
		}

		wchar_t gameVersion[versionLength];
	};
	/// <summary>
	/// Show rooms response packet for server
	/// </summary>
	/// <param name="serializedRooms">- Serialized every room</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_RespondRoomsPacket : public FSagaBasicPacket
	{
		using Super = FSagaBasicPacket;

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
			: Super(EPacketProtocol::SC_RESPOND_ROOMS, static_cast<std::int16_t>(SignedWannabeSize()))
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
		std::unique_ptr<std::byte[]> Serialize() const override
		{
			std::unique_ptr<std::byte[]> buffer = std::make_unique<std::byte[]>(WannabeSize());

			Write(buffer.get());

			return std::move(buffer);
		}

		std::byte* Write(std::byte* buffer) const override
		{
			auto seek = saga::Serialize(saga::Serialize(buffer, myProtocol), static_cast<std::int16_t>(WannabeSize()));

			seek = saga::Serialize(seek, serializedRooms.size());

			for (auto& room : serializedRooms)
			{
				seek = saga::Serialize(seek, room.id);
				seek = saga::Serialize(seek, std::wstring_view{ room.title, room.nameLength });
				seek = saga::Serialize(seek, room.members);
			}

			return seek;
		}

		const std::byte* Read(const std::byte* buffer) override
		{
			auto seek = Super::Read(buffer);

			size_t size{};
			seek = saga::Deserialize(seek, size);

			if (0 < size)
			{
				serializedRooms.clear();
				serializedRooms.resize(size);

				for (auto& room : serializedRooms)
				{
					seek = saga::Deserialize(seek, room.id);
					seek = saga::Deserialize(seek, room.nameLength, room.title);
					seek = saga::Deserialize(seek, room.members);
				}
			}

			return seek;
		}

		std::vector<datagrams::SerializedRoom> serializedRooms;
	};
	/// <summary>
	/// Room members response packet for server
	/// </summary>
	/// <param name="serializedMembers">- Serialized members in the room</param>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_RespondMembersPacket : public FSagaBasicPacket
	{
		using Super = FSagaBasicPacket;

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
			: Super(EPacketProtocol::SC_RESPOND_USERS, static_cast<std::int16_t>(SignedWannabeSize()))
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
		std::unique_ptr<std::byte[]> Serialize() const override
		{
			std::unique_ptr<std::byte[]> buffer = std::make_unique<std::byte[]>(WannabeSize());

			Write(buffer.get());

			return std::move(buffer);
		}

		std::byte* Write(std::byte* buffer) const override
		{
			auto seek = saga::Serialize(saga::Serialize(buffer, myProtocol), static_cast<std::int16_t>(WannabeSize()));

			seek = saga::Serialize(seek, serializedMembers.size());

			for (auto& member : serializedMembers)
			{
				seek = saga::Serialize(seek, member.id);
				seek = saga::Serialize(seek, std::wstring_view{ member.nickname, member.nameLength });
			}

			return seek;
		}

		const std::byte* Read(const std::byte* buffer) override
		{
			auto seek = Super::Read(buffer);

			size_t size{};
			seek = saga::Deserialize(seek, size);

			if (0 < size)
			{
				serializedMembers.clear();
				serializedMembers.resize(size);

				for (auto& member : serializedMembers)
				{
					seek = saga::Deserialize(seek, member.id);
					seek = saga::Deserialize(seek, member.nameLength, member.nickname);
				}
			}

			return seek;
		}

		std::vector<datagrams::SerializedMember> serializedMembers;
	};
	/// <summary>
	/// Room created notification packet for server
	/// </summary>
	/// <param name="roomId">- An id of the created room</param>
	/// <remarks>Server would send it to the client</remarks>
	MAKE_EMPTY_PACKET_1VAR(SC_RoomCreatedPacket, EPacketProtocol::SC_ROOM_CREATED, std::int32_t, roomId, room_id, true);
	/// <summary>
	/// Failed to join to a room packet for server
	/// </summary>
	/// <param name="errCause">Reason of couldn't join to the room</param>
	/// <remarks>Server would send it to the client</remarks>
	MAKE_EMPTY_PACKET_1VAR(SC_RoomCreationFailedPacket, EPacketProtocol::SC_ROOM_CREATE_FAILED, RoomContract, errCause, cause, true);
	/// <summary>
	/// Joined to a room packet for server
	/// </summary>
	/// <param name="clientId">- An id of client</param>
	/// <param name="roomId">- An id of the room</param>
	/// <remarks>Server would send it to the client</remarks>
	MAKE_EMPTY_PACKET_2VAR_WITH_DEFAULT(SC_RoomJoinedPacket, EPacketProtocol::SC_ROOM_JOINED, std::int32_t, clientId, user_id, -1, std::int32_t, roomId, room_id, -1);
	/// <summary>
	/// Failed to join to a room packet for server
	/// </summary>
	/// <param name="errCause">- Reason of couldn't join to the room</param>
	/// <remarks>Server would send it to the client</remarks>
	MAKE_EMPTY_PACKET_1VAR(SC_RoomJoinFailedPacket, EPacketProtocol::SC_ROOM_JOIN_FAILED, RoomContract, errCause, cause, true);
	/// <summary>
	/// Room left packet for server
	/// </summary>
	/// <param name="clientId">- An id of client</param>
	/// <remarks>Server would send it to the client</remarks>
	MAKE_EMPTY_PACKET_1VAR_WITH_DEFAULT(SC_RoomLeftPacket, EPacketProtocol::SC_ROOM_LEFT, std::int32_t, clientId, user_id, -1);
	/// <summary>
	/// Creating a client packet for server
	/// </summary>
	/// <param name="clientId">- An id of client</param>
	/// <param name="roomId"/>
	/// <remarks>Server would send it to the client</remarks>
	struct [[nodiscard]] SC_CreatePlayerPacket : public FSagaBasicPacket
	{
		using Super = FSagaBasicPacket;

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
			: Super(EPacketProtocol::SC_CREATE_PLAYER, SignedWannabeSize())
			, clientId(id), userName()
		{
		}

		[[nodiscard]]
		std::unique_ptr<std::byte[]> Serialize() const override
		{
			return saga::Serializes(myProtocol, mySize, clientId, userName);
		}

		std::byte* Write(std::byte* buffer) const override
		{
			return saga::Serializes(Super::Write(buffer), clientId, userName);
		}

		const std::byte* Read(const std::byte* buffer) override
		{
			return saga::Deserialize(saga::Deserialize(Super::Read(buffer), clientId), nickNameLength, userName);
		}

		std::int32_t clientId;
		wchar_t userName[nickNameLength];
	};
	/// <summary>
	/// Remove a certain client packet for server
	/// </summary>
	/// <param name="clientId">- An id of client</param>
	/// <remarks>Server would send it to the client</remarks>
	MAKE_EMPTY_PACKET_1VAR(SC_DestroyPlayerPacket, EPacketProtocol::SC_REMOVE_PLAYER, std::int32_t, clientId, user_id, true);
	/// <summary>
	/// Assigning ID to client packet for server
	/// </summary>
	/// <param name="clientId">- An id of client</param>
	/// <remarks>Server would send it to the client</remarks>
	MAKE_EMPTY_PACKET_1VAR_WITH_DEFAULT(SC_SucceedSignInPacket, EPacketProtocol::SC_SIGNIN_SUCCESS, std::int32_t, clientId, user_id, -1);
	/// <summary>
	/// Assigning ID to client packet for server
	/// </summary>
	/// <param name="errCause">- Cause of the failure</param>
	/// <remarks>Server would send it to the client</remarks>
	MAKE_EMPTY_PACKET_1VAR(SC_FailedSignInPacket, EPacketProtocol::SC_SIGNIN_FAILURE, int, errCause, cause, true);
	/// <summary>
	/// Position packet for server
	/// </summary>
	/// <param name="clientId">- Target player's id</param>
	/// <param name="x"/>
	/// <param name="y"/>
	/// <param name="z"/>
	/// <remarks>Server would broadcast it to clients</remarks>
	struct [[nodiscard]] SC_UpdatePositionPacket : public FSagaBasicPacket
	{
		using Super = FSagaBasicPacket;

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
			: Super(EPacketProtocol::SC_MOVE_CHARACTER, SignedWannabeSize())
			, clientId(id), x(px), y(py), z(pz)
		{
		}

		[[nodiscard]]
		std::unique_ptr<std::byte[]> Serialize() const override
		{
			return saga::Serializes(myProtocol, mySize, clientId, x, y, z);
		}

		std::byte* Write(std::byte* buffer) const override
		{
			return saga::Serializes(Super::Write(buffer), clientId, x, y, z);
		}

		const std::byte* Read(const std::byte* buffer) override
		{
			return saga::Deserialize(saga::Deserialize(saga::Deserialize(saga::Deserialize(Super::Read(buffer), clientId), x), y), z);
		}

		std::int32_t clientId;
		float x, y, z;
	};
}
