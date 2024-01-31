#pragma once
#include "CoreMinimal.h"
#include <type_traits>
#include <bit>
#include <string_view>
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Serializer.generated.h"

template <typename... Ts>
concept CEnumerations = std::conjunction_v<std::is_enum<Ts>...>;

static constexpr uint8 Byte = 0XFFU;

template <typename T>
[[nodiscard]]
constexpr int8 RShift(const T& Value, const size_t& Times) noexcept
{
	return static_cast<int8>(static_cast<uint8>(Value >> (Times * 8ULL)) & Byte);
}

UCLASS()
class SAGAGAME_API USerializer : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/// <summary>Transfer a boolean value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const bool& value)
	{
		dest[0] = value;
		return dest + 1;
	}

	/// <summary>Allocate a byte buffer for a boolean value</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const bool& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(bool));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer a character to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const int8& value)
	{
		dest[0] = std::bit_cast<uint8>(value);
		return dest + 1;
	}

	/// <summary>Allocate a byte buffer for a character</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const int8& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(int8));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer an unsigned character to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const uint8& value)
	{
		dest[0] = std::bit_cast<uint8>(value);
		return dest + 1;
	}

	/// <summary>Allocate a byte buffer for an unsigned character</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const uint8& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(uint8));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer an utf-8 character to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const char8_t& value)
	{
		dest[0] = std::bit_cast<uint8>(value);
		return dest + 1;
	}

	/// <summary>Allocate a byte buffer for an utf-8 character</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const char8_t& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(char8_t));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer a 16-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const int16& value)
	{
		const auto longer = static_cast<int32>(value);
		dest[0]           = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1]           = std::bit_cast<uint8>(RShift(longer, 1));

		return dest + 2;
	}

	/// <summary>Allocate a byte buffer for a 16-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const int16& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(int16));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer an unsigned 16-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const uint16& value)
	{
		const auto longer = static_cast<uint32>(value);
		dest[0]           = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1]           = std::bit_cast<uint8>(RShift(longer, 1));

		return dest + 2;
	}

	/// <summary>Allocate a byte buffer for an unsigned 16-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const uint16& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(uint16));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer an utf-16 character to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const char16_t& value)
	{
		const auto longer = static_cast<uint32>(value);
		dest[0]           = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1]           = std::bit_cast<uint8>(RShift(longer, 1));

		return dest + 2;
	}

	/// <summary>Allocate a byte buffer for an utf-16 character</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const char16_t& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(char16_t));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer a wide character to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const wchar_t& value)
	{
		const auto longer = static_cast<uint32>(value);
		dest[0]           = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1]           = std::bit_cast<uint8>(RShift(longer, 1));

		return dest + 2;
	}

	/// <summary>Allocate a byte buffer for a wide character</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const wchar_t& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(wchar_t));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer a 32-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const int32& value)
	{
		const auto longer = static_cast<int64>(value);
		dest[0]           = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1]           = std::bit_cast<uint8>(RShift(longer, 1));
		dest[2]           = std::bit_cast<uint8>(RShift(longer, 2));
		dest[3]           = std::bit_cast<uint8>(RShift(longer, 3));

		return dest + 4;
	}

	/// <summary>Allocate a byte buffer for a 32-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const int32& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(int32));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer an unsigned 32-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const uint32& value)
	{
		const auto longer = static_cast<uint64>(value);
		dest[0]           = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1]           = std::bit_cast<uint8>(RShift(longer, 1));
		dest[2]           = std::bit_cast<uint8>(RShift(longer, 2));
		dest[3]           = std::bit_cast<uint8>(RShift(longer, 3));

		return dest + 4;
	}

	/// <summary>Allocate a byte buffer for  an unsigned 32-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const uint32& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(uint32));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer a 32-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const long& value)
	{
		const auto longer = static_cast<int64>(value);
		dest[0]           = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1]           = std::bit_cast<uint8>(RShift(longer, 1));
		dest[2]           = std::bit_cast<uint8>(RShift(longer, 2));
		dest[3]           = std::bit_cast<uint8>(RShift(longer, 3));

		return dest + 4;
	}

	/// <summary>Allocate a byte buffer for a 32-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const long& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(long));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer an unsigned 32-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const unsigned long& value)
	{
		const auto longer = static_cast<uint64>(value);
		dest[0]           = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1]           = std::bit_cast<uint8>(RShift(longer, 1));
		dest[2]           = std::bit_cast<uint8>(RShift(longer, 2));
		dest[3]           = std::bit_cast<uint8>(RShift(longer, 3));

		return dest + 4;
	}

	/// <summary>Allocate a byte buffer for an unsigned 32-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const unsigned long& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(unsigned long));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer an utf-32 character to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const char32_t& value)
	{
		const auto longer = static_cast<uint64>(value);
		dest[0]           = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1]           = std::bit_cast<uint8>(RShift(longer, 1));
		dest[2]           = std::bit_cast<uint8>(RShift(longer, 2));
		dest[3]           = std::bit_cast<uint8>(RShift(longer, 3));

		return dest + 4;
	}

	/// <summary>Allocate a byte buffer for an utf-32 character</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const char32_t& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(char32_t));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer a 64-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const int64& value)
	{
		uint8* it = dest;
		for (size_t i = 0; i < 8; ++i)
		{
			*(it++) = std::bit_cast<uint8>(RShift(value, i));
		}

		return it;
	}

	/// <summary>Allocate a byte buffer for a 64-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const int64& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(int64));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer an unsigned 64-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const uint64& value)
	{
		uint8* it = dest;
		for (size_t i = 0; i < 8; ++i)
		{
			*(it++) = std::bit_cast<uint8>(RShift(value, i));
		}

		return it;
	}

	/// <summary>Allocate a byte buffer for an unsigned 64-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const uint64& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(uint64));
		Serialize(buffer.get(), value);
		return buffer;
	}

	/// <summary>Transfer a 32-bit floating point value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const std::float_t& value)
	{
		return Serialize(dest, std::bit_cast<int32>(value));
	}

	/// <summary>Allocate a byte buffer for a 32-bit floating point value</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const std::float_t& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(int32));
		Serialize(buffer.get(), std::bit_cast<int32>(value));
		return buffer;
	}

	/// <summary>Transfer a 32-bit floating point value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const std::double_t& value)
	{
		return Serialize(dest, std::bit_cast<int64>(value));
	}

	/// <summary>Allocate a byte buffer for a 64-bit floating point value</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const std::double_t& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(int64));
		Serialize(buffer.get(), std::bit_cast<int64>(value));
		return buffer;
	}

	/// <summary>Transfer a string to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const std::string_view str)
	{
		return std::ranges::transform(str.cbegin(), str.cend(), dest, [](const int8& ch) noexcept {
			return std::bit_cast<uint8>(ch);
		}).out;
	}

	/// <summary>Allocate a byte buffer for a string</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const std::string_view str)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(int8) * str.length());
		Serialize(buffer.get(), str);
		return buffer;
	}

	/// <summary>Transfer a wide string to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const std::wstring_view str)
	{
		std::ranges::for_each(str, [&dest](const wchar_t& ch) noexcept {
			dest = Serialize(dest, ch);
		});

		return dest;
	}

	/// <summary>Allocate a byte buffer for a wide string</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const std::wstring_view str)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(wchar_t) * str.length());
		Serialize(buffer.get(), str);
		return buffer;
	}

	/// <summary>Transfer an utf-8 string to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const std::u8string_view str)
	{
		return std::ranges::transform(str.cbegin(), str.cend(), dest, [](const char8_t& ch) noexcept {
			return std::bit_cast<uint8>(ch);
		}).out;
	}

	/// <summary>Allocate a byte buffer for an utf-8 string</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const std::u8string_view str)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(char8_t) * str.length());
		Serialize(buffer.get(), str);
		return buffer;
	}

	/// <summary>Transfer a wide string to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const std::u16string_view str)
	{
		std::ranges::for_each(str, [&dest](const char16_t& ch) noexcept {
			dest = Serialize(dest, ch);
		});

		return dest;
	}

	/// <summary>Allocate a byte buffer for a string</summary>
	/// <exception cref="std::bad_alloc"/>
	static constexpr std::unique_ptr<uint8[]> Serialize(const std::u16string_view str)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(char16_t) * str.length());
		Serialize(buffer.get(), str);
		return buffer;
	}

	/// <summary>Transfer a wide string to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static constexpr uint8* Serialize(uint8* dest, const std::u32string_view str)
	{
		std::ranges::for_each(str, [&dest](const char32_t& ch) noexcept {
			dest = Serialize(dest, ch);
		});

		return dest;
	}

	/// <summary>Allocate a byte buffer for a enumeration</summary>
	/// <exception cref="std::bad_alloc"/>
	template <CEnumerations T>
	static constexpr std::unique_ptr<uint8[]> Serialize(const T& value)
	{
		auto buffer = std::make_unique<uint8[]>(sizeof(value));
		Serialize(buffer.get(), static_cast<std::underlying_type_t<T>>(value));
		return buffer;
	}

	/// <summary>Transfer a enumeration to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	template <CEnumerations T>
	static constexpr uint8* Serialize(uint8* dest, const T& value)
	{
		return Serialize(dest, static_cast<std::underlying_type_t<T>>(value));
	}
};
