module;
#pragma comment(lib, "Ws2_32.lib")
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

module Net.Socket;
import <cstddef>;
import <utility>;
import <coroutine>;

net::SocketReceivingResult
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
		return unexpected(AcquireReceivingError());
	}
}

net::SocketReceivingResult
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
		return unexpected(AcquireReceivingError());
	}
}

net::SocketReceivingResult
net::Socket::Receive(std::byte* const& memory, size_t size)
const noexcept
{
	if (int bytes = ::recv(myHandle
		, reinterpret_cast<char*>(memory), static_cast<int>(size)
		, 0); SOCKET_ERROR != bytes)
	{
		return static_cast<unsigned int>(bytes);
	}
	else
	{
		return unexpected(AcquireReceivingError());
	}
}

bool
net::Socket::Receive(std::span<std::byte> memory
	, net::ReceivingErrorCodes& error_code)
	const noexcept
{
	return Receive(memory).and_then(
		[](unsigned int&&) noexcept -> expected<bool, ReceivingErrorCodes> {
			return true;
		}).or_else(
			[&](net::ReceivingErrorCodes&& tr_error_code) noexcept -> expected<bool, ReceivingErrorCodes> {
				error_code = std::move(tr_error_code);
				return false;
			}).value_or(false);
}

bool
net::Socket::Receive(std::span<std::byte> memory, size_t size, net::ReceivingErrorCodes& error_code)
const noexcept
{
	return Receive(memory, std::move(size)).and_then(
		[](unsigned int&&) noexcept -> expected<bool, ReceivingErrorCodes> {
			return true;
		}).or_else(
			[&](net::ReceivingErrorCodes&& tr_error_code) noexcept -> expected<bool, ReceivingErrorCodes> {
				error_code = std::move(tr_error_code);
				return false;
			}).value_or(false);
}

bool
net::Socket::Receive(std::byte* const& memory, size_t size
	, net::ReceivingErrorCodes& error_code)
	const noexcept
{
	return Receive(memory, std::move(size)).and_then(
		[](unsigned int&&) noexcept -> expected<bool, ReceivingErrorCodes> {
			return true;
		}).or_else(
			[&](net::ReceivingErrorCodes&& tr_error_code) noexcept -> expected<bool, ReceivingErrorCodes> {
				error_code = std::move(tr_error_code);
				return false;
			}).value_or(false);
}

net::SocketReceivingResult
net::Socket::Receive(net::io::Context& context, std::span<std::byte> memory)
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
		if (auto error = AcquireReceivingError(); error != ErrorCodes::PendedIoOperation)
		{
			return unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}

net::SocketReceivingResult
net::Socket::Receive(net::io::Context& context, std::span<std::byte> memory, size_t size) const noexcept
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
		if (auto error = AcquireReceivingError(); error != ErrorCodes::PendedIoOperation)
		{
			return unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}

net::SocketReceivingResult
net::Socket::Receive(net::io::Context& context, std::byte* const& memory, size_t size)
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
		if (auto error = AcquireReceivingError(); error != ErrorCodes::PendedIoOperation)
		{
			return unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}

bool
net::Socket::Receive(net::io::Context& context, std::span<std::byte> memory
	, net::ReceivingErrorCodes& error_code)
	const noexcept
{
	return Receive(context, memory).and_then(
		[](unsigned int&&) noexcept -> expected<bool, ReceivingErrorCodes> {
			return true;
		}).or_else(
			[&](net::ReceivingErrorCodes&& tr_error_code) noexcept -> expected<bool, ReceivingErrorCodes> {
				error_code = std::move(tr_error_code);
				return false;
			}).value_or(false);
}

bool
net::Socket::Receive(net::io::Context& context, std::span<std::byte> memory, size_t size, net::ReceivingErrorCodes& error_code)
const noexcept
{
	return Receive(context, memory, std::move(size)).and_then(
		[](unsigned int&&) noexcept -> expected<bool, ReceivingErrorCodes> {
			return true;
		}).or_else(
			[&](net::ReceivingErrorCodes&& tr_error_code) noexcept -> expected<bool, ReceivingErrorCodes> {
				error_code = std::move(tr_error_code);
				return false;
			}).value_or(false);
}

bool
net::Socket::Receive(net::io::Context& context, std::byte* const& memory, size_t size
	, net::ReceivingErrorCodes& error_code)
	const noexcept
{
	return Receive(context, memory, size).and_then(
		[](unsigned int&&) noexcept -> expected<bool, ReceivingErrorCodes> {
			return true;
		}).or_else(
			[&](net::ReceivingErrorCodes&& tr_error_code) noexcept -> expected<bool, ReceivingErrorCodes> {
				error_code = std::move(tr_error_code);
				return false;
			}).value_or(false);
}

net::Task<net::SocketReceivingResult>
net::Socket::MakeReceiveTask(net::io::Context& context, std::span<std::byte> memory)
const noexcept
{
	if (SocketReceivingResult sent = Receive(context, memory); not sent)
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
		co_return net::unexpected(net::AcquireReceivingError());
	}
	else
	{
		co_return transferred_bytes;
	}
}

net::Task<net::SocketReceivingResult>
net::Socket::MakeReceiveTask(net::io::Context& context, std::span<std::byte> memory, size_t size)
const noexcept
{
	if (SocketReceivingResult sent = Receive(context, memory, size); not sent)
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
		co_return net::unexpected(net::AcquireReceivingError());
	}
	else
	{
		co_return transferred_bytes;
	}
}

net::Task<net::SocketReceivingResult>
net::Socket::MakeReceiveTask(net::io::Context& context, std::byte* const& memory, size_t size)
const noexcept
{
	if (SocketReceivingResult sent = Receive(context, memory, size); not sent)
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
		co_return net::unexpected(net::AcquireReceivingError());
	}
	else
	{
		co_return transferred_bytes;
	}
}

net::Task<net::SocketReceivingResult>
net::Socket::MakeReceiveTask(const std::shared_ptr<io::Context>& context, std::span<std::byte> memory)
const noexcept
{
	return MakeReceiveTask(*context, std::move(memory));
}

net::Task<net::SocketReceivingResult>
net::Socket::MakeReceiveTask(const std::shared_ptr<io::Context>& context, std::span<std::byte> memory, size_t size)
const noexcept
{
	return MakeReceiveTask(*context, std::move(memory), std::move(size));
}

net::Task<net::SocketReceivingResult>
net::Socket::MakeReceiveTask(const std::shared_ptr<io::Context>& context, std::byte* const& memory, size_t size)
const noexcept
{
	return MakeReceiveTask(*context, memory, std::move(size));
}

net::Task<net::SocketReceivingResult>
net::Socket::AsyncRecv(net::io::Context& context, std::span<std::byte> memory)
const noexcept
{
	auto task = MakeReceiveTask(context, memory);
	task.StartAsync();

	return task;
}

net::Task<net::SocketReceivingResult>
net::Socket::AsyncRecv(net::io::Context& context, std::span<std::byte> memory, size_t size)
const noexcept
{
	auto task = MakeReceiveTask(context, memory, std::move(size));
	task.StartAsync();

	return task;
}

net::Task<net::SocketReceivingResult>
net::Socket::AsyncRecv(net::io::Context& context, std::byte* const& memory, size_t size)
const noexcept
{
	auto task = MakeReceiveTask(context, memory, std::move(size));
	task.StartAsync();

	return task;
}
