export module Iconer.Application.Packet:ClientToServerPackets;
export import Iconer.Application.BasicPacket;
import Iconer.Utility.Serializer;
import <cstddef>;
import <utility>;
import <algorithm>;

export namespace iconer::app::packets::inline cs
{
#pragma pack(push, 1)
	/// <summary>
	/// Game initiating packet for client
	/// </summary>
	/// <remarks>Client would send it to the server</remarks>
	struct [[nodiscard]] CS_GameStartPacket : public BasicPacket
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

		constexpr CS_GameStartPacket() noexcept
			: Super(PacketProtocol::CS_GAME_START, SignedWannabeSize())
		{
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			return iconer::util::Serializes(myProtocol, mySize);
		}
	};
	/// <summary>
	/// Room create packet for client
	/// </summary>
	/// <param name="roomTitle">Title of the new room</param>
	/// <remarks>Client would send it to the server</remarks>
	struct [[nodiscard]] CS_CreateRoomPacket : public BasicPacket
	{
		using Super = BasicPacket;

		static inline constexpr size_t roomTitleLength = 16;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(roomTitle);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(roomTitle));
		}

		constexpr CS_CreateRoomPacket() noexcept
			: Super(PacketProtocol::CS_ROOM_CREATE, SignedWannabeSize())
			, roomTitle()
		{
		}

		explicit constexpr CS_CreateRoomPacket(const wchar_t* begin, const wchar_t* end)
			: Super(PacketProtocol::CS_ROOM_CREATE, SignedWannabeSize())
			, roomTitle()
		{
			std::copy(begin, end, roomTitle);
		}

		explicit constexpr CS_CreateRoomPacket(const wchar_t* nts, const size_t length)
			: Super(PacketProtocol::CS_ROOM_CREATE, SignedWannabeSize())
			, roomTitle()
		{
			std::copy_n(nts, std::min(length, roomTitleLength), roomTitle);
		}

		template<size_t Length>
		explicit constexpr CS_CreateRoomPacket(const wchar_t(&str)[Length])
			: Super(PacketProtocol::CS_ROOM_CREATE, SignedWannabeSize())
			, roomTitle()
		{
			std::copy_n(str, std::min(Length, roomTitleLength), roomTitle);
		}

		template<size_t Length>
		explicit constexpr CS_CreateRoomPacket(wchar_t(&& str)[Length])
			: Super(PacketProtocol::CS_ROOM_CREATE, SignedWannabeSize())
			, roomTitle()
		{
			std::move(str, str + std::min(Length, roomTitleLength), roomTitle);
		}

		[[nodiscard]]
		constexpr auto Serialize() const
		{
			return iconer::util::Serializes(myProtocol, mySize, roomTitle);
		}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			return iconer::util::Serialize(Super::Write(buffer), std::wstring_view{ roomTitle });
		}

		constexpr const std::byte* Read(const std::byte* buffer, const size_t& buffer_length)
		{
			return iconer::util::Deserialize(Super::Read(buffer), buffer_length, roomTitle);
		}

		wchar_t roomTitle[roomTitleLength];
	};
	/// <summary>
	/// Room entering packet for client
	/// </summary>
	/// <param name="roomId"/>
	/// <remarks>Client would send it to the server</remarks>
	struct [[nodiscard]] CS_EnterRoomPacket : public BasicPacket
	{
		using Super = BasicPacket;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(std::int32_t);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(std::int32_t));
		}

		constexpr CS_EnterRoomPacket() noexcept
			: CS_EnterRoomPacket(-1)
		{
		}

		constexpr CS_EnterRoomPacket(std::int32_t room_id) noexcept
			: Super(PacketProtocol::CS_ROOM_JOIN, SignedWannabeSize())
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
			return iconer::util::Serializes(Super::Write(buffer), roomId);
		}

		constexpr const std::byte* Read(const std::byte* buffer)
		{
			return iconer::util::Deserialize(Super::Read(buffer), roomId);
		}

		std::int32_t roomId;
	};
	/// <summary>
	/// Room leaving packet for client
	/// </summary>
	/// <remarks>Client would send it to the server</remarks>
	struct [[nodiscard]] CS_LeaveRoomPacket : public BasicPacket
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

		constexpr CS_LeaveRoomPacket() noexcept
			: Super(PacketProtocol::CS_ROOM_LEAVE, SignedWannabeSize())
		{
		}
	};
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

		constexpr CS_UpdatePositionPacket() noexcept
			: CS_UpdatePositionPacket(0, 0, 0)
		{
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
			: Super(PacketProtocol::CS_SIGNIN, SignedWannabeSize())
			, userName()
		{
		}

		explicit constexpr CS_SignInPacket(const wchar_t* begin, const wchar_t* end)
			: Super(PacketProtocol::CS_SIGNIN, SignedWannabeSize())
			, userName()
		{
			std::copy(begin, end, userName);
		}

		explicit constexpr CS_SignInPacket(const wchar_t* nts, const size_t length)
			: Super(PacketProtocol::CS_SIGNIN, SignedWannabeSize())
			, userName()
		{
			std::copy_n(nts, std::min(length, nickNameLength), userName);
		}

		template<size_t Length>
		explicit constexpr CS_SignInPacket(const wchar_t(&str)[Length])
			: Super(PacketProtocol::CS_SIGNIN, SignedWannabeSize())
			, userName()
		{
			std::copy_n(str, std::min(Length, nickNameLength), userName);
		}

		template<size_t Length>
		explicit constexpr CS_SignInPacket(wchar_t(&& str)[Length])
			: Super(PacketProtocol::CS_SIGNIN, SignedWannabeSize())
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
#pragma pack(pop)
}
