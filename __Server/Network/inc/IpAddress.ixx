export module Net.IpAddress;
export import :AddressFamily;
import <string>;
import <string_view>;
import <format>;
import <memory>;

export namespace iconer::net
{
	struct [[nodiscard]] SerializedIpAddress
	{
		char data[64];
	};

	class [[nodiscard]] IpAddress final
	{
	public:
		IpAddress(const IpAddressFamily& family, std::string_view address);
		IpAddress(const IpAddress& other);
		IpAddress& operator=(const IpAddress& other);

		[[nodiscard]]
		SerializedIpAddress Serialize() const noexcept;
		bool TrySerialize(SerializedIpAddress& out) const noexcept;
		bool TrySerialize(void* const& out) const noexcept;

		[[nodiscard]]
		constexpr const IpAddressFamily& GetFamily() const& noexcept
		{
			return addressFamily;
		}

		[[nodiscard]]
		constexpr IpAddressFamily&& GetFamily() && noexcept
		{
			return std::move(addressFamily);
		}

		[[nodiscard]]
		constexpr const std::string& GetAddressString() const& noexcept
		{
			return addressString;
		}

		[[nodiscard]]
		constexpr std::string&& GetAddressString() && noexcept
		{
			return std::move(addressString);
		}

		[[nodiscard]]
		constexpr bool operator==(const IpAddress&) const noexcept = default;

		constexpr IpAddress(const IpAddress&) noexcept = default;
		constexpr IpAddress& operator=(const IpAddress&) noexcept = default;
		constexpr IpAddress(IpAddress&&) noexcept = default;
		constexpr IpAddress& operator=(IpAddress&&) noexcept = default;

		IpAddressFamily addressFamily;
		std::string addressString;
	};
}

export template<>
struct std::formatter<iconer::net::IpAddress, char>
{
	static std::format_parse_context::iterator
		parse(std::format_parse_context& context);

	static std::format_context::iterator
		format(const iconer::net::IpAddress& ip, std::format_context& context)
		noexcept;
};

export template<>
struct std::formatter<iconer::net::IpAddress, wchar_t>
{
	static std::wformat_parse_context::iterator
		parse(std::wformat_parse_context& context);

	static std::wformat_context::iterator
		format(const iconer::net::IpAddress& ip, std::wformat_context& context)
		noexcept;
};

export namespace std
{
	[[nodiscard]]
	std::string to_string(const iconer::net::IpAddress& ip) noexcept
	{
		return std::format("{}", ip);
	}
}
