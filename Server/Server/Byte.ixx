export module Iconer.Utility.Byte;
import <type_traits>;
import <concepts>;
export import <bit>;

static inline constexpr unsigned char LastByte = 0XFFU;

export namespace iconer::util
{
	[[nodiscard]]
	constexpr bool MakeSigned(bool value) noexcept
	{
		return value;
	}
	
	[[nodiscard]]
	constexpr bool MakeUnsigned(bool value) noexcept
	{
		return value;
	}
	
	template <typename T>
	[[nodiscard]]
	constexpr auto MakeSigned(T&& value) noexcept
	{
		return static_cast<std::make_signed_t<std::remove_cvref_t<T>>>(std::forward<T>(value));
	}
	
	template <typename T>
	[[nodiscard]]
	constexpr auto MakeUnsigned(T&& value) noexcept
	{
		return static_cast<std::make_unsigned_t<std::remove_cvref_t<T>>>(std::forward<T>(value));
	}

	template <std::integral T>
	[[nodiscard]]
	constexpr unsigned char RShift(const T& value, const size_t& times) noexcept
	{
		return static_cast<unsigned char>(value >> (times * 8ULL)) & LastByte;
	}
}

export namespace iconer::os
{
	using std::endian;

	[[nodiscard]]
	consteval bool IsBigEndian() noexcept
	{
		return std::endian::native == std::endian::big;
	}

	[[nodiscard]]
	consteval bool IsLittleEndian() noexcept
	{
		return std::endian::native == std::endian::little;
	}

	[[nodiscard]]
	consteval bool IsMixedEndian() noexcept
	{
		return std::endian::native != std::endian::big and std::endian::native != std::endian::little;
	}

	[[nodiscard]]
	constexpr decltype(auto) ToNetworkByteOrder(const std::integral auto& value) noexcept
	{
		if constexpr (IsLittleEndian())
		{
			return std::byteswap(value);
		}
		else
		{
			return value;
		}
	}

	[[nodiscard]]
	constexpr decltype(auto) ToNetworkByteOrder(std::integral auto&& value) noexcept
	{
		if constexpr (IsLittleEndian())
		{
			return std::byteswap(value);
		}
		else
		{
			return std::move(value);
		}
	}

	[[nodiscard]]
	constexpr decltype(auto) ToSystemByteOrder(const std::integral auto& value) noexcept
	{
		if constexpr (IsLittleEndian())
		{
			return std::byteswap(value);
		}
		else
		{
			return value;
		}
	}

	[[nodiscard]]
	constexpr decltype(auto) ToSystemByteOrder(std::integral auto&& value) noexcept
	{
		if constexpr (IsLittleEndian())
		{
			return std::byteswap(value);
		}
		else
		{
			return std::move(value);
		}
	}
}
