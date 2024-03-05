#pragma once
#include "CoreMinimal.h"
#include <type_traits>
#include <bit>

#include "Deserializer.generated.h"

USTRUCT()
struct SAGAGAME_API FDeserializer
{
	GENERATED_BODY()

public:
	// Read a boolean value from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, bool& output)
	{
		output = static_cast<bool>(buffer[0]);

		return buffer + 1;
	}

	// Read a character from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, char& output)
	{
		output = std::bit_cast<char>(buffer[0]);

		return buffer + 1;
	}

	// Read an unsigned character from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, unsigned char& output)
	{
		output = std::bit_cast<unsigned char>(buffer[0]);

		return buffer + 1;
	}

	// Read an utf-8 character from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, char8_t& output)
	{
		output = std::bit_cast<char8_t>(buffer[0]);

		return buffer + 1;
	}

	// Read a 16-bit integer value from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, int16& output)
	{
		const uint32 mid = (static_cast<uint32>((buffer[1])) << 8U) | static_cast<uint32>((buffer[0]));

		output = static_cast<int16>(mid);

		return buffer + 2;
	}

	// Read an unsigned 16-bit integer value from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, uint16& output)
	{
		const uint32 mid = (static_cast<uint32>((buffer[1])) << 8U) | static_cast<uint32>((buffer[0]));

		output = static_cast<uint16>(mid);

		return buffer + 2;
	}

	// Read a wide character from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, wchar_t& output)
	{
		const uint32 mid = (static_cast<uint32>((buffer[1])) << 8U) | static_cast<uint32>((buffer[0]));

		output = static_cast<wchar_t>(mid);

		return buffer + 2;
	}

	// Read an utf-16 character from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, char16_t& output)
	{
		const uint32 mid = (static_cast<uint32>((buffer[1])) << 8U) | static_cast<uint32>((buffer[0]));

		output = static_cast<char16_t>(mid);

		return buffer + 2;
	}

	// Read a 32-bit integer value from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, int32& output)
	{
		const uint64 mid = (static_cast<uint64>((buffer[3])) << 24U) | (static_cast<uint64>((buffer[2])) << 16U) | (
							   static_cast<uint64>((buffer[1])) << 8U) | static_cast<uint64>((buffer[0]));

		output = static_cast<int32>(mid);

		return buffer + 4;
	}

	// Read an unsigned 32-bit integer value from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, uint32& output)
	{
		const uint64 mid = (static_cast<uint64>((buffer[3])) << 24U) | (static_cast<uint64>((buffer[2])) << 16U) | (
							   static_cast<uint64>((buffer[1])) << 8U) | static_cast<uint64>((buffer[0]));

		output = static_cast<uint32>(mid);

		return buffer + 4;
	}

	// Read a 32-bit integer value from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, long& output)
	{
		const uint64 mid = (static_cast<uint64>((buffer[3])) << 24U) | (static_cast<uint64>((buffer[2])) << 16U) | (
							   static_cast<uint64>((buffer[1])) << 8U) | static_cast<uint64>((buffer[0]));

		output = static_cast<long>(mid);

		return buffer + 4;
	}

	// Read an unsigned 32-bit integer value from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, unsigned long& output)
	{
		const uint64 mid = (static_cast<uint64>((buffer[3])) << 24U) | (static_cast<uint64>((buffer[2])) << 16U) | (
							   static_cast<uint64>((buffer[1])) << 8U) | static_cast<uint64>((buffer[0]));

		output = static_cast<unsigned long>(mid);

		return buffer + 4;
	}

	// Read an utf-32 character from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, char32_t& output)
	{
		const uint64 mid = (static_cast<uint64>((buffer[3])) << 24U) | (static_cast<uint64>((buffer[2])) << 16U) | (
							   static_cast<uint64>((buffer[1])) << 8U) | static_cast<uint64>((buffer[0]));

		output = static_cast<char32_t>(mid);

		return buffer + 4;
	}

	// Read a 64-bit integer value from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, std::int64_t& output)
	{
		output = static_cast<std::int64_t>((static_cast<uint64>((buffer[7])) << 56U) | (static_cast<uint64>((buffer[6])) << 48U) | (
											   static_cast<uint64>((buffer[5])) << 40U) | (static_cast<uint64>((buffer[4])) << 32U) | (
											   static_cast<uint64>((buffer[3])) << 24U) | (static_cast<uint64>((buffer[2])) << 16U) | (
											   static_cast<uint64>((buffer[1])) << 8U) | static_cast<uint64>((buffer[0])));

		return buffer + 8;
	}

