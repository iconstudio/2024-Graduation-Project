module;
#include <WinSock2.h>

module Iconer.Net.Socket;
import <cstddef>;
import <utility>;
import <coroutine>;

using namespace iconer;

net::Socket::IoResult
net::Socket::Receive(std::span<std::byte> memory)
const noexcept
{
	if (int bytes = ::recv(myHandle
		, reinterpret_cast<char*>(memory.data()), static_cast<int>(memory.size_bytes())
		, 0); SOCKET_ERROR != bytes)
	{
		return bytes;
	}
	else
	{
		return std::unexpected{ AcquireNetworkError() };
	}
}

net::Socket::IoResult
net::Socket::Receive(std::span<std::byte> memory, size_t size)
const noexcept
{
	if (int bytes = ::recv(myHandle
		, reinterpret_cast<char*>(memory.data()), static_cast<int>(std::min(memory.size_bytes(), size))
		, 0); SOCKET_ERROR != bytes)
	{
		return bytes;
	}
	else
	{
		return std::unexpected{ AcquireNetworkError() };
	}
}

net::Socket::IoResult
net::Socket::Receive(std::byte* const& memory, size_t size)
const noexcept
{
	if (int bytes = ::recv(myHandle
		, reinterpret_cast<char*>(memory), static_cast<int>(size)
		, 0); SOCKET_ERROR != bytes)
	{
		return bytes;
	}
	else
	{
		return std::unexpected{ AcquireNetworkError() };
	}
}

bool
net::Socket::Receive(std::span<std::byte> memory, net::ErrorCode& error_code)
const noexcept
{
	return Receive(memory).transform_error(ErrorTransfer{ error_code }).value_or(true);
}

bool
net::Socket::Receive(std::span<std::byte> memory, size_t size, net::ErrorCode& error_code)
const noexcept
{
	return Receive(memory, std::move(size)).transform_error(ErrorTransfer{ error_code }).value_or(true);
}

bool
net::Socket::Receive(std::byte* const& memory, size_t size, net::ErrorCode& error_code)
const noexcept
{
	return Receive(memory, std::move(size)).transform_error(ErrorTransfer{ error_code }).value_or(true);
}

net::Socket::AsyncResult
net::Socket::Receive(net::IoContext& context, std::span<std::byte> memory)
const noexcept
{
	::WSABUF buffer
	{
		.len = static_cast<::ULONG>(memory.size_bytes()),
		.buf = reinterpret_cast<char*>(const_cast<std::byte*>(memory.data())),
	};

	::DWORD bytes = 0;
	::DWORD flags = 0;
	if (0 == ::WSARecv(myHandle
		, std::addressof(buffer), 1
		, std::addressof(bytes)
		, std::addressof(flags)
		, reinterpret_cast<::LPWSAOVERLAPPED>(std::addressof(context))
		, nullptr))
	{
		return bytes;
	}
	else
	{
		if (auto error = AcquireNetworkError(); error != ErrorCode::PendedIoOperation)
		{
			return std::unexpected(std::move(error));
		}
		else
		{
			return 0UL;
		}
	}
}

net::Socket::AsyncResult
net::Socket::Receive(net::IoContext& context, std::span<std::byte> memory, size_t size) const noexcept
{
	::WSABUF buffer
	{
		.len = static_cast<::ULONG>(std::min(memory.size_bytes(), size)),
		.buf = reinterpret_cast<char*>(const_cast<std::byte*>(memory.data())),
	};

	::DWORD bytes = 0;
	::DWORD flags = 0;
	if (0 == ::WSARecv(myHandle
		, std::addressof(buffer), 1
		, std::addressof(bytes)
		, std::addressof(flags)
		, reinterpret_cast<::LPWSAOVERLAPPED>(std::addressof(context))
		, nullptr))
	{
		return bytes;
	}
	else
	{
		if (auto error = AcquireNetworkError(); error != ErrorCode::PendedIoOperation)
		{
			return std::unexpected(std::move(error));
		}
		else
		{
			return 0UL;
		}
	}
}

net::Socket::AsyncResult
net::Socket::Receive(net::IoContext& context, std::byte* const& memory, size_t size)
const noexcept
{
	::WSABUF buffer
	{
		.len = static_cast<::ULONG>(size),
		.buf = reinterpret_cast<char*>(const_cast<std::byte*>(memory)),
	};

	::DWORD bytes = 0;
	::DWORD flags = 0;
	if (0 == ::WSARecv(myHandle
		, std::addressof(buffer), 1
		, std::addressof(bytes)
		, std::addressof(flags)
		, reinterpret_cast<::LPWSAOVERLAPPED>(std::addressof(context))
		, nullptr))
	{
		return bytes;
	}
	else
	{
		if (auto error = AcquireNetworkError(); error != ErrorCode::PendedIoOperation)
		{
			return std::unexpected(std::move(error));
		}
		else
		{
			return 0UL;
		}
	}
}

