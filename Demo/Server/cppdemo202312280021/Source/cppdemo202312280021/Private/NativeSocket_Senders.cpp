#pragma comment(lib, "Ws2_32.lib")
#include "NativeSocket.h"
#include "IconerBlueprinter.h"
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <cstddef>
#include <utility>
#include <coroutine>

FNativeSocket::SocketResult RawSend(const int64& sock, WSABUF& buffer) noexcept;
FNativeSocket::SocketResult RawSendEx(const int64& sock, WSABUF& buffer, void* context, ::LPWSAOVERLAPPED_COMPLETION_ROUTINE routine) noexcept;

FNativeSocket::SocketResult
FNativeSocket::Send(std::span<const uint8> memory)
const noexcept
{
	WSABUF buffer
	{
		.len = static_cast<unsigned long>(memory.size_bytes()),
		.buf = reinterpret_cast<char*>(const_cast<uint8*>(memory.data())),
	};

	return RawSend(GetHandle(), buffer);
}

FNativeSocket::SocketResult
FNativeSocket::Send(std::span<const uint8> memory, size_t size) const noexcept
{
	WSABUF buffer
	{
		.len = static_cast<unsigned long>(std::min(memory.size_bytes(), size)),
		.buf = reinterpret_cast<char*>(const_cast<uint8*>(memory.data())),
	};

	return RawSend(GetHandle(), buffer);
}

FNativeSocket::SocketResult
FNativeSocket::Send(const uint8* const& memory, size_t size)
const noexcept
{
	WSABUF buffer
	{
		.len = static_cast<unsigned long>(size),
		.buf = reinterpret_cast<char*>(const_cast<uint8*>(memory)),
	};

	return RawSend(GetHandle(), buffer);
}

bool
FNativeSocket::Send(std::span<const uint8> memory, EErrorCode& error_code)
const noexcept
{
	return Send(memory).Translate(
		[](unsigned int&&) noexcept -> Expected<bool, EErrorCode> {
		return true;
	}).Else(
		[&](EErrorCode&& tr_error_code) noexcept -> Expected<bool, EErrorCode> {
		error_code = std::move(tr_error_code);
		return false;
	}).Value();
}

bool
FNativeSocket::Send(std::span<const uint8> memory, size_t size, EErrorCode& error_code)
const noexcept
{
	return Send(memory, size).Translate(
		[](unsigned int&&) noexcept -> Expected<bool, EErrorCode> {
		return true;
	}).Else(
		[&](EErrorCode&& tr_error_code) noexcept -> Expected<bool, EErrorCode> {
		error_code = std::move(tr_error_code);
		return false;
	}).Value();
}

bool
FNativeSocket::Send(const uint8* const& memory, size_t size, EErrorCode& error_code)
const noexcept
{
	return Send(memory, size).Translate(
		[](unsigned int&&) noexcept -> Expected<bool, EErrorCode> {
		return true;
	}).Else(
		[&](EErrorCode&& tr_error_code) noexcept -> Expected<bool, EErrorCode> {
		error_code = std::move(tr_error_code);
		return false;
	}).Value();
}

FNativeSocket::SocketResult
FNativeSocket::Send(FIoContext& context, std::span<const uint8> memory)
const noexcept
{
	WSABUF buffer
	{
		.len = static_cast<unsigned long>(memory.size_bytes()),
		.buf = reinterpret_cast<char*>(const_cast<uint8*>(memory.data())),
	};

	return RawSendEx(GetHandle(), buffer, std::addressof(context), nullptr);
}

FNativeSocket::SocketResult
FNativeSocket::Send(FIoContext& context, std::span<const uint8> memory, size_t size)
const noexcept
{
	WSABUF buffer
	{
		.len = static_cast<unsigned long>(std::min(memory.size_bytes(), size)),
		.buf = reinterpret_cast<char*>(const_cast<uint8*>(memory.data())),
	};

	return RawSendEx(GetHandle(), buffer, std::addressof(context), nullptr);
}

FNativeSocket::SocketResult
FNativeSocket::Send(FIoContext& context, const uint8* const& memory, size_t size)
const noexcept
{
	WSABUF buffer
	{
		.len = static_cast<unsigned long>(size),
		.buf = reinterpret_cast<char*>(const_cast<uint8*>(memory)),
	};

	return RawSendEx(GetHandle(), buffer, std::addressof(context), nullptr);
}

bool
FNativeSocket::Send(FIoContext& context, std::span<const uint8> memory, EErrorCode& error_code)
const noexcept
{
	return Send(context, memory).Translate(
		[](unsigned int&&) noexcept -> Expected<bool, EErrorCode> {
		return true;
	}).Else(
		[&](EErrorCode&& tr_error_code) noexcept -> Expected<bool, EErrorCode> {
		error_code = std::move(tr_error_code);
		return false;
	}).Value();
}

bool
FNativeSocket::Send(FIoContext& context, std::span<const uint8> memory, size_t size, EErrorCode& error_code)
const noexcept
{
	return Send(context, memory, size).Translate(
		[](unsigned int&&) noexcept -> Expected<bool, EErrorCode> {
		return true;
	}).Else(
		[&](EErrorCode&& tr_error_code) noexcept -> Expected<bool, EErrorCode> {
		error_code = std::move(tr_error_code);
		return false;
	}).Value();
}

