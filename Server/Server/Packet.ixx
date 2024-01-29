export module Iconer.Application.Packet;
export import Iconer.Application.BasicPacket;
import <cstddef>;
import <utility>;

export namespace iconer::app::packets
{
#pragma pack(push, 1)
	struct [[nodiscard]] SignInPacket : public BasicPacket
	{
		constexpr std::byte* Write(std::byte* buffer)
		{
			return iconer::util::Serialize(BasicPacket::Write(buffer), userName);
		}

		constexpr const std::byte* Read(const std::byte* buffer, const size_t& buffer_length)
		{
			return iconer::util::Deserialize(BasicPacket::Read(buffer), buffer_length, userName);
		}

		wchar_t userName[64];
	};
#pragma pack(pop)
}
