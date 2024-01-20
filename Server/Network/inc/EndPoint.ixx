export module Net.EndPoint;
import <cstdint>;
import <type_traits>;
import <string_view>;
import Net.IpAddress;

export namespace net
{
	struct [[nodiscard]] EndPoint final
	{
	private:
		struct [[nodiscard]] EmptyEndPointType final
		{
			constexpr EmptyEndPointType() noexcept = default;
			constexpr ~EmptyEndPointType() noexcept = default;
		};

	public:
		static const EmptyEndPointType EmptyEndPoint;

		EndPoint(EmptyEndPointType) noexcept;
		EndPoint(const IpAddress& ip, const std::uint16_t& port) noexcept;
		EndPoint(IpAddress&& ip, const std::uint16_t& port) noexcept;
		~EndPoint() noexcept = default;

		[[nodiscard]]
		constexpr const IpAddressFamily& GetAddressFamily() const& noexcept
		{
			return myAddress.GetFamily();
		}
		[[nodiscard]]
		constexpr IpAddressFamily&& GetAddressFamily() && noexcept
		{
			return std::move(myAddress).GetFamily();
		}

		[[nodiscard]]
		constexpr const IpAddress& GetIpAddress() const& noexcept
		{
			return myAddress;
		}
		[[nodiscard]]
		constexpr IpAddress&& GetIpAddress() && noexcept
		{
			return std::move(myAddress);
		}

		[[nodiscard]]
		constexpr const std::uint16_t& GetPort() const& noexcept
		{
			return myPort;
		}
		[[nodiscard]]
		constexpr std::uint16_t&& GetPort() && noexcept
		{
			return std::move(myPort);
		}

		[[nodiscard]]
		std::string_view GetAddressString() const noexcept
		{
			return myAddress.GetAddressString();
		}

	private:
		IpAddress myAddress;
		std::uint16_t myPort;
	};
}
