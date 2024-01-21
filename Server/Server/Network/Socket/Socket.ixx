export module Iconer.Net.Socket;
export import :SocketOption;
import <cstdint>;
import <format>;

export namespace iconer::net
{
	class Socket
	{
	public:
		using native_handle_t = std::uintptr_t;

		explicit constexpr Socket() noexcept = default;
		constexpr ~Socket() noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Socket&) const noexcept = default;

	private:
	};
}
