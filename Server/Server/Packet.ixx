export module Iconer.Application.Packet;
import Iconer.Utility.TypeTraits;
export import Iconer.Application.BasicPacket;

export namespace iconer::app::packets
{
	struct [[nodiscard]] SignInPacket : public BasicPacket
	{
		[[nodiscard]]
		constexpr size_t GetByteSize() const noexcept override
		{
			return byte_size_v<PacketProtocol, wchar_t[64]>;
		}

		// @param buffer - read buffer
		// @return Address of SignInPacket
		[[nodiscard]]
		void* Read(std::span<std::byte> buffer) const override
		{
			SignInPacket* result = new SignInPacket{};
			result->myProtocol = static_cast<PacketProtocol>(buffer[0]);
			std::memcpy(result->userName, buffer.data() + 1, buffer.size_bytes() - sizeof(PacketProtocol));

			return nullptr;
		}

		[[nodiscard]]
		std::byte* Serialize() const override
		{
			std::byte* result = new std::byte[GetByteSize()]{};
			result[0] = static_cast<std::byte>(myProtocol);
			
			std::memcpy(result + 1, userName, sizeof(userName));

			return result;
		}

		wchar_t userName[64];
	};
}
