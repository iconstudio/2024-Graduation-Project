module;
#include <vector>
#include <memory>
#include <optional>

export module Net.Scheduler;
import Net.BorrowedPointer;
export import :Schedule;
export import Net.Coroutine;

export namespace net::coroutine
{
	class [[nodiscard]] Scheduler
	{
	protected:
		struct [[nodiscard]] Initiator final
		{
			Initiator(Scheduler& scheduler, bool would_block) noexcept;
			~Initiator() noexcept = default;

			bool await_ready() const noexcept;
			void await_suspend(std::coroutine_handle<void> handle);
			/// <summary>
			/// Retrieves how successfully this task is queued on the scheduler.
			/// </summary>
			/// <returns>Whether it has been scheduled or not</returns>
			std::optional<BorrowedPointer<Schedule>> await_resume() const noexcept;

			friend class coroutine::Schedule;

		private:
			Scheduler& myScheduler;
			Schedule* myStarter;
			bool isSucceed;
			bool wouldBlock;
		};

		std::vector<std::unique_ptr<Schedule>> mySchedules;

	public:
		Scheduler();
		Scheduler(size_t pipelines);

		[[nodiscard]] Initiator Start(bool would_block);

		friend class coroutine::Schedule;
	};
}

export namespace net
{
	using coroutine::Scheduler;
}

