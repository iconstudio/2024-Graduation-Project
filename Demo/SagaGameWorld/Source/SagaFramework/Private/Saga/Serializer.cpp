#include "Saga/Serializer.h"

uint8*
FSagaSerializer::Serialize(uint8* dest, const bool& value)
{
	dest[0] = std::bit_cast<uint8>(value);
	return dest + 1;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const bool& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(bool));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const char& value)
{
	dest[0] = std::bit_cast<uint8>(value);
	return dest + 1;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const char& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(char));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const char8_t& value)
{
	dest[0] = std::bit_cast<uint8>(value);
	return dest + 1;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const char8_t& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(char8_t));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const uint16& value)
{
	const auto longer = static_cast<uint32>(value);
	dest[0] = std::bit_cast<uint8>(saga::RShift(longer, 0));
	dest[1] = std::bit_cast<uint8>(saga::RShift(longer, 1));

	return dest + 2;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const uint16& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(uint16));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const char16_t& value)
{
	const auto longer = static_cast<uint32>(value);
	dest[0] = std::bit_cast<uint8>(saga::RShift(longer, 0));
	dest[1] = std::bit_cast<uint8>(saga::RShift(longer, 1));

	return dest + 2;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const char16_t& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(char16_t));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const wchar_t& value)
{
	const auto longer = static_cast<uint32>(value);
	dest[0] = std::bit_cast<uint8>(saga::RShift(longer, 0));
	dest[1] = std::bit_cast<uint8>(saga::RShift(longer, 1));

	return dest + 2;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const wchar_t& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(wchar_t));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const int32& value)
{
	const auto longer = static_cast<int64>(value);
	dest[0] = std::bit_cast<uint8>(saga::RShift(longer, 0));
	dest[1] = std::bit_cast<uint8>(saga::RShift(longer, 1));
	dest[2] = std::bit_cast<uint8>(saga::RShift(longer, 2));
	dest[3] = std::bit_cast<uint8>(saga::RShift(longer, 3));

	return dest + 4;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const int32& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(int32));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const uint32& value)
{
	const auto longer = static_cast<uint64>(value);
	dest[0] = std::bit_cast<uint8>(saga::RShift(longer, 0));
	dest[1] = std::bit_cast<uint8>(saga::RShift(longer, 1));
	dest[2] = std::bit_cast<uint8>(saga::RShift(longer, 2));
	dest[3] = std::bit_cast<uint8>(saga::RShift(longer, 3));

	return dest + 4;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const uint32& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(uint32));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const long& value)
{
	const auto longer = static_cast<int64>(value);
	dest[0] = std::bit_cast<uint8>(saga::RShift(longer, 0));
	dest[1] = std::bit_cast<uint8>(saga::RShift(longer, 1));
	dest[2] = std::bit_cast<uint8>(saga::RShift(longer, 2));
	dest[3] = std::bit_cast<uint8>(saga::RShift(longer, 3));

	return dest + 4;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const long& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(long));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const unsigned long& value)
{
	const auto longer = static_cast<uint64>(value);
	dest[0] = std::bit_cast<uint8>(saga::RShift(longer, 0));
	dest[1] = std::bit_cast<uint8>(saga::RShift(longer, 1));
	dest[2] = std::bit_cast<uint8>(saga::RShift(longer, 2));
	dest[3] = std::bit_cast<uint8>(saga::RShift(longer, 3));

	return dest + 4;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const unsigned long& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(unsigned long));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const char32_t& value)
{
	const auto longer = static_cast<uint64>(value);
	dest[0] = std::bit_cast<uint8>(saga::RShift(longer, 0));
	dest[1] = std::bit_cast<uint8>(saga::RShift(longer, 1));
	dest[2] = std::bit_cast<uint8>(saga::RShift(longer, 2));
	dest[3] = std::bit_cast<uint8>(saga::RShift(longer, 3));

	return dest + 4;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const char32_t& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(char32_t));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const int64& value)
{
	uint8* it = dest;
	for (size_t i = 0; i < 8; ++i)
	{
		*(it++) = std::bit_cast<uint8>(saga::RShift(value, i));
	}

	return it;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const int64& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(int64));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const uint64& value)
{
	uint8* it = dest;
	for (size_t i = 0; i < 8; ++i)
	{
		*(it++) = std::bit_cast<uint8>(saga::RShift(value, i));
	}

	return it;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const uint64& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(uint64));
	Serialize(buffer.Get(), value);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const float_t& value)
{
	return Serialize(dest, std::bit_cast<int32>(value));
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const float_t& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(int32));
	Serialize(buffer.Get(), std::bit_cast<int32>(value));
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const double_t& value)
{
	return Serialize(dest, std::bit_cast<int64>(value));
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const double_t& value)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(int64));
	Serialize(buffer.Get(), std::bit_cast<int64>(value));
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const std::string_view str)
{
	return std::ranges::transform(str.cbegin(), str.cend(), dest
		, [](const char& ch) noexcept {
			return std::bit_cast<uint8>(ch);
		}).out;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const std::string_view str)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(char) * str.length());
	Serialize(buffer.Get(), str);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const std::wstring_view str)
{
	std::ranges::for_each(str, [&dest](const wchar_t& ch) {
		dest = Serialize(dest, ch);
		});

	return dest;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const std::wstring_view str)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(wchar_t) * str.length());
	Serialize(buffer.Get(), str);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const std::u8string_view str)
{
	return std::ranges::transform(str.cbegin(), str.cend(), dest
		, [](const char8_t& ch) {
			return std::bit_cast<uint8>(ch);
		}).out;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const std::u8string_view str)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(char8_t) * str.length());
	Serialize(buffer.Get(), str);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const std::u16string_view str)
{
	std::ranges::for_each(str, [&dest](const char16_t& ch) {
		dest = Serialize(dest, ch);
		});

	return dest;
}

