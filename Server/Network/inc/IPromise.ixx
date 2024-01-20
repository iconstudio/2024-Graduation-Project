export module Net.Coroutine.IPromise;
import Net.Constraints;
import Net.Coroutine.Suspender;
import Net.Coroutine.Awaitable;
import <coroutine>;

export namespace net::coroutine
{
	template<Suspender Init = std::suspend_always, Suspender Final = std::suspend_always>
	class [[nodiscard]] IPromise
	{
	public:
		using type = IPromise<Init, Final>;
		using handle_type = std::coroutine_handle<type>;

		constexpr IPromise() noexcept = default;
		virtual constexpr ~IPromise() noexcept = default;

		[[nodiscard]]
		static constexpr std::decay_t<Init> initial_suspend() noexcept
		{
			return {};
		}

		[[nodiscard]]
		static constexpr std::decay_t<Final> final_suspend() noexcept
		{
			return {};
		}

		[[noreturn]]
		virtual void unhandled_exception()
		{
			throw;
		}
	};
}
