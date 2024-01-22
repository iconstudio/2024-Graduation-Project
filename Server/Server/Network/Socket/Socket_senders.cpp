module;
#pragma comment(lib, "Ws2_32.lib")
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

module Net.Socket;
import <cstddef>;
import <utility>;
import <coroutine>;

net::Socket::SocketResult RawSend(const net::NativeSocket& sock, ::WSABUF& buffer) noexcept;
net::Socket::SocketResult RawSendEx(const net::NativeSocket& sock, ::WSABUF& buffer, void* context, ::LPWSAOVERLAPPED_COMPLETION_ROUTINE routine) noexcept;

net::Socket::SocketResult
net::Socket::Send(std::span<const std::byte> memory)
const noexcept
{
	::WSABUF buffer
	{
		.len = static_cast<::ULONG>(memory.size_bytes()),
		.buf = reinterpret_cast<char*>(const_cast<std::byte*>(memory.data())),
	};

	return RawSend(myHandle, buffer);
}

net::Socket::SocketResult
net::Socket::Send(std::span<const std::byte> memory, size_t size) const noexcept
{
	::WSABUF buffer
	{
		.len = static_cast<::ULONG>(std::min(memory.size_bytes(), size)),
		.buf = reinterpret_cast<char*>(const_cast<std::byte*>(memory.data())),
	};

	return RawSend(myHandle, buffer);
}

net::Socket::SocketResult
net::Socket::Send(const std::byte* const& memory, size_t size)
const noexcept
{
	::WSABUF buffer
	{
		.len = static_cast<::ULONG>(size),
		.buf = reinterpret_cast<char*>(const_cast<std::byte*>(memory)),
	};

	return RawSend(myHandle, buffer);
}

bool
net::Socket::Send(std::span<const std::byte> memory
	, net::ErrorCode& error_code)
	const noexcept
{
	return Send(memory).and_then(
		[](unsigned int&&) noexcept -> expected<bool, ErrorCode> {
			return true;
		}).or_else(
			[&](ErrorCode&& tr_error_code) noexcept -> expected<bool, ErrorCode> {
				error_code = std::move(tr_error_code);
				return false;
			}).value_or(false);
}

bool
net::Socket::Send(std::span<const std::byte> memory, size_t size, net::ErrorCode& error_code)
const noexcept
{
	return Send(memory, size).and_then(
		[](unsigned int&&) noexcept -> expected<bool, ErrorCode> {
			return true;
		}).or_else(
			[&](ErrorCode&& tr_error_code) noexcept -> expected<bool, ErrorCode> {
				error_code = std::move(tr_error_code);
				return false;
			}).value_or(false);
}

bool
net::Socket::Send(const std::byte* const& memory, size_t size
	, net::ErrorCode& error_code)
	const noexcept
{
	return Send(memory, size).and_then(
		[](unsigned int&&) noexcept -> expected<bool, ErrorCode> {
			return true;
		}).or_else(
			[&](ErrorCode&& tr_error_code) noexcept -> expected<bool, ErrorCode> {
				error_code = std::move(tr_error_code);
				return false;
			}).value_or(false);
}

net::Socket::SocketResult
net::Socket::Send(net::IoContext& context, std::span<const std::byte> memory)
const noexcept
{
	::WSABUF buffer
	{
		.len = static_cast<::ULONG>(memory.size_bytes()),
		.buf = reinterpret_cast<char*>(const_cast<std::byte*>(memory.data())),
	};

	return RawSendEx(myHandle, buffer, std::addressof(context), nullptr);
}

net::Socket::SocketResult
net::Socket::Send(net::IoContext& context, std::span<const std::byte> memory, size_t size)
const noexcept
{
	::WSABUF buffer
	{
		.len = static_cast<::ULONG>(std::min(memory.size_bytes(), size)),
		.buf = reinterpret_cast<char*>(const_cast<std::byte*>(memory.data())),
	};

	return RawSendEx(myHandle, buffer, std::addressof(context), nullptr);
}

net::Socket::SocketResult
net::Socket::Send(net::IoContext& context, const std::byte* const& memory, size_t size)
const noexcept
{
	::WSABUF buffer
	{
		.len = static_cast<::ULONG>(size),
		.buf = reinterpret_cast<char*>(const_cast<std::byte*>(memory)),
	};

	return RawSendEx(myHandle, buffer, std::addressof(context), nullptr);
}

bool
net::Socket::Send(io::Context& context, std::span<const std::byte> memory
	, net::ErrorCode& error_code)
	const noexcept
{
	return Send(context, memory).and_then(
		[](unsigned int&&) noexcept -> expected<bool, ErrorCode> {
			return true;
		}).or_else(
			[&](ErrorCode&& tr_error_code) noexcept -> expected<bool, ErrorCode> {
				error_code = std::move(tr_error_code);
				return false;
			}).value_or(false);
}

