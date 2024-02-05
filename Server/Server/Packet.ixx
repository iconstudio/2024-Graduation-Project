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
	/// Login packet for client
	/// </summary>
	/// <param name="userName">Nickname of client</param>
	/// <remarks>Client would send it to the server</remarks>
	struct [[nodiscard]] CS_SignInPacket : public BasicPacket
	{
		using Super = BasicPacket;

		[[nodiscard]]
		static consteval size_t WannabeSize() noexcept
		{
			return Super::MinSize() + sizeof(userName);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedWannabeSizeSize() noexcept
		{
			return static_cast<ptrdiff_t>(Super::MinSize() + sizeof(userName));
		}

		constexpr CS_SignInPacket() noexcept
			: Super(PacketProtocol::CS_SIGNIN, CS_SignInPacket::SignedWannabeSizeSize())
			, userName()
		{
		}

		explicit constexpr CS_SignInPacket(const wchar_t* begin, const wchar_t* end)
			: Super(PacketProtocol::CS_SIGNIN, CS_SignInPacket::SignedWannabeSizeSize())
			, userName()
		{
			std::copy(begin, end, userName);
		}

		explicit constexpr CS_SignInPacket(const wchar_t* nts, const size_t length)
			: Super(PacketProtocol::CS_SIGNIN, CS_SignInPacket::SignedWannabeSizeSize())
			, userName()
		{
			std::copy_n(nts, length, userName);
		}

		template<size_t Length>
		explicit constexpr CS_SignInPacket(const wchar_t(&str)[Length])
			: Super(PacketProtocol::CS_SIGNIN, CS_SignInPacket::SignedWannabeSizeSize())
			, userName()
		{
			std::copy_n(str, Length, userName);
		}

		template<size_t Length>
		explicit constexpr CS_SignInPacket(wchar_t(&&str)[Length])
			: Super(PacketProtocol::CS_SIGNIN, CS_SignInPacket::SignedWannabeSizeSize())
			, userName()
		{
			std::move(str, str + Length, userName);
		}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			return iconer::util::Serialize(Super::Write(buffer), std::wstring_view{ userName });
		}

		constexpr const std::byte* Read(const std::byte* buffer, const size_t& buffer_length)
		{
			return iconer::util::Deserialize(Super::Read(buffer), buffer_length, userName);
		}

		wchar_t userName[16];
	};
#pragma pack(pop)
}
