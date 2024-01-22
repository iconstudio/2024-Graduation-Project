module;
#include <exception>
#include <thread>

module Iconer.Utility.Task;
import Iconer.Constraints;

net::Task<void>
net::Task<void>::promise_type::get_return_object() noexcept
{
	return Task<void>(handle_type::from_promise(*this));
}

net::Task<void>::~Task()
noexcept
{
	if (myHandle)
	{
		myHandle.destroy();
	}
}

void
net::Task<void>::Start()
const
{
	net::__ExecuteCoroutine(myHandle);
}

void
net::Task<void>::StartAsync()
const
{
	net::__ExecuteCoroutineAsync(myHandle);
}

void
net::Task<void>::operator()()
const
{
	net::__ExecuteCoroutine(myHandle);
}

net::Task<void>::Awaiter
net::Task<void>::operator co_await()
const noexcept
{
	return Awaiter{ .coHandle = myHandle };
}

bool
net::Task<void>::IsDone()
const noexcept
{
	return myHandle.done();
}

bool
net::Task<void>::operator==(const net::Task<void>& other)
const noexcept
{
	return myHandle.address() == other.myHandle.address();
}

void
net::__ExecuteCoroutine(std::coroutine_handle<void> handle)
{
	if (handle)
	{
		handle.resume();
	}
}

void net::__ExecuteCoroutineAsync(std::coroutine_handle<void> handle)
{
	if (handle)
	{
		std::thread{
			[h = std::move(handle)] {
			h.resume();
		} }.detach();
	}
}
