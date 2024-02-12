export module Iconer.Utility.StaticStringPool;
import <type_traits>;
import <string_view>;

export namespace iconer::util
{
	template<typename Char, size_t Index>
	struct BasicStaticStringPool
	{};

	template<size_t Index>
	using StaticStringPool = BasicStaticStringPool<char, Index>;

	template<size_t Index>
	using StaticUtf8StringPool = BasicStaticStringPool<char8_t, Index>;

	template<size_t Index>
	using StaticWideStringPool = BasicStaticStringPool<wchar_t, Index>;

	template<size_t Index>
	using StaticUtf16StringPool = BasicStaticStringPool<char16_t, Index>;

	template<size_t Index>
	using StaticUtf32StringPool = BasicStaticStringPool<char32_t, Index>;

	template<typename Char, size_t Index>
	inline constexpr std::basic_string_view<Char> BasicStaticString = BasicStaticStringPool<Char, Index>::template value;
	
	template<size_t Index>
	[[nodiscard]]
	constexpr const std::string_view& StaticString() noexcept
	{
		return BasicStaticString<char, Index>;
	}

	template<size_t Index>
	[[nodiscard]]
	constexpr const std::u8string_view& StaticUtf8String() noexcept
	{
		return BasicStaticString<char8_t, Index>;
	}

	template<size_t Index>
	[[nodiscard]]
	constexpr const std::wstring_view& StaticWideString() noexcept
	{
		return BasicStaticString<wchar_t, Index>;
	}

	template<size_t Index>
	[[nodiscard]]
	constexpr const std::u16string_view& StaticUtf16String() noexcept
	{
		return BasicStaticString<char16_t, Index>;
	}

	template<size_t Index>
	[[nodiscard]]
	constexpr const std::u32string_view& StaticUtf32String() noexcept
	{
		return BasicStaticString<char32_t, Index>;
	}

	template<>
	struct BasicStaticStringPool<char, -1> {};
	template<>
	struct BasicStaticStringPool<char8_t, -1> {};
	template<>
	struct BasicStaticStringPool<wchar_t, -1> {};
	template<>
	struct BasicStaticStringPool<char16_t, -1> {};
	template<>
	struct BasicStaticStringPool<char32_t, -1> {};
}
