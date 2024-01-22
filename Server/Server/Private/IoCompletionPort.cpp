module;
#include <WinSock2.h>

module Iconer.Net.IoCompletionPort;
import <thread>;

using namespace iconer;

net::IoCompletionPort::FactoryResult
net::IoCompletionPort::Create()
noexcept
{
	return Create(std::thread::hardware_concurrency());
}

net::IoCompletionPort::FactoryResult
net::IoCompletionPort::Create(std::uint32_t concurrency_hint)
noexcept
{
	auto ptr = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, std::move(concurrency_hint));

	if (nullptr == ptr)
	{
		return std::unexpected(AcquireNetworkError());
	}

	return IoCompletionPort{ ptr };
}

net::IoCompletionPort::IoCompletionPort(void* handle)
noexcept
	: Handler(std::move(handle))
{
}

net::Socket::SocketResult
net::IoCompletionPort::Register(net::Socket& socket, std::uintptr_t id)
noexcept
{
#if _DEBUG
	auto& sk = socket.GetHandle();
	const HANDLE target = reinterpret_cast<::HANDLE>(sk);

	auto& handle = GetHandle();
	auto port = ::CreateIoCompletionPort(target, const_cast<void*>(handle), id, 0);
#else
	auto port = ::CreateIoCompletionPort(reinterpret_cast<::HANDLE>(socket.GetHandle()), const_cast<void*>(GetHandle().GetPointer()), id, 0);
#endif

	if (nullptr == handle)
	{
		return AcquireNetworkError();
	}

	return std::nullopt;
}

bool
net::IoCompletionPort::TryRegister(net::Socket& socket, std::uintptr_t id, net::ErrorCode& error_code)
noexcept
{
	if (auto result = Register(socket, id); result)
	{
		return true;
	}
	else
	{
		error_code = std::move(result).value();
		return false;
	}
}

bool
net::IoCompletionPort::Destroy()
noexcept
{
	if (auto& handle = GetHandle(); nullptr != handle)
	{
		const bool result = (1 == CloseHandle(handle));
		myHandle = nullptr;

		return result;
	}
	else
	{
		return false;
	}
}

bool
net::IoCompletionPort::Destroy(net::ErrorCode& error_code)
noexcept
{
	if (auto result = Destroy(); result)
	{
		return true;
	}
	else
	{
		error_code = AcquireNetworkError();
		return false;
	}
}

bool
net::IoCompletionPort::Schedule(net::IoContext& context, std::uintptr_t id, unsigned long infobytes)
noexcept
{
	return 0 != ::PostQueuedCompletionStatus(GetHandle()
		, std::move(infobytes)
		, std::move(id)
		, reinterpret_cast<::WSAOVERLAPPED*>(std::addressof(context)));
}

bool
net::IoCompletionPort::Schedule(net::IoContext* const context, std::uintptr_t id, unsigned long infobytes)
noexcept
{
	return 0 != ::PostQueuedCompletionStatus(GetHandle()
		, std::move(infobytes)
		, std::move(id)
		, reinterpret_cast<::WSAOVERLAPPED*>(context));
}

net::IoEvent
net::IoCompletionPort::WaitForIoResult()
noexcept
{
	net::IoEvent ev_handle{};

	::LPOVERLAPPED overlapped{};
	::BOOL result = 0;
	try
	{
		result = ::GetQueuedCompletionStatus(GetHandle()
			, std::addressof(ev_handle.ioBytes)
			, std::addressof(ev_handle.eventId)
			, std::addressof(overlapped)
			, INFINITE);

		ev_handle.ioContext = reinterpret_cast<net::IoContext*>(overlapped);
		ev_handle.isSucceed = (1 == result);
	}
	catch (...)
	{
		ev_handle.ioContext = nullptr;
		ev_handle.isSucceed = false;
	}

	return ev_handle;
}
