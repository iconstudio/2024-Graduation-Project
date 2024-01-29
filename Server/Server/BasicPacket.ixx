export module Iconer.Application.BasicPacket;
export import :Protocol;
import <cstddef>;
import <utility>;
export import <span>;

export namespace iconer::app
{
	struct [[nodiscard]] BasicPacket
	{
		explicit constexpr BasicPacket() noexcept = default;
		virtual constexpr ~BasicPacket() noexcept = default;

		explicit constexpr BasicPacket(const PacketProtocol& protocol) noexcept
			: myProtocol(protocol), mySize(0)
		{
		}

		explicit constexpr BasicPacket(PacketProtocol&& protocol) noexcept
			: myProtocol(std::move(protocol)), mySize(0)
		{
		}

		[[nodiscard]]
		virtual std::byte* Serialize() const = 0;

		[[nodiscard]]
		virtual BasicPacket* Read(std::span<const std::byte> buffer) const = 0;

		[[nodiscard]]
		constexpr PacketProtocol GetProtocol() const noexcept
		{
			return myProtocol;
		}

		[[nodiscard]]
		virtual size_t GetByteSize() const noexcept = 0;

		[[nodiscard]]
		static consteval size_t MinSize() noexcept
		{
			return sizeof(PacketProtocol) + sizeof(std::uint32_t);
		}

		[[nodiscard]]
		static consteval ptrdiff_t SignedMinSize() noexcept
		{
			return static_cast<ptrdiff_t>(sizeof(PacketProtocol) + sizeof(std::uint32_t));
		}

		constexpr BasicPacket(const BasicPacket&) noexcept = default;
		constexpr BasicPacket& operator=(const BasicPacket&) noexcept = default;
		constexpr BasicPacket(BasicPacket&&) noexcept = default;
		constexpr BasicPacket& operator=(BasicPacket&&) noexcept = default;

		PacketProtocol myProtocol;
		std::uint32_t mySize;
	};
}
