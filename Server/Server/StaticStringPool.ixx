export module Iconer.Utility.StaticStringPool;
export import Iconer.Collection.FixedString;
import <type_traits>;

export namespace iconer::util
{
	template<typename Char, size_t Index>
	struct BasicStaticStringPool
	{};

	template<iconer::collection::basic_fixed_string FixedString>
	struct StaticStringView
	{
		using char_type = typename decltype(FixedString)::value_type;
	};

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
	inline constexpr iconer::collection::basic_fixed_string BasicStaticString = BasicStaticStringPool<Char, Index>::template value;
	
	template<size_t Index>
	inline constexpr iconer::collection::fixed_string StaticString = BasicStaticStringPool<char, Index>;

	template<size_t Index>
	inline constexpr iconer::collection::fixed_u8string StaticUtf8String = BasicStaticStringPool<char8_t, Index>;

	template<size_t Index>
	inline constexpr iconer::collection::fixed_wstring StaticWideString = BasicStaticStringPool<wchar_t, Index>;

	template<size_t Index>
	inline constexpr iconer::collection::fixed_u16string StaticUtf16String = BasicStaticStringPool<char16_t, Index>;

	template<size_t Index>
	inline constexpr iconer::collection::fixed_u32string StaticUtf32String = BasicStaticStringPool<char32_t, Index>;

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
