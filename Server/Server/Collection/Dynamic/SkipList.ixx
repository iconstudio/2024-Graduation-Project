export module Iconer.Collection.SkipList;
import <string>;
import <format>;

export namespace iconer::collection
{
	class SkipList
	{
	public:
		explicit constexpr SkipList() noexcept = default;
		~SkipList();

		[[nodiscard]] constexpr bool operator==(const SkipList&) const noexcept = default;

	private:
	};
}

export namespace std
{
	[[nodiscard]] string to_string(const iconer::collection::SkipList& list);
}

export template<>
struct std::formatter<iconer::collection::SkipList, char>
{
	static format_parse_context::iterator
		parse(format_parse_context& context)
		noexcept;

	static format_context::iterator
		format(const iconer::collection::SkipList& list, format_context& context)
		noexcept;
};

export template<>
struct std::formatter<iconer::collection::SkipList, wchar_t>
{
	static wformat_parse_context::iterator
		parse(wformat_parse_context& context)
		noexcept;

	static wformat_context::iterator
		format(const iconer::collection::SkipList& list, wformat_context& context)
		noexcept;
};
