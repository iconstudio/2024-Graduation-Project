export module Net.IoService;
import Iconer.Utility.Handler;
import Net.Io.Entity;
import Net.Io.Context;
import <vector>;
import <thread>;

export namespace net::io
{
	class [[nodiscard]] Service
	{
	private:
		class Scheduler : public Handler<std::jthread>
		{
		public:
		};

		class Schedule
		{
		public:
		};

	public:
		Service() noexcept = default;
		~Service() noexcept = default;

		std::vector<Entity> ioContexts;
		std::vector<Scheduler> myThreads;
	};
}
