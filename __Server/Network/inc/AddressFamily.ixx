export module Net.IpAddress:AddressFamily;
import <string>;
import <format>;

export namespace iconer::net
{
	enum class [[nodiscard]] IpAddressFamily
	{
		Unknown, IPv4 = 2, IPv6 = 23
	};
}

export namespace std
{
	[[nodiscard]]
	constexpr std::string to_string(const iconer::net::IpAddressFamily& fm) noexcept
	{
		switch (fm)
		{
			case iconer::net::IpAddressFamily::IPv4:
			{
				return "IPv4";
			}

			case iconer::net::IpAddressFamily::IPv6:
			{
				return "IPv6";
			}

			default:
			{
				return "Unknown";
			}
		}
	}

	[[nodiscard]]
	constexpr std::wstring to_wstring(const iconer::net::IpAddressFamily& fm) noexcept
	{
		switch (fm)
		{
			case iconer::net::IpAddressFamily::IPv4:
			{
				return L"IPv4";
			}

			case iconer::net::IpAddressFamily::IPv6:
			{
				return L"IPv6";
			}

			default:
			{
				return L"Unknown";
			}
		}
	}
}

export template<>
struct std::formatter<iconer::net::IpAddressFamily, char>
{
	std::format_parse_context::iterator
		parse(std::format_parse_context& context)
		noexcept;

	std::format_context::iterator
		format(const iconer::net::IpAddressFamily& fm, std::format_context& context)
		const noexcept;

private:
	bool isSimplified = false;   // e, E
	bool isStrengthened = false; // g, G
	bool isUpperCase = false;    // U
};

export template<>
struct std::formatter<iconer::net::IpAddressFamily, wchar_t>
{
	std::wformat_parse_context::iterator
		parse(std::wformat_parse_context& context)
		noexcept;

	std::wformat_context::iterator
		format(const iconer::net::IpAddressFamily& fm, std::wformat_context& context)
		const noexcept;

private:
	bool isSimplified = false;   // e, E
	bool isStrengthened = false; // g, G
	bool isUpperCase = false;    // U
};
