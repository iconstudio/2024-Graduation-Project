export module Iconer.Utility.Atomic;
import <atomic>;
import <format>;

/// <summary>
/// {a} : memory order acquire
/// {r} : memory order release
/// {o} : memory order acq_rel
/// {x} : memory order relaxed
/// {_} : memory order consume
/// {c} : memory order seq_cst
/// {}  : default
/// </summary>
[[nodiscard]]
constexpr std::memory_order ParseOrderSpec(const char ch)
{
	switch (ch)
	{
		case 'a': return std::memory_order_acquire;
		case 'r': return std::memory_order_release;
		case 'o': return std::memory_order_acq_rel;
		case 'x': return std::memory_order_relaxed;
		case '_': return std::memory_order_consume;
		case 'c': return std::memory_order_seq_cst;
		default: std::format_error{ "Invalid order specifier." };
	}
}
[[nodiscard]]
constexpr std::memory_order ParseOrderSpec(const wchar_t ch)
{
	switch (ch)
	{
		case L'a': return std::memory_order_acquire;
		case L'r': return std::memory_order_release;
		case L'o': return std::memory_order_acq_rel;
		case L'x': return std::memory_order_relaxed;
		case L'_': return std::memory_order_consume;
		case L'c': return std::memory_order_seq_cst;
		default: std::format_error{ "Invalid order specifier." };
	}
}


export template<typename T>
struct std::formatter<std::atomic<T>, char>
{
	constexpr format_parse_context::iterator
		parse(format_parse_context& context)
	{
		auto it = context.begin();
		auto end = context.end();
		if (it == end or *it != '{')
		{
			throw std::format_error{ "Invalid format string." };
		}

		if (*it != '{')
		{
			throw std::format_error{ "Missing '{' in format string." };
		}

		if (++it == end)
		{
			throw std::format_error{ "Missing '}' in format string." };
		}

		if (it != end and *it == '}')
		{
			readOrder = std::memory_order_seq_cst;
			writeOrder = std::memory_order_seq_cst;
			return it;
		}

		readOrder = ParseOrderSpec(*it);

		if (++it == end)
		{
			throw std::format_error{ "Missing '}' in format string." };
		}

		if (*it == '}')
		{
			writeOrder = readOrder;
		}

		writeOrder = ParseOrderSpec(*(it++));

		if (it != end and *it != '}')
		{
			throw std::format_error{ "Missing '}' in format string." };
		}

		return it;
	}

	format_context::iterator
		format(const std::atomic<T>& atomic, format_context& context)
		const noexcept
	{
		auto value = atomic.load(readOrder);
		format_context::iterator out = format_to(context.out(), "Atomic({})", value);
		atomic.store(value, writeOrder);
		return out;
	}

	format_context::iterator
		format(const volatile std::atomic<T>& atomic, format_context& context)
		const noexcept
	{
		auto value = atomic.load(readOrder);
		format_context::iterator out = format_to(context.out(), "Atomic({})", value);
		atomic.store(value, writeOrder);
		return out;
	}

	std::memory_order readOrder;
	std::memory_order writeOrder;
};

export template<typename T>
struct std::formatter<std::atomic<T>, wchar_t>
{
	constexpr wformat_parse_context::iterator
		parse(wformat_parse_context& context)
	{
		auto it = context.begin();
		auto end = context.end();
		if (it == end or *it != L'{')
		{
			throw std::format_error{ "Invalid format string." };
		}

		if (*it != L'{')
		{
			throw std::format_error{ "Missing '{' in format string." };
		}

		if (++it == end)
		{
			throw std::format_error{ "Missing '}' in format string." };
		}

		if (it != end and *it == L'}')
		{
			readOrder = std::memory_order_seq_cst;
			writeOrder = std::memory_order_seq_cst;
			return it;
		}

		readOrder = ParseOrderSpec(*it);

		if (++it == end)
		{
			throw std::format_error{ "Missing '}' in format string." };
		}

		if (*it == L'}')
		{
			writeOrder = readOrder;
		}

		writeOrder = ParseOrderSpec(*(it++));

		if (it == end or *it != L'}')
		{
			throw std::format_error{ "Missing '}' in format string." };
		}

		return it;
	}

	wformat_context::iterator
		format(const std::atomic<T>& atomic, wformat_context& context)
		const noexcept
	{
		auto value = atomic.load(readOrder);
		wformat_context::iterator out = format_to(context.out(), L"Atomic({})", value);
		atomic.store(value, writeOrder);
		return out;
	}

	wformat_context::iterator
		format(const volatile std::atomic<T>& atomic, wformat_context& context)
		const noexcept
	{
		auto value = atomic.load(readOrder);
		format_context::iterator out = format_to(context.out(), L"Atomic({})", value);
		atomic.store(value, writeOrder);
		return out;
	}

	std::memory_order readOrder;
	std::memory_order writeOrder;
};
