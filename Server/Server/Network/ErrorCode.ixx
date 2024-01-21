export module Iconer.Net.ErrorCode;
import <cstdint>;
import <string>;
import <format>;

export namespace iconer::net
{
	enum class [[nodiscard]] ErrorCode : std::int32_t
	{};
}

export namespace std
{
	[[nodiscard]] string to_string(const iconer::net::ErrorCode& category);
	[[nodiscard]] string to_string(iconer::net::ErrorCode&& category);
}

export template<>
struct std::formatter<iconer::net::ErrorCode, char>
{
	static format_parse_context::iterator
		parse(format_parse_context& context)
		noexcept;

	static format_context::iterator
		format(const iconer::net::ErrorCode& code, format_context& context)
		noexcept;

	static format_context::iterator
		format(iconer::net::ErrorCode&& code, format_context& context)
		noexcept;
};

export template<>
struct std::formatter<iconer::net::ErrorCode, wchar_t>
{
	static wformat_parse_context::iterator
		parse(wformat_parse_context& context)
		noexcept;

	static wformat_context::iterator
		format(const iconer::net::ErrorCode& code, wformat_context& context)
		noexcept;

	static wformat_context::iterator
		format(iconer::net::ErrorCode&& code, wformat_context& context)
		noexcept;
};
