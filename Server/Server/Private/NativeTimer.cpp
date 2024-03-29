module;
#include <Windows.h>
#include <memory>
#include <unordered_map>
module Iconer.Application.NativeTimer;

namespace
{
	std::unordered_map<iconer::app::NativeTimer::IdType, std::unique_ptr<iconer::app::TimerProcedure>> timerProcs{};
}

iconer::app::NativeTimer::~NativeTimer()
noexcept
{
	(void)Stop();
}

bool
iconer::app::NativeTimer::Stop()
noexcept
{
	auto it = timerProcs.find(static_cast<iconer::app::NativeTimer::IdType>(myId));
	if (it != timerProcs.cend())
	{
		timerProcs.erase(it);
	}

	if (myHandle != 0 and not isStopped)
	{
		isStopped = true;
		return 0 != ::KillTimer(nullptr, std::exchange(myHandle, 0));
	}
	else
	{
		return isStopped;
	}
}

iconer::app::NativeTimer
iconer::app::StartTimer(iconer::app::NativeTimer::IdType id
	, const iconer::app::NativeTimerProcedure& proc
	, std::uint32_t milliseconds)
noexcept
{
	return NativeTimer{ id, ::SetTimer(nullptr, id, milliseconds, proc) };
}

iconer::app::NativeTimer
iconer::app::StartTimer(iconer::app::NativeTimer::IdType id
	, iconer::app::TimerProcedure&& proc)
noexcept
{
	timerProcs.insert({ id, std::make_unique<TimerProcedure>(std::move(proc)) });

	return StartTimer(id, ExecuteTimer, proc.myPeriod);
}

void
__stdcall
iconer::app::ExecuteTimer(::HWND, std::uint32_t, ::UINT_PTR timer_id, unsigned long sys_time)
{
	auto it = timerProcs.find(static_cast<iconer::app::NativeTimer::IdType>(timer_id));
	if (it != timerProcs.cend())
	{
		auto&& proc = *(it->second);

		proc();

		auto& timer = *proc.myTimer;
		if (proc.isLooping)
		{
			timer = NativeTimer{ timer.GetID(), ::SetTimer(nullptr, timer.GetID(), proc.myPeriod, ExecuteTimer) };
		}
		else
		{
			timer.Stop();
		}
	}
}
