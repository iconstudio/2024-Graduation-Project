export module Iconer.Coroutine;
export import :TimedAwaiter;
export import :BasicCoroutine;
import :BasicPromise;
import <utility>;
import <atomic>;
export import <coroutine>;

export namespace iconer::coroutine
{
	using std::suspend_never;
	using std::suspend_always;
	using std::coroutine_handle;

	class Coroutine
		: public BasicCoroutine<Coroutine, BasicPromise<Coroutine, suspend_always, suspend_always, void>>
	{
	public:
		using handle_type = BasicCoroutine::handle_type;

		constexpr Coroutine(const handle_type& handle) noexcept
			: BasicCoroutine(handle)
			, isTriggered(), triggerHandle()
		{}

		constexpr Coroutine(handle_type&& handle) noexcept
			: BasicCoroutine(static_cast<handle_type&&>(handle))
			, isTriggered(), triggerHandle()
		{}

		virtual ~Coroutine();

		void Start() const;
		void StartAsync() const;
		void Resume() const;
		void operator()() const;

		[[nodiscard]]
		bool IsTriggered() const noexcept
		{
			return isTriggered.load(std::memory_order_relaxed);
		}

		Coroutine(Coroutine&& other) noexcept
			: BasicCoroutine(std::move(std::exchange(other.GetHandle(), nullptr)))
			, isTriggered(other.IsTriggered()), triggerHandle(std::move(other.triggerHandle))
		{}

		Coroutine& operator=(Coroutine&& other) noexcept
		{
			myHandle = std::move(std::exchange(other.GetHandle(), nullptr));
			isTriggered = other.IsTriggered();
			triggerHandle = std::move(other.triggerHandle);
			return *this;
		}

		[[nodiscard]]
		constexpr bool operator==(const Coroutine&) const noexcept = default;

	private:
		Coroutine(const Coroutine&) = delete;
		Coroutine& operator=(const Coroutine&) = delete;

		mutable volatile std::atomic_bool isTriggered;
		void* triggerHandle;
	};

	class Action final
		: public BasicCoroutine<Action, BasicPromise<Action, suspend_never, suspend_always, void>>
	{
	public:
		using handle_type = BasicCoroutine::handle_type;

		constexpr Action(const handle_type& handle) noexcept
			: BasicCoroutine(handle)
		{}

		constexpr Action(handle_type&& handle) noexcept
			: BasicCoroutine(static_cast<handle_type&&>(handle))
		{}

		void Resume() const;
		void operator()() const;

		[[nodiscard]]
		constexpr bool operator==(const Action&) const noexcept = default;

	private:
		Action(const Action&) = delete;
		Action(Action&&) = delete;
		Action& operator=(const Action&) = delete;
		Action& operator=(Action&&) = delete;
	};
}

export namespace net
{
	using Coroutine = coroutine::Coroutine;
	using CoAction = coroutine::Action;
}
