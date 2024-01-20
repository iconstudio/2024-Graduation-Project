export module Net.IpAddress:IpAddressFamily;
import <string>;
import <format>;

export namespace net
{
	enum class [[nodiscard]] IpAddressFamily
	{
		Unknown, IPv4 = 2, IPv6 = 23
	};
}

export namespace std
{
	[[nodiscard]]
	constexpr std::string to_string(const net::IpAddressFamily& fm) noexcept
	{
		switch (fm)
		{
			case net::IpAddressFamily::IPv4:
			{
				return "IPv4";
			}

			case net::IpAddressFamily::IPv6:
			{
				return "IPv6";
			}

			default:
			{
				return "Unknown";
			}
		}
	}
}

export template<> struct std::formatter<net::IpAddressFamily>
{
	std::format_parse_context::iterator parse(std::format_parse_context& context) noexcept;

	std::format_context::iterator format(const net::IpAddressFamily& fm, std::format_context& context) const noexcept;

private:
	bool isSimplified = false;   // e, E
	bool isStrengthened = false; // g, G
	bool isUpperCase = false;    // U
};
