export module Net.Coroutine.Awaitable;
import Iconer.Constraints;
import <coroutine>;

export namespace net
{
	template<typename T>
	concept Awaitable = requires(T object)
	{
		object.await_ready();
		{ object.await_ready() } -> convertible_to<bool>;
		object.await_suspend(std::declval<std::coroutine_handle<void>>());
		object.await_resume();
	};
}
