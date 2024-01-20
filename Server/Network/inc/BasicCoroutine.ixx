export module Net.Coroutine:BasicCoroutine;
import Net.Handler;
import <coroutine>;

export namespace net::coroutine
{
	template<typename Co, typename Promise>
	class BasicCoroutine : public Handler<std::coroutine_handle<Promise>>
	{
	public:
		using promise_type = Promise;
		using handle_type = std::coroutine_handle<promise_type>;
		using super = Handler<handle_type>;

		using super::super;
		using super::GetHandle;

		virtual ~BasicCoroutine() noexcept(noexcept(GetHandle().destroy()))
		{
			if (auto& handle = GetHandle(); handle)
			{
				handle.destroy();
			}
		}

		void Resume() const noexcept(noexcept(Co::Resume()))
		{
			Co::Resume();
		}

		void operator()() const noexcept(noexcept(Co::operator()()))
		{
			Co::operator()();
		}

		[[nodiscard]]
		bool IsAvailable() const noexcept
		{
			return GetHandle();
		}

		[[nodiscard]]
		bool IsDone() const noexcept
		{
			return GetHandle().done();
		}

		BasicCoroutine(BasicCoroutine&&) noexcept = default;
		BasicCoroutine& operator=(BasicCoroutine&&) noexcept = default;

		[[nodiscard]]
		constexpr bool operator==(const BasicCoroutine&) const noexcept = default;

	private:
		BasicCoroutine(const BasicCoroutine&) = delete;
		BasicCoroutine& operator=(const BasicCoroutine&) = delete;
	};
}
