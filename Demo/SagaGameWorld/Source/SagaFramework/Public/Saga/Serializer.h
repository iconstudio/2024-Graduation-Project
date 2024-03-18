#pragma once
#include "CoreMinimal.h"
#include "Saga/Constraints.h"
#include "Saga/Byte.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <bit>
#include <memory>
#include <tuple>
#include <string>
#include <string_view>
#include <utility>

class SAGAFRAMEWORK_API FSagaSerializer
{
public:
	/// <summary>Transfer a boolean value to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const bool& value);

	/// <summary>Allocate a byte buffer for a boolean value</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const bool& value);

	/// <summary>Transfer a character to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const char& value);

	/// <summary>Allocate a byte buffer for a character</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const char& value);

	/// <summary>Transfer an unsigned character to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const unsigned char& value)
	{
		dest[0] = std::bit_cast<uint8>(value);
		return dest + 1;
	}

	/// <summary>Allocate a byte buffer for an unsigned character</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const unsigned char& value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(unsigned char));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer an utf-8 character to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const char8_t& value);

	/// <summary>Allocate a byte buffer for an utf-8 character</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const char8_t& value);

	/// <summary>Transfer a 16-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const int16& value)
	{
		const auto longer = static_cast<int32>(value);
		dest[0] = std::bit_cast<uint8>(saga::RShift(longer, 0));
		dest[1] = std::bit_cast<uint8>(saga::RShift(longer, 1));

		return dest + 2;
	}

	/// <summary>Allocate a byte buffer for a 16-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const int16& value)
	{
		auto buffer = MakeUnique<uint8[]>(sizeof(int16));
		Serialize(buffer.Get(), value);
		return buffer;
	}

	/// <summary>Transfer an unsigned 16-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const uint16& value);

	/// <summary>Allocate a byte buffer for an unsigned 16-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const uint16& value);

	/// <summary>Transfer an utf-16 character to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const char16_t& value);

	/// <summary>Allocate a byte buffer for an utf-16 character</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const char16_t& value);

	/// <summary>Transfer a wide character to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const wchar_t& value);

	/// <summary>Allocate a byte buffer for a wide character</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const wchar_t& value);

	/// <summary>Transfer a 32-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const int32& value);

	/// <summary>Allocate a byte buffer for a 32-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const int32& value);

	/// <summary>Transfer an unsigned 32-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const uint32& value);

	/// <summary>Allocate a byte buffer for  an unsigned 32-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const uint32& value);

	/// <summary>Transfer a 32-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const long& value);

	/// <summary>Allocate a byte buffer for a 32-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const long& value);

	/// <summary>Transfer an unsigned 32-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const unsigned long& value);

	/// <summary>Allocate a byte buffer for an unsigned 32-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const unsigned long& value);

	/// <summary>Transfer an utf-32 character to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const char32_t& value);

	/// <summary>Allocate a byte buffer for an utf-32 character</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const char32_t& value);

	/// <summary>Transfer a 64-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const int64& value);

	/// <summary>Allocate a byte buffer for a 64-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const int64& value);

	/// <summary>Transfer an unsigned 64-bit integer value to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const uint64& value);

	/// <summary>Allocate a byte buffer for an unsigned 64-bit integer value</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const uint64& value);

	/// <summary>Transfer a 32-bit floating point value to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const float_t& value);

	/// <summary>Allocate a byte buffer for a 32-bit floating point value</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const float_t& value);

	/// <summary>Transfer a 32-bit floating point value to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const double_t& value);

	/// <summary>Allocate a byte buffer for a 64-bit floating point value</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const double_t& value);

	/// <summary>Transfer a string to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const std::string_view str);

	/// <summary>Allocate a byte buffer for a string</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const std::string_view str);

	/// <summary>Transfer a wide string to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const std::wstring_view str);

	/// <summary>Allocate a byte buffer for a wide string</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const std::wstring_view str);

	/// <summary>Transfer an utf-8 string to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const std::u8string_view str);

	/// <summary>Allocate a byte buffer for an utf-8 string</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const std::u8string_view str);

	/// <summary>Transfer a wide string to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const std::u16string_view str);

	/// <summary>Allocate a byte buffer for a string</summary>
	/// <exception cref="std::bad_alloc"/>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const std::u16string_view str);

	/// <summary>Transfer a wide string to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	static uint8* Serialize(uint8* dest, const std::u32string_view str);

