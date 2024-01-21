export module Iconer.Net.IoContext;
import <format>;

export namespace iconer::net
{
	class IoContext
	{
	public:
		explicit constexpr IoContext() noexcept = default;
		constexpr ~IoContext() noexcept = default;

		[[nodiscard]] constexpr bool operator==(const IoContext&) const noexcept = default;

	private:
	};
}

export template<>
struct std::formatter<iconer::net::IoContext, char>
{
	static format_parse_context::iterator
		parse(format_parse_context& context)
		noexcept;

	static format_context::iterator
		format(const iconer::net::IoContext& ctx, format_context& context)
		noexcept;
};

export template<>
struct std::formatter<iconer::net::IoContext, wchar_t>
{
	static wformat_parse_context::iterator
		parse(wformat_parse_context& context)
		noexcept;

	static wformat_context::iterator
		format(const iconer::net::IoContext& ctx, wformat_context& context)
		noexcept;
};
