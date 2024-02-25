module;
#include <compare>
#include <chrono>
export module Iconer.Utility.Chronograph;

export namespace std::chrono
{
	using namespace ::std::chrono;
}

export namespace iconer::util
{
	template<typename ChronoClock>
	class BasicChronograph
	{
	public:
		using clock_t = ChronoClock;
		using rep = clock_t::rep;
		using period = clock_t::period;
		using duration = clock_t::duration;
		using time_point = clock_t::time_point;
		static constexpr bool is_steady = clock_t::is_steady;

		explicit BasicChronograph() noexcept
			: myTime(clock_t::now())
		{
		}

		[[nodiscard]]
		bool HasTimePassed(const duration& duration) const noexcept
		{
			return clock_t::now() + duration <= myTime;
		}

		[[nodiscard]]
		bool HasTimePassed(duration&& duration) const noexcept
		{
			return clock_t::now() + std::move(duration) <= myTime;
		}

		[[nodiscard]]
		constexpr bool HasReachedClock(const time_point& clock) const noexcept
		{
			return myTime <= clock;
		}

		[[nodiscard]]
		constexpr bool HasReachedClock(time_point&& clock) const noexcept
		{
			return std::move(clock).time_since_epoch() <= myTime.time_since_epoch();
		}

		constexpr bool operator==(const BasicChronograph&) const noexcept = default;
		constexpr std::strong_ordering operator<=>(const BasicChronograph&) const noexcept = default;

		time_point myTime;

	private:
	};

	using Chronograph = BasicChronograph<std::chrono::high_resolution_clock>;
	using SystemChronograph = BasicChronograph<std::chrono::system_clock>;
	using SteadyChronograph = BasicChronograph<std::chrono::steady_clock>;
	using FileChronograph = BasicChronograph<std::chrono::file_clock>;
	using GpsChronograph = BasicChronograph<std::chrono::gps_clock>;
	using UtcChronograph = BasicChronograph<std::chrono::utc_clock>;
	using TaiChronograph = BasicChronograph<std::chrono::tai_clock>;
}
