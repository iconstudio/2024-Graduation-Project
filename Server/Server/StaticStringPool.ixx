export module Iconer.Utility.StaticStringPool;
export import Iconer.Collection.FixedString;
import <cstdint>;
import <span>;
import <string>;
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

	template<size_t Index>
	inline constexpr iconer::collection::fixed_string StaticString = StaticStringPool<Index>::template value;

	template<size_t Index>
	inline constexpr iconer::collection::fixed_u8string StaticUtf8String = StaticUtf8StringPool<Index>::template value;

	template<size_t Index>
	inline constexpr iconer::collection::fixed_wstring StaticWideString = StaticWideStringPool<Index>::template value;

	template<size_t Index>
	inline constexpr iconer::collection::fixed_u16string StaticUtf16String = StaticUtf16StringPool<Index>::template value;

	template<size_t Index>
	inline constexpr iconer::collection::fixed_u32string StaticUtf32String = StaticUtf32StringPool<Index>::template value;
}
