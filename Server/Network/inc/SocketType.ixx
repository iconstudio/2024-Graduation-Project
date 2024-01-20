export module Net.Socket:Type;
import <cstdint>;

export namespace net
{
	enum class [[nodiscard]] SocketType : std::uint32_t
	{
		Synchronous  = 0b000000000U,
		Asynchronous = 0b000000001U,
		Registered   = 0b100000000U,
	};
}
