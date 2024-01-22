module;
#define NOMINMAX
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
module Net.Io.Schedule;

net::io::Event
net::io::Schedule::WaitForIoResult()
noexcept
{
	net::io::Event ev_handle{};

	::LPOVERLAPPED overlapped{};
	::BOOL result = 0;
	try
	{
		result = ::GetQueuedCompletionStatus(ioHandle
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