export module Iconer.Net.IpAddress;
import <string>;
import <format>;

export namespace iconer::net
{
	class IpAddress
	{
	public:
		explicit constexpr IpAddress() noexcept = default;
		constexpr ~IpAddress() noexcept = default;

		[[nodiscard]] constexpr bool operator==(const IpAddress&) const noexcept = default;

	private:
	};
}

export namespace std
{
	[[nodiscard]] string to_string(const iconer::net::IpAddress& ip_address);
}

export template<>
struct std::formatter<iconer::net::IpAddress, char>
{
	static format_parse_context::iterator
		parse(format_parse_context& context)
		noexcept;

	static format_context::iterator
		format(const iconer::net::IpAddress& ip_address, format_context& context)
		noexcept;

	static format_context::iterator
		format(iconer::net::IpAddress&& ip_address, format_context& context)
		noexcept;
};

export template<>
struct std::formatter<iconer::net::IpAddress, wchar_t>
{
	static wformat_parse_context::iterator
		parse(wformat_parse_context& context)
		noexcept;

	static wformat_context::iterator
		format(const iconer::net::IpAddress& ip_address, wformat_context& context)
		noexcept;

	static wformat_context::iterator
		format(iconer::net::IpAddress&& ip_address, wformat_context& context)
		noexcept;
};
