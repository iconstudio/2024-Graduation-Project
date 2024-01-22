export module Iconer.Coroutine.ConcurrentAwaiter;
import <coroutine>;

export namespace net::coroutine
{
	struct [[nodiscard]] ConcurrentAwaiter
	{
		static constexpr bool await_ready() noexcept
		{
			return false;
		}

		void await_suspend(std::coroutine_handle<void> prev_handle);

		static constexpr void await_resume() noexcept
		{}
	};
}
