export module Net.Coroutine.Suspender;
import <concepts>;
import <coroutine>;

export namespace net::coroutine
{
	template<typename W>
	concept Suspender = requires(W object, std::coroutine_handle<void> handle)
	{
		{ object.await_ready() } -> std::convertible_to<bool>;
		{ object.await_suspend(handle) };
		{ object.await_resume() };
	};
}
