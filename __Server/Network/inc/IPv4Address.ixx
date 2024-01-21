export module Net.IpAddress.IPv4;
export import Net.IpAddress;
import Net.Property;
import <string_view>;

export namespace net
{
	class [[nodiscard]] IPv4Address final
	{
	public:
		[[nodiscard]]
		static IpAddress Create(std::string_view address) noexcept
		{
			return IpAddress{ IpAddressFamily::IPv4, address };
		}

		static inline ReadonlyProperty<IpAddress> Loopback = Create("127.0.0.1");

	private:
		constexpr IPv4Address() noexcept = default;
		constexpr ~IPv4Address() noexcept = default;
	};
}