	// Read an unsigned 64-bit integer value from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, uint64& output)
	{
		output = (static_cast<uint64>((buffer[7])) << 56U) | (static_cast<uint64>((buffer[6])) << 48U) | (
					 static_cast<uint64>((buffer[5])) << 40U) | (static_cast<uint64>((buffer[4])) << 32U) | (
					 static_cast<uint64>((buffer[3])) << 24U) | (static_cast<uint64>((buffer[2])) << 16U) | (
					 static_cast<uint64>((buffer[1])) << 8U) | static_cast<uint64>((buffer[0]));

		return buffer + 8;
	}

	// Read a 32-bit floating point value from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, std::float_t& output)
	{
		int32 mid{};
		auto it = Deserialize(buffer, mid);

		output = std::bit_cast<std::float_t>(mid);

		return it;
	}

	// Read a 64-bit floating point value from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, std::double_t& output)
	{
		std::int64_t mid{};
		auto it = Deserialize(buffer, mid);

		output = std::bit_cast<std::double_t>(mid);

		return it;
	}

	// Read a string from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, size_t length, std::string& output)
	{
		output.reserve(length);

		for (auto it = buffer; it < buffer + length; ++it)
		{
			output.push_back(std::bit_cast<char>(*it));
		}

		return buffer + length;
	}

	// Read a utf-8 string from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, size_t length, std::u8string& output)
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

	// Read a wide string from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, size_t length, std::wstring& output)
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

	// Read a utf-16 string from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, size_t length, std::u16string& output)
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

	// Read a utf-32 string from the byte buffer
	static constexpr const uint8* Deserialize(const uint8* buffer, size_t length, std::u32string& output)
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

	/// <summary>Read a array from the byte buffer</summary>
	/// <exception cref="std::out_of_range"/>
	template <size_t Length>
	static constexpr const uint8* Deserialize(const uint8* buffer, size_t length, char (&output)[Length])
	{
		const uint8* it = buffer;
		char* out       = output;

		while (it < buffer + length * sizeof(char))
		{
			*out = std::bit_cast<char>(*it);

			++it;
			++out;
		}

		return it;
	}

	/// <summary>Read a array from the byte buffer</summary>
	/// <exception cref="std::out_of_range"/>
	template <size_t Length>
	static constexpr const uint8* Deserialize(const uint8* buffer, size_t length, char8_t (&output)[Length])
	{
		const uint8* it = buffer;
		char8_t* out    = output;

		while (it < buffer + length * sizeof(char8_t))
		{
			*out = std::bit_cast<char8_t>(*it);

			++it;
			++out;
		}

		return it;
	}

	/// <summary>Read a array from the byte buffer</summary>
	/// <exception cref="std::out_of_range"/>
	template <size_t Length>
	static constexpr const uint8* Deserialize(const uint8* buffer, size_t length, wchar_t (&output)[Length])
	{
		const uint8* it = buffer;
		wchar_t* out    = output;

		while (it < buffer + length * sizeof(wchar_t))
		{
			it = Deserialize(it, *out);

			++out;
		}

		return it;
	}

	/// <summary>Read a array from the byte buffer</summary>
	/// <exception cref="std::out_of_range"/>
	template <size_t Length>
	static constexpr const uint8* Deserialize(const uint8* buffer, size_t length, char16_t (&output)[Length])
	{
		const uint8* it = buffer;
		char16_t* out   = output;

		while (it < buffer + length * sizeof(char16_t))
		{
			it = Deserialize(it, *out);

			++out;
		}

		return it;
	}

	/// <summary>Read a array from the byte buffer</summary>
	/// <exception cref="std::out_of_range"/>
	template <size_t Length>
	static constexpr const uint8* Deserialize(const uint8* buffer, size_t length, char32_t (&output)[Length])
	{
		const uint8* it = buffer;
		char32_t* out   = output;

		while (it < buffer + length * sizeof(char32_t))
		{
			it = Deserialize(it, *out);

			++out;
		}

		return it;
	}

	template <typename T> requires std::is_enum_v<T>
	/// <summary>Read a enumeration from the byte buffer</summary>
	/// <exception cref="std::out_of_range"/>
	static constexpr const uint8* Deserialize(const uint8* buffer, T& output)
	{
		std::underlying_type_t<T> result{};
		auto it = Deserialize(buffer, result);
		output  = static_cast<T>(result);

		return it;
	}
};
