module;
#define NOMINMAX
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>

module Net.Io.Station;
import <thread>;

net::io::Station::Stationary
net::io::Station::Create()
noexcept
{
	return Create(std::thread::hardware_concurrency());
}

net::io::Station::Stationary
net::io::Station::Create(std::uint32_t concurrency_hint)
noexcept
{
	auto ptr = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, std::move(concurrency_hint));
	NativeHandle io_port = NativeHandle::Create(ptr);

	if (not io_port)
	{
		return std::unexpected(AcquireNetworkError());
	}

	return Station{ std::move(io_port) };
}

net::io::Station::Station(net::NativeHandle&& handle)
noexcept
	: Handler(std::move(handle))
{}

net::SocketResult
net::io::Station::Register(net::Socket& socket, std::uintptr_t id)
noexcept
{
#if _DEBUG
	auto& sk = socket.GetHandle();
	const HANDLE target = reinterpret_cast<::HANDLE>(sk);

	auto& handle = GetHandle();
	auto ptr = handle.GetPointer();

	auto port = ::CreateIoCompletionPort(target, const_cast<void*>(ptr), id, 0);
#else
	auto port = ::CreateIoCompletionPort(reinterpret_cast<::HANDLE>(socket.GetHandle()), const_cast<void*>(GetHandle().GetPointer()), id, 0);
#endif

	WSA_FLAG_OVERLAPPED;
	NativeHandle result = NativeHandle::Create(port);

	if (not result)
	{
		return std::unexpected(AcquireNetworkError());
	}

	return 1;
}

bool
net::io::Station::TryRegister(net::Socket& socket, std::uintptr_t id, net::ErrorCodes& error_code)
noexcept
{
	if (auto result = Register(socket, id); result)
	{
		return true;
	}
	else
	{
		error_code = std::move(result).error();
		return false;
	}
}

bool
net::io::Station::Destroy()
noexcept
{
	if (auto& handle = GetHandle(); handle)
	{
		const bool result = (1 == handle.Delegate(::CloseHandle));
		myHandle = nullptr;

		return result;
	}
	else
	{
		return false;
	}
}

bool
net::io::Station::Destroy(net::ErrorCodes& error_code)
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
net::io::Station::Schedule(net::io::Context& context, std::uintptr_t id, unsigned long infobytes)
noexcept
{
	return 0 != ::PostQueuedCompletionStatus(GetHandle()
		, std::move(infobytes)
		, std::move(id)
		, reinterpret_cast<::WSAOVERLAPPED*>(std::addressof(context)));
}

bool
net::io::Station::Schedule(net::io::Context* const context, std::uintptr_t id, unsigned long infobytes)
noexcept
{
	return 0 != ::PostQueuedCompletionStatus(GetHandle()
		, std::move(infobytes)
		, std::move(id)
		, reinterpret_cast<::WSAOVERLAPPED*>(context));
}

net::io::Event
net::io::Station::WaitForIoResult()
noexcept
{
	net::io::Event ev_handle{};

	::LPOVERLAPPED overlapped{};
	::BOOL result = 0;
	try
	{
		result = ::GetQueuedCompletionStatus(GetHandle()
			, std::addressof(ev_handle.ioBytes)
			, std::addressof(ev_handle.eventId)
			, std::addressof(overlapped)
			, INFINITE);

		ev_handle.ioContext = reinterpret_cast<net::io::Context*>(overlapped);
		ev_handle.isSucceed = (1 == result);
	}
	catch (...)
	{
		ev_handle.ioContext = nullptr;
		ev_handle.isSucceed = false;
	}

	return ev_handle;
}
