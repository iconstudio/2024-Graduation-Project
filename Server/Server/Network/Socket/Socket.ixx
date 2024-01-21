export module Iconer.Net.Socket;
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

export template<>
struct std::formatter<iconer::net::Socket, char>
{
	static format_parse_context::iterator
		parse(format_parse_context& context)
		noexcept;

	static format_context::iterator
		format(const iconer::net::Socket& sk, format_context& context)
		noexcept;
};

export template<>
struct std::formatter<iconer::net::Socket, wchar_t>
{
	static wformat_parse_context::iterator
		parse(wformat_parse_context& context)
		noexcept;

	static wformat_context::iterator
		format(const iconer::net::Socket& sk, wformat_context& context)
		noexcept;
};
