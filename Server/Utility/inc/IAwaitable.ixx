export module Net.Coroutine.IAwaitable;
import <coroutine>;

export namespace net::coroutine
{
	template<typename R = void, typename H = std::coroutine_handle<void>>
	class IAwaitable
	{
	public:
		constexpr IAwaitable() noexcept = default;
		constexpr ~IAwaitable() noexcept = default;
		constexpr IAwaitable(const IAwaitable&) noexcept = default;
		constexpr IAwaitable(IAwaitable&&) noexcept = default;
		constexpr IAwaitable& operator=(const IAwaitable&) noexcept = default;
		constexpr IAwaitable& operator=(IAwaitable&&) noexcept = default;

		virtual constexpr bool await_ready() noexcept = 0;
		virtual void await_suspend(H handle) const = 0;
		virtual constexpr R await_resume() const = 0;
	};
}
