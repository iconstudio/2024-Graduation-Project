export module Iconer.Net.IoCompletionPort;
import <format>;

export namespace iconer::net
{
	class IoCompletionPort
	{
	public:
		explicit constexpr IoCompletionPort() noexcept = default;
		constexpr ~IoCompletionPort() noexcept = default;

		[[nodiscard]] constexpr bool operator==(const IoCompletionPort&) const noexcept = default;

	private:
	};
}

export template<>
struct std::formatter<iconer::net::IoCompletionPort, char>
{
	static format_parse_context::iterator
		parse(format_parse_context& context)
		noexcept;

	static format_context::iterator
		format(const iconer::net::IoCompletionPort& port, format_context& context)
		noexcept;
};

export template<>
struct std::formatter<iconer::net::IoCompletionPort, wchar_t>
{
	static wformat_parse_context::iterator
		parse(wformat_parse_context& context)
		noexcept;

	static wformat_context::iterator
		format(const iconer::net::IoCompletionPort& port, wformat_context& context)
		noexcept;
};
