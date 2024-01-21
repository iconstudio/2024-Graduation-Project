module;
#include <thread>
module Iconer.Coroutine.ConcurrentAwaiter;

void
net::coroutine::ConcurrentAwaiter::await_suspend(std::coroutine_handle<void> prev_handle)
{
	std::thread([prev_handle] {
		prev_handle();
	}).detach();
}
