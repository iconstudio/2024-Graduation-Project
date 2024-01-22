export module Iconer.Net.IoEvent;
import <format>;

export namespace iconer::net
{
	class IoEvent
	{
	public:
		explicit constexpr IoEvent() noexcept = default;
		constexpr ~IoEvent() noexcept = default;

		[[nodiscard]] constexpr bool operator==(const IoEvent&) const noexcept = default;

	private:
	};
}

export template<>
struct std::formatter<iconer::net::IoEvent, char>
{
	static format_parse_context::iterator
		parse(format_parse_context& context)
		noexcept;

	static format_context::iterator
		format(const iconer::net::IoEvent& event, format_context& context)
		noexcept;
};

export template<>
struct std::formatter<iconer::net::IoEvent, wchar_t>
{
	static wformat_parse_context::iterator
		parse(wformat_parse_context& context)
		noexcept;

	static wformat_context::iterator
		format(const iconer::net::IoEvent& event, wformat_context& context)
		noexcept;
};
