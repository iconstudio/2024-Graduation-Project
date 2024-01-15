export module Iconer.NetworkView;
import Net.Constraints;
import <utility>;

export namespace demo
{
	template<net::crtp T>
	class [[nodiscard]] NetworkView
	{
	public:
		constexpr NetworkView() noexcept = default;
		constexpr ~NetworkView() noexcept = default;

#define REQUIRE_METHOD(name) requires { T::name(); }
#define NOTHROW_METHOD(name) (REQUIRE_METHOD(name) and noexcept(std::declval<T>().name())) or (not REQUIRE_METHOD(name))

		constexpr void OnNetworkIntialized()
			noexcept(NOTHROW_METHOD(name))
		{
			if constexpr (REQUIRE_METHOD(OnNetworkIntialized))
			{
				_Cast().OnNetworkIntialized();
			}
		}


		constexpr NetworkView(const NetworkView<T>&) noexcept = default;
		constexpr NetworkView(NetworkView<T>&&) noexcept = default;
		constexpr NetworkView& operator=(const NetworkView<T>&) noexcept = default;
		constexpr NetworkView& operator=(NetworkView<T>&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const NetworkView<T>&) const noexcept = default;

	protected:
		[[nodiscard]]
		T& _Cast() noexcept
		{
			return static_cast<T&>(*this);
		}

		[[nodiscard]]
		const T& _Cast() const noexcept
		{
			return static_cast<const T&>(*this);
		}

		[[nodiscard]]
		volatile T& _Cast() volatile noexcept
		{
			return static_cast<volatile T&>(*this);
		}

		[[nodiscard]]
		const volatile T& _Cast() const volatile noexcept
		{
			return static_cast<const volatile T&>(*this);
		}
	};
}
