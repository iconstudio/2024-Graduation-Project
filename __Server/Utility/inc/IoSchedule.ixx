export module Net.Io.Schedule;
import Net.NativeHandle;
import Net.Io.Event;
import Net.Io.Context;
import <stop_token>;

export namespace net::io
{
	class [[nodiscard]] Schedule final
	{
	public:
		Schedule(NativeHandle& io_handle, std::stop_token&& token) noexcept
			: ioHandle(io_handle), myCancelToken(std::move(token))
		{}

		[[nodiscard]] net::io::Event WaitForIoResult() noexcept;

		[[nodiscard]]
		bool IsCancelled() const noexcept
		{
			return myCancelToken.stop_requested();
		}

		constexpr bool operator==(const Schedule&) const noexcept = default;

	private:
		Schedule(const Schedule&) = delete;
		Schedule(Schedule&&) = delete;
		Schedule& operator=(const Schedule&) = delete;
		Schedule& operator=(Schedule&&) = delete;

		NativeHandle& ioHandle;
		std::stop_token myCancelToken;
	};
}
