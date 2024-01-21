module;
#include <deque>
#include <atomic>
#include <thread>
#include <coroutine>
export module Net.Scheduler:Schedule;

export namespace net::coroutine
{
	class Scheduler;

	class [[nodiscard]] Schedule final
	{
	private:
		struct Task
		{
			std::coroutine_handle<void> coHandle;
			bool isBlocked;
		};

	public:
		Schedule(Scheduler& scheduler);
		~Schedule() noexcept = default;

		void AddTask(std::coroutine_handle<void> handle, bool would_block);
		[[nodiscard]] std::suspend_never Pause() noexcept;
		void Resume() noexcept;
		bool Stop() noexcept;

		[[nodiscard]] size_t NumberOfTasks() const noexcept;
		[[nodiscard]] bool IsBusy() const noexcept;

		Schedule(Schedule&&) noexcept = default;
		Schedule& operator=(Schedule&&) noexcept = default;

	private:
		void Lock() noexcept;
		bool TryLock() noexcept;
		void Unlock() noexcept;
		[[nodiscard]] bool IsLocked() const noexcept;

		Schedule(const Schedule&) = delete;
		void operator=(const Schedule&) = delete;

		std::jthread myWorker;
		std::deque<Task> myTasks;

		Scheduler* myParent;
		volatile std::atomic_bool isPaused;
		volatile std::atomic_bool isBusy;
		volatile std::atomic_bool isLocked;
	};
}
