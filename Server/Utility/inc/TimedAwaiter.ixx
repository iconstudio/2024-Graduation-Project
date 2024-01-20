export module Net.Coroutine:TimedAwaiter;
import <coroutine>;

export namespace net::coroutine
{
	struct [[nodiscard]] WaitForSeconds final
	{
		static constexpr bool await_ready() noexcept
		{
			return false;
		}
		void await_suspend(std::coroutine_handle<void> previous_frame);
		static constexpr void await_resume() noexcept
		{}

		float myTime;
	};

	struct [[nodiscard]] WaitForMilliseconds final
	{
		static constexpr bool await_ready() noexcept
		{
			return false;
		}
		void await_suspend(std::coroutine_handle<void> previous_frame) const;
		static constexpr void await_resume() noexcept
		{}

		float myTime;
	};

	struct [[nodiscard]] WaitForMinutes final
	{
	public:
		static constexpr bool await_ready() noexcept
		{
			return false;
		}
		void await_suspend(std::coroutine_handle<void> previous_frame) const;
		static constexpr void await_resume() noexcept
		{}

		float myTime;
	};
}