TUniquePtr<uint8[]>
FSagaSerializer::Serialize(const std::u16string_view str)
{
	auto buffer = MakeUnique<uint8[]>(sizeof(char16_t) * str.length());
	Serialize(buffer.Get(), str);
	return buffer;
}

uint8*
FSagaSerializer::Serialize(uint8* dest, const std::u32string_view str)
{
	std::ranges::for_each(str, [&dest](const char32_t& ch) {
		dest = Serialize(dest, ch);
		});

	return dest;
}

const uint8*
FSagaSerializer::Deserialize(const uint8* buffer, size_t length, std::string& output)
{
	output.reserve(length);

	for (auto it = buffer; it < buffer + length; ++it)
	{
		output.push_back(std::bit_cast<char>(*it));
	}

	return buffer + length;
}

#ifdef __cpp_lib_char8_t
const uint8*
FSagaSerializer::Deserialize(const uint8* buffer, size_t length, std::u8string& output)
{
	output.reserve(length);

	const uint8* it = buffer;
	while (it < buffer + length * sizeof(char8_t))
	{
		output.push_back(std::bit_cast<char>(*it));
		++it;
	}

	return it;
}
#endif // __cpp_lib_char8_t

const uint8*
FSagaSerializer::Deserialize(const uint8* buffer, size_t length, std::wstring& output)
{
	output.reserve(length);

	const uint8* it = buffer;
	while (it < buffer + length * sizeof(wchar_t))
	{
		wchar_t ch{};

		it = Deserialize(it, ch);

		output.push_back(ch);
	}

	return it;
}

const uint8*
FSagaSerializer::Deserialize(const uint8* buffer, size_t length, std::u16string& output)
{
	output.reserve(length);

	const uint8* it = buffer;
	while (it < buffer + length * sizeof(char16_t))
	{
		char16_t ch{};

		it = Deserialize(it, ch);

		output.push_back(ch);
	}

	return it;
}

const uint8*
FSagaSerializer::Deserialize(const uint8* buffer, size_t length, std::u32string& output)
{
	output.reserve(length);

	const uint8* it = buffer;
	while (it < buffer + length * sizeof(char32_t))
	{
		char32_t ch{};

		it = Deserialize(it, ch);

		output.push_back(ch);
	}

	return it;
}
