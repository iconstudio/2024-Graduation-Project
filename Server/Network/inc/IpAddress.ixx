export module Net.IpAddress;
import <string_view>;
import <format>;
import <memory>;
export import :IpAddressFamily;

export namespace net
{
	struct alignas(char) [[nodiscard]] SerializedIpAddress
	{
		constexpr SerializedIpAddress() noexcept = default;
		constexpr ~SerializedIpAddress() noexcept = default;

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
			return static_cast<IpAddressFamily&&>(addressFamily);
		}

		[[nodiscard]]
		constexpr std::string_view GetAddressString() const noexcept
		{
			return addressBuffer.get();
		}

		[[nodiscard]]
		constexpr bool operator==(const IpAddress&) const noexcept = default;

		constexpr IpAddress(IpAddress&&) noexcept = default;
		constexpr IpAddress& operator=(IpAddress&&) noexcept = default;

		IpAddressFamily addressFamily;
		std::unique_ptr<char[]> addressBuffer;
	};
}

export template<> struct std::formatter<net::IpAddress>
{
	std::format_parse_context::iterator parse(std::format_parse_context& context) const;

	std::format_context::iterator format(const net::IpAddress& ip, std::format_context& context) const noexcept;
};

export namespace std
{
	[[nodiscard]]
	std::string to_string(const net::IpAddress& ip) noexcept
	{
		return std::format("{}", ip);
	}
}
