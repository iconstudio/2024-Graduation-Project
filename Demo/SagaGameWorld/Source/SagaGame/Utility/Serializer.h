#pragma once
#include "CoreMinimal.h"
#include <type_traits>
#include <bit>
#include <memory>
#include <tuple>
#include <string_view>

template <typename... Ts>
concept CEnumerations = std::conjunction_v<std::is_enum<Ts>...>;

static uint8 Byte = 0XFFU;

template <typename T>
[[nodiscard]] constexpr int8 RShift(const T &Value, const size_t &Times) noexcept
{
	return static_cast<int8>(static_cast<uint8>(Value >> (Times * 8ULL)) & Byte);
}

struct SAGAGAME_API FSerializer
{
	/// <summary>Transfer a boolean value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const bool &value)
	{
		dest[0] = std::bit_cast<uint8>(value);
		return dest + 1;
	}

	/// <summary>Allocate a byte buffer for a boolean value</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const bool &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(bool));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer a character to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const int8 &value)
	{
		dest[0] = std::bit_cast<uint8>(value);
		return dest + 1;
	}

	/// <summary>Allocate a byte buffer for a character</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const int8 &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(int8));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer an unsigned character to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const uint8 &value)
	{
		dest[0] = std::bit_cast<uint8>(value);
		return dest + 1;
	}

	/// <summary>Allocate a byte buffer for an unsigned character</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const uint8 &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(uint8));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer an utf-8 character to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const char8_t &value)
	{
		dest[0] = std::bit_cast<uint8>(value);
		return dest + 1;
	}

	/// <summary>Allocate a byte buffer for an utf-8 character</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const char8_t &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(char8_t));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer a 16-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const int16 &value)
	{
		const auto longer = static_cast<int32>(value);
		dest[0] = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1] = std::bit_cast<uint8>(RShift(longer, 1));

