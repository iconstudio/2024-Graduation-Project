export module Iconer.Utility.Property;
import :IProperty;
import <typeinfo>;
import <concepts>;
import <string>;
import <format>;

export namespace iconer::util
{
	template<typename T, typename Context = void, bool Copyable = std::copyable<T>>
	using Property = IProperty<T, Context, false, Copyable, false, true>;

	template<typename T, typename Context = void, bool Copyable = std::copyable<T>>
	using CustomProperty = IProperty<T, Context, true, Copyable, false, false>;

	template<typename T, typename Context = void, bool Copyable = std::copyable<T>>
	using CustomNothrowProperty = IProperty<T, Context, true, Copyable, false, true>;

	template<typename T, typename Context = void, bool NothrowFn = false, bool Custom = false>
	using ReadonlyProperty = IProperty<T, Context, Custom, false, true, NothrowFn>;
}

export namespace std
{
	template<typename T, typename Context, bool Custom, bool Copyable, bool Readonly, bool Nothrow>
	[[nodiscard]]
	string
		to_string(const iconer::util::IProperty<T, Context, Custom, Copyable, Readonly, Nothrow>& property)
	{
		if constexpr (std::convertible_to<T, std::string>)
		{
			return static_cast<std::string>(property);
		}
		else
		{
			return std::to_string(static_cast<const T&>(property));
		}
	}

	template<typename T, typename Context, bool Custom, bool Copyable, bool Readonly, bool Nothrow>
	[[nodiscard]]
	string
		to_string(iconer::util::IProperty<T, Context, Custom, Copyable, Readonly, Nothrow>&& property)
	{
		if constexpr (std::convertible_to<T, std::string>)
		{
			return static_cast<std::string>(property);
		}
		else
		{
			return std::to_string(static_cast<const T&>(property));
		}
	}

	template<typename T, typename Context, bool Custom, bool Copyable, bool Readonly, bool Nothrow>
	[[nodiscard]]
	wstring
		to_wstring(const iconer::util::IProperty<T, Context, Custom, Copyable, Readonly, Nothrow>& property)
	{
		if constexpr (std::convertible_to<T, std::wstring>)
		{
			return static_cast<std::wstring>(property);
		}
		else
		{
			return std::to_wstring(static_cast<const T&>(property));
		}
	}

	template<typename T, typename Context, bool Custom, bool Copyable, bool Readonly, bool Nothrow>
	[[nodiscard]]
	wstring
		to_wstring(iconer::util::IProperty<T, Context, Custom, Copyable, Readonly, Nothrow>&& property)
	{
		if constexpr (std::convertible_to<T, std::wstring>)
		{
			return static_cast<std::wstring>(property);
		}
		else
		{
			return std::to_wstring(static_cast<const T&>(property));
		}
	}
}

export template<typename T, typename Context, bool Custom, bool Copyable, bool Readonly, bool Nothrow>
struct std::formatter<iconer::util::IProperty<T, Context, Custom, Copyable, Readonly, Nothrow>, char>
{
	using property_t = iconer::util::IProperty<T, Context, Custom, Copyable, Readonly, Nothrow>;

	static constexpr format_parse_context::iterator
		parse(format_parse_context& context)
		noexcept
	{
		auto it = context.begin();
		const auto end = context.end();
		if (it == end or *it != '{')
		{
			throw std::format_error{ "Invalid format string." };
		}

		++it;
		if (it != end and *it != '}')
		{
			throw std::format_error{ "Missing '}' in format string." };
		}

		return it;
	}

	static format_context::iterator
		format(const property_t& property, format_context& context)
		noexcept
	{
		static auto&& meta = typeid(T);

		if constexpr (Readonly)
		{
			return format_to(context.out(), "ReadonlyProperty<{}>({})", meta.name(), to_string(property));
		}
		else
		{
			if constexpr (Custom)
			{
				return format_to(context.out(), "CustomProperty<{}>({})", meta.name(), to_string(property));
			}
			else
			{
				return format_to(context.out(), "Property<{}>({})", meta.name(), to_string(property));
			}
		}
	}

	static format_context::iterator
		format(property_t&& property, format_context& context)
		noexcept
	{
		static auto&& meta = typeid(T);

		if constexpr (Readonly)
		{
			return format_to(context.out(), "ReadonlyProperty<{}>({})", meta.name(), to_string(std::move(property)));
		}
		else
		{
			if constexpr (Custom)
			{
				return format_to(context.out(), "CustomProperty<{}>({})", meta.name(), to_string(std::move(property)));
			}
			else
			{
				return format_to(context.out(), "Property<{}>({})", meta.name(), to_string(std::move(property)));
			}
		}
	}
};

export template<typename T, typename Context, bool Custom, bool Copyable, bool Readonly, bool Nothrow>
struct std::formatter<iconer::util::IProperty<T, Context, Custom, Copyable, Readonly, Nothrow>, wchar_t>
{
	using property_t = iconer::util::IProperty<T, Context, Custom, Copyable, Readonly, Nothrow>;

	static constexpr wformat_parse_context::iterator
		parse(wformat_parse_context& context)
		noexcept
	{
		auto it = context.begin();
		const auto end = context.end();
		if (it == end or *it != L'{')
		{
			throw std::format_error{ "Invalid format string." };
		}

		++it;
		if (it == end or *it != L'}')
		{
			throw std::format_error{ "Missing '}' in format string." };
		}

		return it;
	}

	static wformat_context::iterator
		format(const property_t& property, wformat_context& context)
		noexcept
	{
		static auto&& meta = typeid(T);

		if constexpr (Readonly)
		{
			return format_to(context.out(), L"ReadonlyProperty<{}>({})", meta.name(), to_wstring(property));
		}
		else
		{
			if constexpr (Custom)
			{
				return format_to(context.out(), L"CustomProperty<{}>({})", meta.name(), to_wstring(property));
			}
			else
			{
				return format_to(context.out(), L"Property<{}>({})", meta.name(), to_wstring(property));
			}
		}
	}

	static wformat_context::iterator
		format(property_t&& property, wformat_context& context)
		noexcept
	{
		static auto&& meta = typeid(T);

		if constexpr (Readonly)
		{
			return format_to(context.out(), L"ReadonlyProperty<{}>({})", meta.name(), to_string(std::move(property)));
		}
		else
		{
			if constexpr (Custom)
			{
				return format_to(context.out(), L"CustomProperty<{}>({})", meta.name(), to_string(std::move(property)));
			}
			else
			{
				return format_to(context.out(), L"Property<{}>({})", meta.name(), to_string(std::move(property)));
			}
		}
	}
};
