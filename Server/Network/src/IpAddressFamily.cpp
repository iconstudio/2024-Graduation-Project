module Net.IpAddress;
import <string_view>;
import <utility>;
import <ranges>;
import :IpAddressFamily;

std::format_parse_context::iterator
std::formatter<net::IpAddressFamily>::parse(std::format_parse_context& context)
noexcept
{
	std::format_parse_context::iterator it = context.begin();
	for (; context.end() != it; ++it)
	{
		if (*it == '}') break;
		
		if (*it == 'U')
		{
			isUpperCase = true;
		}
		else if (*it == 'e')
		{
			isSimplified = true;
		}
		else if (*it == 'E')
		{
			isUpperCase = true;
			isSimplified = true;
		}
		else if (*it == 'g')
		{
			isStrengthened = true;
		}
		else if (*it == 'G')
		{
			isUpperCase = true;
			isStrengthened = true;
		}
	}

	return it;
}

std::format_context::iterator
std::formatter<net::IpAddressFamily>::format(const net::IpAddressFamily& fm, std::format_context& context)
const noexcept
{
	static auto myprint = [&]
	(std::string_view caption) noexcept {
		if (isUpperCase)
		{
			static constexpr auto myupper = []
			(const char& c) noexcept -> char { return c + 32; };

			using formatted_result = std::ranges::in_out_result<std::ranges::dangling, decltype(context.out())>;

			formatted_result it = std::ranges::copy(std::views::transform(caption, myupper), context.out());

			return it.out;
		}
		else
		{
			return std::format_to(context.out(), "{}", caption);
		}
	};

	switch (fm)
	{
		case net::IpAddressFamily::IPv4:
		{
			if (isStrengthened)
			{
				return myprint("Internet Protocol v4 Familiy");
			}
			else if (isSimplified)
			{
				return myprint("IPv4");
			}
			else
			{
				return myprint("IPv4 Familiy");
			}
		}

		case net::IpAddressFamily::IPv6:
		{
			if (isStrengthened)
			{
				return myprint("Internet Protocol v6 Familiy");
			}
			else if (isSimplified)
			{
				return myprint("IPv6");
			}
			else
			{
				return myprint("IPv6 Familiy");
			}
		}

		default:
		{
			if (isStrengthened)
			{
				return myprint("Unknown Internet Protocol Address Family");
			}
			else if (isSimplified)
			{
				return myprint("Unknown");
			}
			else
			{
				return myprint("Unknown Address Familiy");
			}
		}
	}
}