	/// <summary>Allocate a byte buffer for a enumeration</summary>
	/// <exception cref="std::bad_alloc"/>
	template<saga::enumerations T>
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serialize(const T& value)
	{
		return Serialize(static_cast<std::underlying_type_t<T>>(value));
	}

	/// <summary>Transfer a enumeration to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	template<saga::enumerations T>
	static uint8* Serialize(uint8* dest, const T& value)
	{
		return Serialize(dest, static_cast<std::underlying_type_t<T>>(value));
	}

	/// <summary>Transfer a copied tuple to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	template<typename... Args>
	static uint8* Serialize(uint8* dest, const std::tuple<Args...>& tuple);

	/// <summary>Transfer a moved tuple to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	template<typename... Args>
	static uint8* Serialize(uint8* dest, std::tuple<Args...>&& tuple);

	/// <summary>Allocate a byte buffer of multiple values</summary>
	/// <exception cref="std::bad_alloc"/>
	template<typename... Args>
		requires (1 < sizeof...(Args))
	[[nodiscard]]
	static TUniquePtr<uint8[]> Serializes(Args&&... args);

	/// <summary>Transfer arguments to the byte buffer</summary>
	/// <returns>last buffer pointer after dest</returns>
	template<typename... Args>
		requires (0 < sizeof...(Args))
	static uint8* Serializes(uint8* dest, Args&&... args);

	/// <summary>Read a boolean value from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, bool& output)
	{
		output = std::bit_cast<bool>(buffer[0]);

		return buffer + 1;
	}

	/// <summary>Read a character from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, char& output)
	{
		output = std::bit_cast<char>(buffer[0]);

		return buffer + 1;
	}

	/// <summary>Read an unsigned character from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, unsigned char& output)
	{
		output = std::bit_cast<unsigned char>(buffer[0]);

		return buffer + 1;
	}

	/// <summary>Read an utf-8 character from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, char8_t& output)
	{
		output = std::bit_cast<char8_t>(buffer[0]);

		return buffer + 1;
	}

	/// <summary>Read a 16-bit integer value from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, int16& output)
	{
		const uint32 mid = (static_cast<uint32>(static_cast<uint8>(buffer[1])) << 8U)
			| static_cast<uint32>(static_cast<uint8>(buffer[0]));

		output = static_cast<int16>(mid);

		return buffer + 2;
	}

	/// <summary>Read an unsigned 16-bit integer value from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, uint16& output)
	{
		const uint32 mid = (static_cast<uint32>(static_cast<uint8>(buffer[1])) << 8U)
			| static_cast<uint32>(static_cast<uint8>(buffer[0]));

		output = static_cast<uint16>(mid);

		return buffer + 2;
	}

	/// <summary>Read a wide character from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, wchar_t& output)
	{
		const uint32 mid = (static_cast<uint32>(static_cast<uint8>(buffer[1])) << 8U)
			| static_cast<uint32>(static_cast<uint8>(buffer[0]));

		output = static_cast<wchar_t>(mid);

		return buffer + 2;
	}

	/// <summary>Read an utf-16 character from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, char16_t& output)
	{
		const uint32 mid = (static_cast<uint32>(static_cast<uint8>(buffer[1])) << 8U)
			| static_cast<uint32>(static_cast<uint8>(buffer[0]));

		output = static_cast<char16_t>(mid);

		return buffer + 2;
	}

