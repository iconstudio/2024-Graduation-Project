#pragma comment(lib, "Ws2_32.lib")
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "NativeSocket.h"
#include "IconerBlueprinter.h"
#include <WinSock2.h>
#include <cstddef>
#include <utility>
#include <coroutine>
#undef min
#undef max

FNativeSocket::SocketResult
FNativeSocket::Receive(std::span<uint8> memory)
const noexcept
{
	int bytes = recv(GetHandle(), reinterpret_cast<char*>(memory.data()), static_cast<int>(memory.size_bytes()), 0);

	if (SOCKET_ERROR != bytes)
	{
		return static_cast<uint32>(bytes);
	}
	else
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}
}

FNativeSocket::SocketResult
FNativeSocket::Receive(std::span<uint8> memory, size_t size)
const noexcept
{
	int bytes = recv(GetHandle(), reinterpret_cast<char*>(memory.data()), static_cast<int>(std::min(memory.size_bytes(), size)), 0);

	if (SOCKET_ERROR != bytes)
	{
		return static_cast<uint32>(bytes);
	}
	else
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}
}

FNativeSocket::SocketResult
FNativeSocket::Receive(uint8* const& memory, size_t size)
const noexcept
{
	int bytes = recv(GetHandle(), reinterpret_cast<char*>(memory), static_cast<int>(size), 0);

	if (SOCKET_ERROR != bytes)
	{
		return static_cast<uint32>(bytes);
	}
	else
	{
		return Unexpected(UNetworkUtility::AcquireNetworkError());
	}
}

bool
FNativeSocket::Receive(std::span<uint8> memory
	, EErrorCode& error_code)
	const noexcept
{
	return Receive(memory).Translate(
		[](unsigned int&&) noexcept -> Expected<bool, EErrorCode> {
		return true;
	}).Else(
		[&](EErrorCode&& tr_error_code) noexcept -> Expected<bool, EErrorCode> {
		error_code = std::move(tr_error_code);
		return false;
	}).ValueOr(false);
}

bool
FNativeSocket::Receive(std::span<uint8> memory, size_t size, EErrorCode& error_code)
const noexcept
{
	return Receive(memory, std::move(size)).Translate(
		[](unsigned int&&) noexcept -> Expected<bool, EErrorCode> {
		return true;
	}).Else(
		[&](EErrorCode&& tr_error_code) noexcept -> Expected<bool, EErrorCode> {
		error_code = std::move(tr_error_code);
		return false;
	}).ValueOr(false);
}

bool
FNativeSocket::Receive(uint8* const& memory, size_t size
	, EErrorCode& error_code)
	const noexcept
{
	return Receive(memory, std::move(size)).Translate(
		[](unsigned int&&) noexcept -> Expected<bool, EErrorCode> {
		return true;
	}).Else(
		[&](EErrorCode&& tr_error_code) noexcept -> Expected<bool, EErrorCode> {
		error_code = std::move(tr_error_code);
		return false;
	}).ValueOr(false);
}

