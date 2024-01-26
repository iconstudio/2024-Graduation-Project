module;
#include <string>
#include <string_view>
#include <format>
#include <bit>

export module Iconer.Utility.Serializer;
import Iconer.Utility.File;

export namespace iconer::util
{
	constexpr std::byte* Serialize(bool value)
	{
		//return new std::byte{ static_cast<std::uintptr_t>(value) };
		return nullptr;
	}

	constexpr std::byte* Serialize(std::byte* dest, bool value)
	{
		return dest;
	}
}