	/// <summary>Read a 32-bit integer value from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, int32& output)
	{
		const uint64 mid = (static_cast<uint64>(static_cast<uint8>(buffer[3])) << 24U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[2])) << 16U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[1])) << 8U)
			| static_cast<uint64>(static_cast<uint8>(buffer[0]));

		output = static_cast<int32>(mid);

		return buffer + 4;
	}

	/// <summary>Read an unsigned 32-bit integer value from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, uint32& output)
	{
		const uint64 mid = (static_cast<uint64>(static_cast<uint8>(buffer[3])) << 24U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[2])) << 16U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[1])) << 8U)
			| static_cast<uint64>(static_cast<uint8>(buffer[0]));

		output = static_cast<uint32>(mid);

		return buffer + 4;
	}

	/// <summary>Read a 32-bit integer value from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, long& output)
	{
		const uint64 mid = (static_cast<uint64>(static_cast<uint8>(buffer[3])) << 24U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[2])) << 16U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[1])) << 8U)
			| static_cast<uint64>(static_cast<uint8>(buffer[0]));

		output = static_cast<long>(mid);

		return buffer + 4;
	}

	/// <summary>Read an unsigned 32-bit integer value from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, unsigned long& output)
	{
		const uint64 mid = (static_cast<uint64>(static_cast<uint8>(buffer[3])) << 24U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[2])) << 16U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[1])) << 8U)
			| static_cast<uint64>(static_cast<uint8>(buffer[0]));

		output = static_cast<unsigned long>(mid);

		return buffer + 4;
	}

	/// <summary>Read an utf-32 character from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, char32_t& output)
	{
		const uint64 mid = (static_cast<uint64>(static_cast<uint8>(buffer[3])) << 24U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[2])) << 16U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[1])) << 8U)
			| static_cast<uint64>(static_cast<uint8>(buffer[0]));

		output = static_cast<char32_t>(mid);

		return buffer + 4;
	}

	/// <summary>Read a 64-bit integer value from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, int64& output)
	{
		output = static_cast<int64>((static_cast<uint64>(static_cast<uint8>(buffer[7])) << 56U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[6])) << 48U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[5])) << 40U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[4])) << 32U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[3])) << 24U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[2])) << 16U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[1])) << 8U)
			| static_cast<uint64>(static_cast<uint8>(buffer[0])));

		return buffer + 8;
	}

	/// <summary>Read an unsigned 64-bit integer value from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, uint64& output)
	{
		output = (static_cast<uint64>(static_cast<uint8>(buffer[7])) << 56U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[6])) << 48U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[5])) << 40U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[4])) << 32U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[3])) << 24U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[2])) << 16U)
			| (static_cast<uint64>(static_cast<uint8>(buffer[1])) << 8U)
			| static_cast<uint64>(static_cast<uint8>(buffer[0]));

		return buffer + 8;
	}

	/// <summary>Read a 32-bit floating point value from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, float_t& output)
	{
		int32 mid{};
		auto it = Deserialize(buffer, mid);

		output = std::bit_cast<float_t>(mid);

		return it;
	}

	/// <summary>Read a 64-bit floating point value from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, double_t& output)
	{
		int64 mid{};
		auto it = Deserialize(buffer, mid);

		output = std::bit_cast<double_t>(mid);

		return it;
	}

	/// <summary>Read a string from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static const uint8* Deserialize(const uint8* buffer, size_t length, std::string& output);

#ifdef __cpp_lib_char8_t
	/// <summary>Read a utf-8 string from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static const uint8* Deserialize(const uint8* buffer, size_t length, std::u8string& output);
#endif // __cpp_lib_char8_t

	/// <summary>Read a wide string from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static const uint8* Deserialize(const uint8* buffer, size_t length, std::wstring& output);

	/// <summary>Read a utf-16 string from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static const uint8* Deserialize(const uint8* buffer, size_t length, std::u16string& output);

	/// <summary>Read a utf-32 string from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	static const uint8* Deserialize(const uint8* buffer, size_t length, std::u32string& output);

	/// <summary>Read a array from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	template<size_t Length>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, size_t length, char(&output)[Length])
	{
		const uint8* it = buffer;
		char* out = output;

		while (it < buffer + length * sizeof(char))
		{
			*out = std::bit_cast<char>(*it);

			++it; ++out;
		}

		return it;
	}

	/// <summary>Read a array from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	template<size_t Length>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, size_t length, char8_t(&output)[Length])
	{
		const uint8* it = buffer;
		char8_t* out = output;

		while (it < buffer + length * sizeof(char8_t))
		{
			*out = std::bit_cast<char8_t>(*it);

			++it; ++out;
		}

		return it;
	}

	/// <summary>Read a array from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	template<size_t Length>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, size_t length, wchar_t(&output)[Length])
	{
		const uint8* it = buffer;
		wchar_t* out = output;

		while (it < buffer + length * sizeof(wchar_t))
		{
			it = Deserialize(it, *out);

			++out;
		}

		return it;
	}

	/// <summary>Read a array from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	template<size_t Length>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, size_t length, char16_t(&output)[Length])
	{
		const uint8* it = buffer;
		char16_t* out = output;

		while (it < buffer + length * sizeof(char16_t))
		{
			it = Deserialize(it, *out);

			++out;
		}

		return it;
	}

	/// <summary>Read a array from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	template<size_t Length>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, size_t length, char32_t(&output)[Length])
	{
		const uint8* it = buffer;
		char32_t* out = output;

		while (it < buffer + length * sizeof(char32_t))
		{
			it = Deserialize(it, *out);

			++out;
		}

		return it;
	}

	/// <summary>Read a enumeration from the byte buffer</summary>
	/// <returns>last buffer pointer after read dest</returns>
	/// <exception cref="std::out_of_range"/>
	template<saga::enumerations T>
	static constexpr
		const uint8*
		Deserialize(const uint8* buffer, T& output)
	{
		std::underlying_type_t<T> result{};
		auto it = Deserialize(buffer, result);
		output = static_cast<T>(result);

		return it;
	}
};