FNativeSocket::SocketResult
FNativeSocket::Receive(FIoContext& context, std::span<uint8> memory)
const noexcept
{
	WSABUF buffer
	{
		.len = static_cast<unsigned long>(memory.size_bytes()),
		.buf = reinterpret_cast<char*>(const_cast<uint8*>(memory.data())),
	};

	unsigned long flags = 0;
	unsigned long transferred_bytes = 0;

	if (0 == WSARecv(GetHandle()
		, std::addressof(buffer), 1
		, std::addressof(transferred_bytes)
		, std::addressof(flags)
		, reinterpret_cast<LPWSAOVERLAPPED>(std::addressof(context))
		, nullptr))
	{
		return transferred_bytes;
	}
	else
	{
		if (auto error = UNetworkUtility::AcquireNetworkError(); error != EErrorCode::PendedIoOperation)
		{
			return Unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}

FNativeSocket::SocketResult
FNativeSocket::Receive(FIoContext& context, std::span<uint8> memory, size_t size) const noexcept
{
	WSABUF buffer
	{
		.len = static_cast<unsigned long>(std::min(memory.size_bytes(), size)),
		.buf = reinterpret_cast<char*>(const_cast<uint8*>(memory.data())),
	};

	unsigned long flags = 0;
	unsigned long transferred_bytes = 0;

	if (0 == WSARecv(GetHandle()
		, std::addressof(buffer), 1
		, std::addressof(transferred_bytes)
		, std::addressof(flags)
		, reinterpret_cast<LPWSAOVERLAPPED>(std::addressof(context))
		, nullptr))
	{
		return transferred_bytes;
	}
	else
	{
		if (auto error = UNetworkUtility::AcquireNetworkError(); error != EErrorCode::PendedIoOperation)
		{
			return Unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}

FNativeSocket::SocketResult
FNativeSocket::Receive(FIoContext& context, uint8* const& memory, size_t size)
const noexcept
{
	WSABUF buffer
	{
		.len = static_cast<unsigned long>(size),
		.buf = reinterpret_cast<char*>(const_cast<uint8*>(memory)),
	};

	unsigned long flags = 0;
	unsigned long transferred_bytes = 0;

	if (0 == WSARecv(GetHandle()
		, std::addressof(buffer), 1
		, std::addressof(transferred_bytes)
		, std::addressof(flags)
		, reinterpret_cast<LPWSAOVERLAPPED>(std::addressof(context))
		, nullptr))
	{
		return transferred_bytes;
	}
	else
	{
		if (auto error = UNetworkUtility::AcquireNetworkError(); error != EErrorCode::PendedIoOperation)
		{
			return Unexpected(std::move(error));
		}
		else
		{
			return 0U;
		}
	}
}

bool
FNativeSocket::Receive(FIoContext& context, std::span<uint8> memory, EErrorCode& error_code)
	const noexcept
{
	return Receive(context, memory).Translate(
		[](unsigned int&&) noexcept -> Expected<bool, EErrorCode> {
		return true;
	}).Else(
		[&](EErrorCode&& tr_error_code) noexcept -> Expected<bool, EErrorCode> {
		error_code = std::move(tr_error_code);
		return false;
	}).ValueOr(false);
}

bool
FNativeSocket::Receive(FIoContext& context, std::span<uint8> memory, size_t size, EErrorCode& error_code)
const noexcept
{
	return Receive(context, memory, std::move(size)).Translate(
		[](unsigned int&&) noexcept -> Expected<bool, EErrorCode> {
		return true;
	}).Else(
		[&](EErrorCode&& tr_error_code) noexcept -> Expected<bool, EErrorCode> {
		error_code = std::move(tr_error_code);
		return false;
	}).ValueOr(false);
}

bool
FNativeSocket::Receive(FIoContext& context, uint8* const& memory, size_t size, EErrorCode& error_code)
	const noexcept
{
	return Receive(context, memory, size).Translate(
		[](unsigned int&&) noexcept -> Expected<bool, EErrorCode> {
		return true;
	}).Else(
		[&](EErrorCode&& tr_error_code) noexcept -> Expected<bool, EErrorCode> {
		error_code = std::move(tr_error_code);
		return false;
	}).ValueOr(false);
}

FSocketTask
FNativeSocket::MakeReceiveTask(FIoContext& context, std::span<uint8> memory)
const noexcept
{
	SocketResult sent = Receive(context, memory);
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
FNativeSocket::MakeReceiveTask(FIoContext& context, std::span<uint8> memory, size_t size)
const noexcept
{
	SocketResult sent = Receive(context, memory, size);
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
FNativeSocket::MakeReceiveTask(FIoContext& context, uint8* const& memory, size_t size)
const noexcept
{
	SocketResult sent = Receive(context, memory, size);
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
FNativeSocket::MakeReceiveTask(const TSharedPtr<FIoContext>& context, std::span<uint8> memory)
const noexcept
{
	return MakeReceiveTask(*context, std::move(memory));
}

FSocketTask
FNativeSocket::MakeReceiveTask(const TSharedPtr<FIoContext>& context, std::span<uint8> memory, size_t size)
const noexcept
{
	return MakeReceiveTask(*context, std::move(memory), std::move(size));
}

FSocketTask
FNativeSocket::MakeReceiveTask(const TSharedPtr<FIoContext>& context, uint8* const& memory, size_t size)
const noexcept
{
	return MakeReceiveTask(*context, memory, std::move(size));
}

FSocketTask
FNativeSocket::AsyncRecv(FIoContext& context, std::span<uint8> memory)
const noexcept
{
	auto task = MakeReceiveTask(context, memory);
	task.StartAsync();

	return task;
}

FSocketTask
FNativeSocket::AsyncRecv(FIoContext& context, std::span<uint8> memory, size_t size)
const noexcept
{
	auto task = MakeReceiveTask(context, memory, std::move(size));
	task.StartAsync();

	return task;
}

FSocketTask
FNativeSocket::AsyncRecv(FIoContext& context, uint8* const& memory, size_t size)
const noexcept
{
	auto task = MakeReceiveTask(context, memory, std::move(size));
	task.StartAsync();

	return task;
}
