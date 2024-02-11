#pragma once

#define StoreStaticString(index, string) template<>\
struct iconer::util::BasicStaticStringPool<std::remove_cvref_t<decltype(string[0])>, index>\
{\
	static inline constexpr auto value = std::basic_string_view{ string };\
}

#define LoadStaticString(index, character) iconer::util::BasicStaticString<character, index>