namespace
{
	template<typename Arg>
	constexpr size_t GetItemByteSize(Arg&& arg) noexcept
	{
		if constexpr (std::is_same_v<saga::clean_t<Arg>, FString>)
		{
			return arg.Len() * sizeof(TCHAR);
		}
		else if constexpr (std::is_same_v<saga::clean_t<Arg>, FName>)
		{
			return arg.GetStringLength() * sizeof(TCHAR);
		}
		else if constexpr (std::is_same_v<saga::clean_t<Arg>, std::string>)
		{
			return arg.size();
		}
		else if constexpr (std::is_same_v<saga::clean_t<Arg>, std::wstring>)
		{
			return arg.size() * sizeof(wchar_t);
		}
		if constexpr (std::is_same_v<saga::clean_t<Arg>, std::string_view>)
		{
			return arg.size();
		}
		else if constexpr (std::is_same_v<saga::clean_t<Arg>, std::wstring_view>)
		{
			return arg.size() * sizeof(wchar_t);
		}
		else
		{
			return sizeof(Arg);
		}
	}

	template<typename Tuple, size_t... Indices>
	constexpr size_t GetByteSize(const Tuple& tuple, std::index_sequence<Indices...>) noexcept
	{
		size_t result{};

		((result += GetItemByteSize(std::get<Indices>(tuple))), ...);

		return result;
	}

	template<typename Tuple, size_t... Indices>
	uint8* SagaSerializeImpl(uint8* dest, Tuple&& tuple, std::index_sequence<Indices...>)
	{
		uint8* it = dest;

		((it = FSagaSerializer::Serialize(it, std::get<Indices>(std::forward<Tuple>(tuple)))), ...);

		return it;
	}

	template<typename ...Args>
	TUniquePtr<uint8[]>
		SagaSerializeImpl(const std::tuple<Args...>& tuple)
	{
		const size_t bfsize = GetByteSize(tuple, std::index_sequence_for<Args...>{});

		TUniquePtr<uint8[]> buffer = MakeUnique<uint8[]>(bfsize);
		Serialize(buffer.get(), tuple);
		return buffer;
	}

	template<typename ...Args>
	TUniquePtr<uint8[]>
		SagaSerializeImpl(std::tuple<Args...>&& tuple)
	{
		const size_t bfsize = GetByteSize(tuple, std::index_sequence_for<Args...>{});

		TUniquePtr<uint8[]> buffer = MakeUnique<uint8[]>(bfsize);
		FSagaSerializer::Serialize(buffer.Get(), std::move(tuple));
		return buffer;
	}
}

template<typename ...Args>
inline uint8* FSagaSerializer::Serialize(uint8* dest, const std::tuple<Args...>& tuple)
{
	if constexpr (0 < sizeof...(Args))
	{
		return SagaSerializeImpl(dest, tuple, std::index_sequence_for<Args...>{});
	}
	else
	{
		return dest;
	}
}

template<typename ...Args>
inline uint8* FSagaSerializer::Serialize(uint8* dest, std::tuple<Args...>&& tuple)
{
	if constexpr (0 < sizeof...(Args))
	{
		return SagaSerializeImpl(dest, std::move(tuple), std::index_sequence_for<Args...>{});
	}
	else
	{
		return dest;
	}
}

template<typename ...Args> requires (1 < sizeof...(Args))
	TUniquePtr<uint8[]>
	FSagaSerializer::Serializes(Args && ...args)
{
	return SagaSerializeImpl(std::forward_as_tuple(std::forward<Args>(args)...));
}

template<typename ...Args> requires (0 < sizeof...(Args))
	uint8*
	FSagaSerializer::Serializes(uint8* dest, Args && ...args)
{
	return SagaSerializeImpl(dest, std::forward_as_tuple(std::forward<Args>(args)...), std::index_sequence_for<Args...>{});
}
