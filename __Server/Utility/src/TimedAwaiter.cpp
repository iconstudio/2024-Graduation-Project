module;
#include <Windows.h>
#include <chrono>
#include <thread>

module Iconer.Coroutine;
import :TimedAwaiter;

void
net::coroutine::WaitForSeconds::await_suspend(std::coroutine_handle<void> previous_frame)
{
	::Sleep(static_cast<DWORD>(myTime * 1000));
	previous_frame();
}

void
net::coroutine::WaitForMilliseconds::await_suspend(std::coroutine_handle<void> previous_frame)
const
{
	::Sleep(static_cast<DWORD>(myTime * 1000));
	previous_frame();
}

void
net::coroutine::WaitForMinutes::await_suspend(std::coroutine_handle<void> previous_frame)
const
{
	::Sleep(static_cast<DWORD>(myTime * 1000));
	previous_frame();
}
