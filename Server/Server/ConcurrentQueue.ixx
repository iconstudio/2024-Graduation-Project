export module Iconer.Collection.Concurrent.Queue;
import <string>;
import <format>;

export namespace iconer::collection
{
	class ConcurrentQueue
	{
	public:
		explicit constexpr ConcurrentQueue() noexcept = default;
		~ConcurrentQueue();

		[[nodiscard]] constexpr bool operator==(const ConcurrentQueue&) const noexcept = default;

	private:
	};
}

export namespace std
{
	[[nodiscard]] string to_string(const iconer::collection::ConcurrentQueue& queue);
	[[nodiscard]] string to_string(const volatile iconer::collection::ConcurrentQueue& queue);
}

export template<>
struct std::formatter<iconer::collection::ConcurrentQueue, char>
{
	static format_parse_context::iterator
		parse(format_parse_context& context)
		noexcept;

	static format_context::iterator
		format(const iconer::collection::ConcurrentQueue& queue, format_context& context)
		noexcept;
};

export template<>
struct std::formatter<iconer::collection::ConcurrentQueue, wchar_t>
{
	static wformat_parse_context::iterator
		parse(wformat_parse_context& context)
		noexcept;

	static wformat_context::iterator
		format(const iconer::collection::ConcurrentQueue& queue, wformat_context& context)
		noexcept;
};
