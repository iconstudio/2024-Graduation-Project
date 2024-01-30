module;
export module Iconer.Application.BasicPacket;
export import :Protocol;
export import Iconer.Utility.Serializer;
import <cstddef>;
import <utility>;
export import <span>;

export namespace iconer::app
{
#pragma pack(push, 1)
	struct [[nodiscard]] BasicPacket
	{
		constexpr std::byte* Write(std::byte* buffer) const
		{
			return iconer::util::Serialize(iconer::util::Serialize(buffer, std::to_underlying(myProtocol)), mySize);
		}

		constexpr const std::byte* Read(const std::byte* buffer)
		{
			return iconer::util::Deserialize(iconer::util::Deserialize(buffer, myProtocol), mySize);
		}

		[[nodiscard]]
		static consteval size_t MinSize() noexcept
		{
			return sizeof(PacketProtocol) + sizeof(std::int16_t);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedMinSize() noexcept
		{
			return static_cast<ptrdiff_t>(sizeof(PacketProtocol) + sizeof(std::int16_t));
		}

		PacketProtocol myProtocol;
		std::int16_t mySize;
	};
#pragma pack(pop)
}
