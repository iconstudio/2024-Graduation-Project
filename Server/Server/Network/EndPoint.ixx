export module Iconer.Net.EndPoint;
import <string>;
import <format>;

export namespace iconer::net
{
	class EndPoint
	{
	public:
		explicit constexpr EndPoint() noexcept = default;
		constexpr ~EndPoint() noexcept = default;

		[[nodiscard]] constexpr bool operator==(const EndPoint&) const noexcept = default;

	private:
	};
}

export namespace std
{
	[[nodiscard]] string to_string(const iconer::net::EndPoint& endpoint);
}

export template<>
struct std::formatter<iconer::net::EndPoint, char>
{
	static format_parse_context::iterator
		parse(format_parse_context& context)
		noexcept;

	static format_context::iterator
		format(const iconer::net::EndPoint& ep, format_context& context)
		noexcept;
};

export template<>
struct std::formatter<iconer::net::EndPoint, wchar_t>
{
	static wformat_parse_context::iterator
		parse(wformat_parse_context& context)
		noexcept;

	static wformat_context::iterator
		format(const iconer::net::EndPoint& ep, wformat_context& context)
		noexcept;
};
