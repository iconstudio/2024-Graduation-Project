export module Iconer.Utility.Handler;
import Iconer.Constraints;

export namespace iconer::util
{
	template<typename H>
	class [[nodiscard]] Handler
	{
	public:
		constexpr Handler()
			noexcept(nothrow_default_constructibles<H>) requires default_initializables<H> = default;
		constexpr ~Handler()
			noexcept(nothrow_destructibles<H>) = default;

		constexpr Handler(const H& handle) noexcept(nothrow_copy_constructibles<H>) requires copy_constructible<H>
			: myHandle(handle)
		{}

		constexpr Handler(H&& handle) noexcept(nothrow_move_constructibles<H>) requires move_constructible<H>
			: myHandle(static_cast<H&&>(handle))
		{}

		[[nodiscard]]
		constexpr H& GetHandle() & noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr volatile H& GetHandle() volatile& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr const H& GetHandle() const& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr const volatile H& GetHandle() const volatile& noexcept
		{
			return myHandle;
		}

		[[nodiscard]]
		constexpr H&& GetHandle() && noexcept
		{
			return static_cast<H&&>(myHandle);
		}

		[[nodiscard]]
		constexpr volatile H&& GetHandle() volatile&& noexcept
		{
			return static_cast<volatile H&&>(myHandle);
		}

		[[nodiscard]]
		constexpr bool operator==(const Handler&) const noexcept = default;

		constexpr Handler(const Handler&)
			noexcept(nothrow_copy_constructibles<H>) requires copy_constructible<H> = default;
		constexpr Handler(Handler&&)
			noexcept(nothrow_move_constructibles<H>) requires move_constructible<H> = default;
		constexpr Handler& operator=(const Handler&)
			noexcept(nothrow_copy_assignables<H>) requires copy_assignables<H> = default;
		constexpr Handler& operator=(Handler&&)
			noexcept(nothrow_move_assignables<H>) requires move_assignables<H> = default;

	protected:
		H myHandle;
	};
}