bool
net::Socket::Send(net::IoContext& context, std::span<const std::byte> memory, size_t size, net::ErrorCode& error_code)
const noexcept
{
	return Send(context, memory, size).and_then(
		[](unsigned int&&) noexcept -> expected<bool, ErrorCode> {
			return true;
		}).or_else(
			[&](ErrorCode&& tr_error_code) noexcept -> expected<bool, ErrorCode> {
				error_code = std::move(tr_error_code);
				return false;
			}).value_or(false);
}

bool
net::Socket::Send(io::Context& context, const std::byte* const& memory
	, size_t size, net::ErrorCode& error_code)
	const noexcept
{
	return Send(context, memory, size).and_then(
		[](unsigned int&&) noexcept -> expected<bool, ErrorCode> {
			return true;
		}).or_else(
			[&](ErrorCode&& tr_error_code) noexcept -> expected<bool, ErrorCode> {
				error_code = std::move(tr_error_code);
				return false;
			}).value_or(false);
}

net::Socket::SocketTask
net::Socket::MakeSendTask(io::Context& context, std::span<const std::byte> memory)
const noexcept
{
	if (SocketSendingResult sent = Send(context, memory); not sent)
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
		co_return net::unexpected(net::AcquireSendingError());
	}
	else
	{
		co_return transferred_bytes;
	}
}

net::Socket::SocketTask
net::Socket::MakeSendTask(net::IoContext& context, std::span<const std::byte> memory, size_t size)
const noexcept
{
	if (SocketSendingResult sent = Send(context, memory, size); not sent)
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
		co_return net::unexpected(net::AcquireSendingError());
	}
	else
	{
		co_return transferred_bytes;
	}
}

net::Socket::SocketTask
net::Socket::MakeSendTask(io::Context& context, const std::byte* const& memory, size_t size)
const noexcept
{
	if (SocketSendingResult sent = Send(context, memory, size); not sent)
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
		co_return net::unexpected(net::AcquireSendingError());
	}
	else
	{
		co_return transferred_bytes;
	}
}

net::Socket::SocketTask
net::Socket::MakeSendTask(const std::shared_ptr<io::Context>& context, std::span<const std::byte> memory)
const noexcept
{
	return MakeSendTask(*context, std::move(memory));
}

net::Socket::SocketTask
net::Socket::MakeSendTask(const std::shared_ptr<io::Context>& context, std::span<const std::byte> memory, size_t size)
const noexcept
{
	return MakeSendTask(*context, std::move(memory), std::move(size));
}

net::Socket::SocketTask
net::Socket::MakeSendTask(const std::shared_ptr<io::Context>& context, const std::byte* const& memory, size_t size)
const noexcept
{
	return MakeSendTask(*context, memory, std::move(size));
}

net::Socket::SocketTask
net::Socket::AsyncSend(net::IoContext& context, std::span<const std::byte> memory)
const noexcept
{
	auto task = MakeSendTask(context, memory);
	task.StartAsync();

	return task;
}

net::Socket::SocketTask
net::Socket::AsyncSend(net::IoContext& context, std::span<const std::byte> memory, size_t size)
const noexcept
{
	auto task = MakeSendTask(context, memory, size);
	task.StartAsync();

	return task;
}

net::Socket::SocketTask
net::Socket::AsyncSend(net::IoContext& context, const std::byte* const& memory, size_t size)
const noexcept
{
	auto task = MakeSendTask(context, memory, size);
	task.StartAsync();

	return task;
}

net::Socket::SocketResult
RawSend(const net::NativeSocket& sock
	, ::WSABUF& buffer)
	noexcept
{
	if (::DWORD bytes = 0; 0 == ::WSASend(sock
		, std::addressof(buffer), 1
		, std::addressof(bytes)
		, 0
		, nullptr, nullptr))
	{
		return bytes;
	}
	else
	{
		return net::unexpected(net::AcquireSendingError());
	}
}

net::Socket::SocketResult
RawSendEx(const net::NativeSocket& sock
	, ::WSABUF& buffer
	, void* context
	, ::LPWSAOVERLAPPED_COMPLETION_ROUTINE routine)
	noexcept
{
	if (::DWORD bytes = 0; 0 == ::WSASend(sock
		, std::addressof(buffer), 1
		, std::addressof(bytes)
		, 0
		, reinterpret_cast<::LPWSAOVERLAPPED>(context)
		, routine))
	{
		return bytes;
	}
	else
	{
		if (net::ErrorCode error = net::AcquireSendingError(); error != net::ErrorCode::PendedIoOperation)
		{
			return net::unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}
