export module Iconer.Application.Packet;
export import Iconer.Application.BasicPacket;
import Iconer.Utility.Serializer;
import <cstddef>;
import <utility>;

export namespace iconer::app::packets
{
#pragma pack(push, 1)
	struct [[nodiscard]] SignInPacket : public BasicPacket
	{
		[[nodiscard]]
		static consteval size_t ByteSize() noexcept
		{
			return sizeof(PacketProtocol) + sizeof(std::int16_t) + sizeof(userName);
		}

		[[nodiscard]]
		static consteval std::int16_t SignedByteSize() noexcept
		{
			return static_cast<std::int16_t>(sizeof(BasicPacket) + sizeof(userName));
		}

		constexpr SignInPacket() noexcept
			: BasicPacket{ PacketProtocol::CS_SIGNIN, SignInPacket::SignedByteSize() }
		{}

		constexpr std::byte* Write(std::byte* buffer) const
		{
			return iconer::util::Serialize(BasicPacket::Write(buffer), std::wstring_view{ userName });
		}

		constexpr const std::byte* Read(const std::byte* buffer, const size_t& buffer_length)
		{
			return iconer::util::Deserialize(BasicPacket::Read(buffer), buffer_length, userName);
		}

		wchar_t userName[64];
	};
#pragma pack(pop)
}
