export module  Net.Coroutine:BasicPromise;
import Net.Coroutine.Awaitable;
export import <coroutine>;

export namespace net::coroutine
{
	template<typename Co, Awaitable Init, Awaitable Final, typename R = void>
	struct BasicPromise;

	template<typename Co, Awaitable Init, Awaitable Final>
	struct BasicPromise<Co, Init, Final, void>
	{
		[[nodiscard]]
		Co get_return_object() noexcept
		{
			return Co(std::coroutine_handle<BasicPromise>::from_promise(*this));
		}

		static constexpr void return_void() noexcept
		{}

		static constexpr Init initial_suspend() noexcept
		{
			return {};
		}

		static constexpr Final final_suspend() noexcept
		{
			return {};
		}

		[[noreturn]]
		static void unhandled_exception()
		{
			throw;
		}
	};
}
