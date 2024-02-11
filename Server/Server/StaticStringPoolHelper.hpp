#pragma once

#define StoreStaticString(index, character, string) template<>\
struct iconer::util::BasicStaticStringPool<character, 0>\
{\
	static inline constexpr auto value = std::basic_string_view{ string };\
}

#define LoadStaticString(index, character) iconer::util::BasicStaticString<character, index>
