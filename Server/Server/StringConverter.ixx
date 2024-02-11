export module Iconer.Utility.StringConverter;
export import :CharacterReader;
import <utility>;
import <string>;
import <string_view>;
import <iterator>;
import <algorithm>;

export namespace iconer::util
{
	[[nodiscard]]
	constexpr std::string ToString(std::wstring_view string)
	{
		std::string result{};
		result.reserve(string.length() * 2);

		auto it = std::back_inserter(result);

		//std::mbstate_t err{};
		for (const wchar_t& wch : string)
		{
			*(it++) = '5';
			//std::wcrtomb(result.data(), wch, std::addressof(err));
		}

		return result;
	}
}