		return dest + 2;
	}

	/// <summary>Allocate a byte buffer for a 16-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const int16 &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(int16));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer an unsigned 16-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const uint16 &value)
	{
		const auto longer = static_cast<uint32>(value);
		dest[0] = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1] = std::bit_cast<uint8>(RShift(longer, 1));

		return dest + 2;
	}

	/// <summary>Allocate a byte buffer for an unsigned 16-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const uint16 &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(uint16));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer an utf-16 character to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const char16_t &value)
	{
		const auto longer = static_cast<uint32>(value);
		dest[0] = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1] = std::bit_cast<uint8>(RShift(longer, 1));

		return dest + 2;
	}

	/// <summary>Allocate a byte buffer for an utf-16 character</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const char16_t &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(char16_t));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer a wide character to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const wchar_t &value)
	{
		const auto longer = static_cast<uint32>(value);
		dest[0] = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1] = std::bit_cast<uint8>(RShift(longer, 1));

		return dest + 2;
	}

	/// <summary>Allocate a byte buffer for a wide character</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const wchar_t &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(wchar_t));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer a 32-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const int32 &value)
	{
		const auto longer = static_cast<int64>(value);
		dest[0] = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1] = std::bit_cast<uint8>(RShift(longer, 1));
		dest[2] = std::bit_cast<uint8>(RShift(longer, 2));
		dest[3] = std::bit_cast<uint8>(RShift(longer, 3));

		return dest + 4;
	}

	/// <summary>Allocate a byte buffer for a 32-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const int32 &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(int32));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer an unsigned 32-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const uint32 &value)
	{
		const auto longer = static_cast<uint64>(value);
		dest[0] = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1] = std::bit_cast<uint8>(RShift(longer, 1));
		dest[2] = std::bit_cast<uint8>(RShift(longer, 2));
		dest[3] = std::bit_cast<uint8>(RShift(longer, 3));

		return dest + 4;
	}

	/// <summary>Allocate a byte buffer for  an unsigned 32-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const uint32 &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(uint32));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer a 32-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const long &value)
	{
		const auto longer = static_cast<int64>(value);
		dest[0] = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1] = std::bit_cast<uint8>(RShift(longer, 1));
		dest[2] = std::bit_cast<uint8>(RShift(longer, 2));
		dest[3] = std::bit_cast<uint8>(RShift(longer, 3));

		return dest + 4;
	}

	/// <summary>Allocate a byte buffer for a 32-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const long &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(long));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer an unsigned 32-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const unsigned long &value)
	{
		const auto longer = static_cast<uint64>(value);
		dest[0] = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1] = std::bit_cast<uint8>(RShift(longer, 1));
		dest[2] = std::bit_cast<uint8>(RShift(longer, 2));
		dest[3] = std::bit_cast<uint8>(RShift(longer, 3));

		return dest + 4;
	}

	/// <summary>Allocate a byte buffer for an unsigned 32-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const unsigned long &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(unsigned long));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer an utf-32 character to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const char32_t &value)
	{
		const auto longer = static_cast<uint64>(value);
		dest[0] = std::bit_cast<uint8>(RShift(longer, 0));
		dest[1] = std::bit_cast<uint8>(RShift(longer, 1));
		dest[2] = std::bit_cast<uint8>(RShift(longer, 2));
		dest[3] = std::bit_cast<uint8>(RShift(longer, 3));

		return dest + 4;
	}

	/// <summary>Allocate a byte buffer for an utf-32 character</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const char32_t &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(char32_t));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer a 64-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const int64 &value)
	{
		uint8 *it = dest;
		for (size_t i = 0; i < 8; ++i)
		{
			*(it++) = std::bit_cast<uint8>(RShift(value, i));
		}

		return it;
	}

	/// <summary>Allocate a byte buffer for a 64-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const int64 &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(int64));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer an unsigned 64-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const uint64 &value)
	{
		uint8 *it = dest;
		for (size_t i = 0; i < 8; ++i)
		{
			*(it++) = std::bit_cast<uint8>(RShift(value, i));
		}

		return it;
	}

	/// <summary>Allocate a byte buffer for an unsigned 64-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const uint64 &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(uint64));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer a 32-bit floating point value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const std::float_t &value)
	{
		return Serialize(dest, std::bit_cast<int32>(value));
	}

	/// <summary>Allocate a byte buffer for a 32-bit floating point value</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const std::float_t &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(int32));
		Serialize(buffer.Get(), std::bit_cast<int32>(value));
		return buffer;
	}

	/// <summary>Transfer a 32-bit floating point value to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const std::double_t &value)
	{
		return Serialize(dest, std::bit_cast<int64>(value));
	}

	/// <summary>Allocate a byte buffer for a 64-bit floating point value</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const std::double_t &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(int64));
		Serialize(buffer.Get(), std::bit_cast<int64>(value));
		return buffer;
	}

	/// <summary>Transfer a string to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const std::string_view str)
	{
		return std::ranges::transform(str.cbegin(), str.cend(), dest, [](const int8 &ch) noexcept
									  { return std::bit_cast<uint8>(ch); })
			.out;
	}

	/// <summary>Allocate a byte buffer for a string</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const std::string_view str)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(int8) * str.length());
		Serialize(buffer.Get(), str);
		return buffer;
	}

	/// <summary>Transfer a wide string to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const std::wstring_view str)
	{
		std::ranges::for_each(str, [&dest](const wchar_t &ch) noexcept
							  { dest = Serialize(dest, ch); });

		return dest;
	}

	/// <summary>Allocate a byte buffer for a wide string</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const std::wstring_view str)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(wchar_t) * str.length());
		Serialize(buffer.Get(), str);
		return buffer;
	}

	/// <summary>Transfer an utf-8 string to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const std::u8string_view str)
	{
		return std::ranges::transform(str.cbegin(), str.cend(), dest, [](const char8_t &ch) noexcept
									  { return std::bit_cast<uint8>(ch); })
			.out;
	}

	/// <summary>Allocate a byte buffer for an utf-8 string</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const std::u8string_view str)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(char8_t) * str.length());
		Serialize(buffer.Get(), str);
		return buffer;
	}

	/// <summary>Transfer a wide string to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const std::u16string_view str)
	{
		std::ranges::for_each(str, [&dest](const char16_t &ch) noexcept
							  { dest = Serialize(dest, ch); });

		return dest;
	}

	/// <summary>Allocate a byte buffer for a string</summary>
	/// <exception cref="std::bad_alloc"/>
	static TUniquePtr<uint8[]> Serialize(const std::u16string_view str)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(char16_t) * str.length());
		Serialize(buffer.Get(), str);
		return buffer;
	}

	/// <summary>Transfer a wide string to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	static uint8 *Serialize(uint8 *dest, const std::u32string_view str)
	{
		std::ranges::for_each(str, [&dest](const char32_t &ch) noexcept
							  { dest = Serialize(dest, ch); });

		return dest;
	}

	/// <summary>Allocate a byte buffer for a enumeration</summary>
	/// <exception cref="std::bad_alloc"/>
	template <CEnumerations T>
	static TUniquePtr<uint8[]> Serialize(const T &value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(value));
		Serialize(buffer.Get(), static_cast<std::underlying_type_t<T>>(value));
		return buffer;
	}

	/// <summary>Transfer a enumeration to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	template <CEnumerations T>
	static uint8 *Serialize(uint8 *dest, const T &value)
	{
		return Serialize(dest, static_cast<std::underlying_type_t<T>>(value));
	}

