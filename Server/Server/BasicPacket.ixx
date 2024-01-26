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
			: myProtocol(protocol)
		{
		}

		explicit constexpr BasicPacket(PacketProtocol&& protocol) noexcept
			: myProtocol(std::move(protocol))
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

		constexpr BasicPacket(const BasicPacket&) noexcept = default;
		constexpr BasicPacket& operator=(const BasicPacket&) noexcept = default;
		constexpr BasicPacket(BasicPacket&&) noexcept = default;
		constexpr BasicPacket& operator=(BasicPacket&&) noexcept = default;

		PacketProtocol myProtocol;
	};
}
