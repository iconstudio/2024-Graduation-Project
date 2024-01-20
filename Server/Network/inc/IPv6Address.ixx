export module Net.IpAddress.IPv6;
export import Net.IpAddress;
import Net.Property;
import <string_view>;

export namespace net
{
	class [[nodiscard]] IPv6Address final
	{
	public:
		static ReadonlyProperty<IpAddress> Loopback;

		[[nodiscard]]
		static IpAddress Create(std::string_view address) noexcept
		{
			return IpAddress{ IpAddressFamily::IPv6, address };
		}

	private:
		constexpr IPv6Address() noexcept = default;
		constexpr ~IPv6Address() noexcept = default;
	};

	ReadonlyProperty<IpAddress> IPv6Address::Loopback = IPv6Address::Create(":::::1");
}