bool
net::Socket::Receive(net::IoContext& context, std::span<std::byte> memory, net::ErrorCode& error_code)
const noexcept
{
	return Receive(context, memory).transform_error(ErrorTransfer{ error_code }).value_or(true);
}

bool
net::Socket::Receive(net::IoContext& context, std::span<std::byte> memory, size_t size, net::ErrorCode& error_code)
const noexcept
{
	return Receive(context, memory, std::move(size)).transform_error(ErrorTransfer{ error_code }).value_or(true);
}

bool
net::Socket::Receive(net::IoContext& context, std::byte* const& memory, size_t size, net::ErrorCode& error_code)
const noexcept
{
	return Receive(context, memory, std::move(size)).transform_error(ErrorTransfer{ error_code }).value_or(true);
}

net::Socket::IoTask
net::Socket::MakeReceiveTask(net::IoContext& context, std::span<std::byte> memory)
const noexcept
{
	if (auto sent = Receive(context, memory); sent.has_value())
	{
		co_return std::move(sent);
	}

	static ::DWORD flags = 0;
	::DWORD transferred_bytes = 0;

	::BOOL result = ::WSAGetOverlappedResult(myHandle
		, reinterpret_cast<::LPWSAOVERLAPPED>(std::addressof(context))
		, std::addressof(transferred_bytes)
		, TRUE
		, std::addressof(flags));

	if (FALSE == result)
	{
		co_return std::unexpected{ AcquireNetworkError() };
	}
	else
	{
		co_return transferred_bytes;
	}
}

net::Socket::IoTask
net::Socket::MakeReceiveTask(net::IoContext& context, std::span<std::byte> memory, size_t size)
const noexcept
{
	if (auto sent = Receive(context, memory, std::move(size)); sent.has_value())
	{
		co_return std::move(sent);
	}

	static ::DWORD flags = 0;
	::DWORD transferred_bytes = 0;

	::BOOL result = ::WSAGetOverlappedResult(myHandle
		, reinterpret_cast<::LPWSAOVERLAPPED>(std::addressof(context))
		, std::addressof(transferred_bytes)
		, TRUE
		, std::addressof(flags));

	if (FALSE == result)
	{
		co_return std::unexpected{ AcquireNetworkError() };
	}
	else
	{
		co_return transferred_bytes;
	}
}

net::Socket::IoTask
net::Socket::MakeReceiveTask(net::IoContext& context, std::byte* const& memory, size_t size)
const noexcept
{
	if (auto sent = Receive(context, memory, std::move(size)); sent.has_value())
	{
		co_return std::move(sent);
	}

	static ::DWORD flags = 0;
	::DWORD transferred_bytes = 0;

	::BOOL result = ::WSAGetOverlappedResult(myHandle
		, reinterpret_cast<::LPWSAOVERLAPPED>(std::addressof(context))
		, std::addressof(transferred_bytes)
		, TRUE
		, std::addressof(flags));

	if (FALSE == result)
	{
		co_return std::unexpected{ AcquireNetworkError() };
	}
	else
	{
		co_return transferred_bytes;
	}
}

net::Socket::IoTask
net::Socket::MakeReceiveTask(const std::shared_ptr<net::IoContext>& context, std::span<std::byte> memory)
const noexcept
{
	return MakeReceiveTask(*context, std::move(memory));
}

net::Socket::IoTask
net::Socket::MakeReceiveTask(const std::shared_ptr<net::IoContext>& context, std::span<std::byte> memory, size_t size)
const noexcept
{
	return MakeReceiveTask(*context, std::move(memory), std::move(size));
}

net::Socket::IoTask
net::Socket::MakeReceiveTask(const std::shared_ptr<net::IoContext>& context, std::byte* const& memory, size_t size)
const noexcept
{
	return MakeReceiveTask(*context, memory, std::move(size));
}

net::Socket::IoTask
net::Socket::AsyncRecv(net::IoContext& context, std::span<std::byte> memory)
const noexcept
{
	auto task = MakeReceiveTask(context, memory);
	task.StartAsync();

	return task;
}

net::Socket::IoTask
net::Socket::AsyncRecv(net::IoContext& context, std::span<std::byte> memory, size_t size)
const noexcept
{
	auto task = MakeReceiveTask(context, memory, std::move(size));
	task.StartAsync();

	return task;
}

net::Socket::IoTask
net::Socket::AsyncRecv(net::IoContext& context, std::byte* const& memory, size_t size)
const noexcept
{
	auto task = MakeReceiveTask(context, memory, std::move(size));
	task.StartAsync();

	return task;
}