bool
FNativeSocket::Send(FIoContext& context, const uint8* const& memory
	, size_t size, EErrorCode& error_code)
	const noexcept
{
	return Send(context, memory, size).Translate(
		[](unsigned int&&) noexcept -> Expected<bool, EErrorCode> {
		return true;
	}).Else(
		[&](EErrorCode&& tr_error_code) noexcept -> Expected<bool, EErrorCode> {
		error_code = std::move(tr_error_code);
		return false;
	}).Value();
}

FSocketTask
FNativeSocket::MakeSendTask(FIoContext& context, std::span<const uint8> memory)
const noexcept
{
	SocketResult sent = Send(context, memory);
	if (not sent)
	{
		co_return std::move(sent);
	}

	unsigned long flags = 0;
	unsigned long transferred_bytes = 0;

	::BOOL result = ::WSAGetOverlappedResult(GetHandle()
		, reinterpret_cast<LPWSAOVERLAPPED>(std::addressof(context))
		, std::addressof(transferred_bytes)
		, TRUE
		, std::addressof(flags));

	if (FALSE == result)
	{
		co_return Unexpected(UNetworkUtility::AcquireNetworkError());
	}
	else
	{
		co_return transferred_bytes;
	}
}

FSocketTask
FNativeSocket::MakeSendTask(FIoContext& context, std::span<const uint8> memory, size_t size)
const noexcept
{
	SocketResult sent = Send(context, memory, size);
	if (not sent)
	{
		co_return std::move(sent);
	}

	unsigned long flags = 0;
	unsigned long transferred_bytes = 0;

	::BOOL result = ::WSAGetOverlappedResult(GetHandle()
		, reinterpret_cast<LPWSAOVERLAPPED>(std::addressof(context))
		, std::addressof(transferred_bytes)
		, TRUE
		, std::addressof(flags));

	if (FALSE == result)
	{
		co_return Unexpected(UNetworkUtility::AcquireNetworkError());
	}
	else
	{
		co_return transferred_bytes;
	}
}

FSocketTask
FNativeSocket::MakeSendTask(FIoContext& context, const uint8* const& memory, size_t size)
const noexcept
{
	SocketResult sent = Send(context, memory, size);
	if (not sent)
	{
		co_return std::move(sent);
	}

	unsigned long flags = 0;
	unsigned long transferred_bytes = 0;

	::BOOL result = ::WSAGetOverlappedResult(GetHandle()
		, reinterpret_cast<LPWSAOVERLAPPED>(std::addressof(context))
		, std::addressof(transferred_bytes)
		, TRUE
		, std::addressof(flags));

	if (FALSE == result)
	{
		co_return Unexpected(UNetworkUtility::AcquireNetworkError());
	}
	else
	{
		co_return transferred_bytes;
	}
}

FSocketTask
FNativeSocket::MakeSendTask(const std::shared_ptr<FIoContext>& context, std::span<const uint8> memory)
const noexcept
{
	return MakeSendTask(*context, std::move(memory));
}

FSocketTask
FNativeSocket::MakeSendTask(const std::shared_ptr<FIoContext>& context, std::span<const uint8> memory, size_t size)
const noexcept
{
	return MakeSendTask(*context, std::move(memory), std::move(size));
}

FSocketTask
FNativeSocket::MakeSendTask(const std::shared_ptr<FIoContext>& context, const uint8* const& memory, size_t size)
const noexcept
{
	return MakeSendTask(*context, memory, std::move(size));
}

FSocketTask
FNativeSocket::AsyncSend(FIoContext& context, std::span<const uint8> memory)
const noexcept
{
	auto task = MakeSendTask(context, memory);
	task.StartAsync();

	return task;
}

FSocketTask
FNativeSocket::AsyncSend(FIoContext& context, std::span<const uint8> memory, size_t size)
const noexcept
{
	auto task = MakeSendTask(context, memory, size);
	task.StartAsync();

	return task;
}

FSocketTask
FNativeSocket::AsyncSend(FIoContext& context, const uint8* const& memory, size_t size)
const noexcept
{
	auto task = MakeSendTask(context, memory, size);
	task.StartAsync();

	return task;
}

FNativeSocket::SocketResult
RawSend(const int64& sock
	, WSABUF& buffer)
	noexcept
{
	unsigned long bytes = 0;

	if (0 == ::WSASend(static_cast<uintptr_t>(sock)
		, std::addressof(buffer), 1
		, std::addressof(bytes)
		, 0
		, nullptr, nullptr))
	{
		return bytes;
	}
	else
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}
}

FNativeSocket::SocketResult
RawSendEx(const int64& sock
	, WSABUF& buffer
	, void* context
	, ::LPWSAOVERLAPPED_COMPLETION_ROUTINE routine)
	noexcept
{
	unsigned long bytes = 0;

	if (0 == ::WSASend(static_cast<uintptr_t>(sock)
		, std::addressof(buffer), 1
		, std::addressof(bytes)
		, 0
		, reinterpret_cast<LPWSAOVERLAPPED>(context)
		, routine))
	{
		return bytes;
	}
	else
	{
		EErrorCode error = UNetworkUtility::AcquireNetworkError();

		if (error != EErrorCode::PendedIoOperation)
		{
			return Unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}
