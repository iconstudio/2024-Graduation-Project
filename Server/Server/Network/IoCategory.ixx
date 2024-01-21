export module Iconer.Net.IoCategory;
import <cstdint>;
import <string>;
import <format>;

export namespace iconer::net
{
	enum class [[nodiscard]] IoCategory : std::int32_t
	{};
}

export namespace std
{
	[[nodiscard]] string to_string(const iconer::net::IoCategory& category);
	[[nodiscard]] string to_string(iconer::net::IoCategory&& category);
}

/// <summary>
/// {i} : format to int32_t
/// </summary>
export template<>
struct std::formatter<iconer::net::IoCategory, char>
{
	static format_parse_context::iterator
		parse(format_parse_context& context)
		noexcept;

	static format_context::iterator
		format(const iconer::net::IoCategory& category, format_context& context)
		noexcept;

	static format_context::iterator
		format(iconer::net::IoCategory&& category, format_context& context)
		noexcept;
};

/// <summary>
/// {i} : format to int32_t
/// </summary>
export template<>
struct std::formatter<iconer::net::IoCategory, wchar_t>
{
	static wformat_parse_context::iterator
		parse(wformat_parse_context& context)
		noexcept;

	static wformat_context::iterator
		format(const iconer::net::IoCategory& category, wformat_context& context)
		noexcept;

	static wformat_context::iterator
		format(iconer::net::IoCategory&& category, wformat_context& context)
		noexcept;
};
