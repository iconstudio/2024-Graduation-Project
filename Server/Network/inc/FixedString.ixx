export module Net.FixedString;
import <type_traits>;
import <compare>;
import <string_view>;

export namespace net
{
	template <typename Char, size_t N>
	struct [[nodiscard]] basic_fixed_string final
	{
		static_assert(std::is_trivially_copyable_v<Char>, "Char must be trivially copyable.");
		static_assert(std::is_standard_layout_v<Char>, "Char must be standard layout.");
		static_assert(std::is_integral_v<Char>, "Char must be an integral type.");
		static_assert(0 < N, "Fixed string must have at least one element.");

		constexpr basic_fixed_string() noexcept = default;
		constexpr ~basic_fixed_string() noexcept = default;

		constexpr basic_fixed_string(const Char* const& buffer) noexcept
			: intBuffer()
		{
			for (size_t i = 0; i < N; ++i)
			{
				const Char& elem = buffer[i];
				intBuffer[i] = elem;
			}
		}

		constexpr operator std::basic_string_view<Char>() const noexcept
		{
			return std::basic_string_view<Char>(intBuffer, N);
		}

		[[nodiscard]]
		constexpr bool operator==(const basic_fixed_string&) const noexcept = default;
		[[nodiscard]]
		constexpr std::strong_ordering operator<=>(const basic_fixed_string&) const noexcept = default;

	private:
		Char intBuffer[N];
	};

	template <typename Char, size_t N>
	basic_fixed_string(const Char(&str)[N]) -> basic_fixed_string<Char, N>;

	template <size_t N>
	using fixed_string = basic_fixed_string<char, N>;

	template <size_t N>
	using fixed_u8string = basic_fixed_string<char8_t, N>;

	template <size_t N>
	using fixed_u16string = basic_fixed_string<char16_t, N>;

	template <size_t N>
	using fixed_u32string = basic_fixed_string<char32_t, N>;

	template <size_t N>
	using fixed_wstring = basic_fixed_string<wchar_t, N>;
}