private:
	// summarize byte size of each type in a sequence
	template <typename...>
	struct byte_size;

	template <typename... Ts>
	static inline constexpr size_t byte_size_v = byte_size<Ts...>::value;

	template <typename T>
	struct byte_size<T> : public std::integral_constant<size_t, sizeof(T)>
	{
	};

	template <typename T, typename... Rests>
	struct byte_size<T, Rests...> : public std::integral_constant<size_t, sizeof(T) + byte_size_v<Rests...>>
	{
	};

	template <typename Tuple, size_t... Indices>
	static uint8 *_SerializeTuple(uint8 *dest, Tuple &&tuple, std::index_sequence<Indices...>)
	{
		uint8 *it = dest;

		((it = Serialize(it, std::get<Indices>(std::forward<Tuple>(tuple)))), ...);

		return it;
	}

public:
	/// <summary>Allocate a byte buffer for a copied tuple</summary>
	/// <exception cref="std::bad_alloc"/>
	template <typename... Args>
	static TUniquePtr<uint8[]> Serialize(const std::tuple<Args...> &tuple)
	{
		auto buffer = MakeUnique<uint8[]>(byte_size_v<Args...>);
		Serialize(buffer.Get(), tuple);
		return buffer;
	}

	/// <summary>Transfer a copied tuple to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	template <typename... Args>
	static uint8 *Serialize(uint8 *dest, const std::tuple<Args...> &tuple)
	{
		if constexpr (0 < sizeof...(Args))
		{
			return _SerializeTuple(dest, tuple, std::index_sequence_for<Args...>{});
		}
		else
		{
			return dest;
		}
	}

	/// <summary>Allocate a byte buffer for a moved tuple</summary>
	/// <exception cref="std::bad_alloc"/>
	template <typename... Args>
	static TUniquePtr<uint8[]> Serialize(std::tuple<Args...> &&tuple)
	{
		auto buffer = MakeUnique<uint8[]>(byte_size_v<Args...>);
		Serialize(buffer.Get(), MoveTempIfPossible(tuple));
		return buffer;
	}

	/// <summary>Transfer a moved tuple to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	template <typename... Args>
	static uint8 *Serialize(uint8 *dest, std::tuple<Args...> &&tuple)
	{
		if constexpr (0 < sizeof...(Args))
		{
			return _SerializeTuple(dest, MoveTempIfPossible(tuple), std::index_sequence_for<Args...>{});
		}
		else
		{
			return dest;
		}
	}

	/// <summary>Allocate a byte buffer of multiple values</summary>
	/// <exception cref="std::bad_alloc"/>
	template <typename... Args>
		requires(1 < sizeof...(Args))
	static TUniquePtr<uint8[]> Serializes(Args &&...args)
	{
		return Serialize(std::forward_as_tuple(Forward<Args>(args)...));
	}

	/// <summary>Transfer arguments to the byte buffer</summary>
	/// <returns>last buffer pointer foregoing from dest</returns>
	template <typename... Args>
		requires(1 < sizeof...(Args))
	static uint8 *Serializes(uint8 *dest, Args &&...args)
	{
		return _SerializeTuple(dest, std::forward_as_tuple(Forward<Args>(args)...));
	}
};
