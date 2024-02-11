export module Iconer.Utility.Byte;
import <type_traits>;
import <concepts>;
export import <bit>;

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
	auto&& ToNetworkByteOrder(const std::integral auto& value) noexcept
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
	auto&& ToNetworkByteOrder(std::integral auto&& value) noexcept
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
	auto&& ToSystemByteOrder(const std::integral auto& value) noexcept
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
	auto&& ToSystemByteOrder(std::integral auto&& value) noexcept
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
