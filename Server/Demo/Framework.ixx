module;
#include <utility>
#include <vector>
#include <thread>

export module Demo.Framework;
import Iconer.Utility.Logger;
import Iconer.Net.IoContext;
import Iconer.Net.Socket;
import Iconer.Net.IoCompletionPort;
import Iconer.Application.UserManager;

export class Framework
{
public:
	Framework() = default;
	~Framework() = default;

	void Awake();
	void Start();
	void Update();
	void Destroy();
	void Cleanup();

	[[nodiscard]]
	bool Schedule(iconer::net::IoContext& context, iconer::app::UserManager::key_type id, unsigned long infobytes) noexcept
	{
		return ioCompletionPort.Schedule(context, static_cast<std::uintptr_t>(id), std::move(infobytes));
	}

	[[nodiscard]]
	bool Schedule(iconer::net::IoContext* const context, iconer::app::UserManager::key_type id, unsigned long infobytes) noexcept
	{
		return ioCompletionPort.Schedule(context, static_cast<std::uintptr_t>(id), std::move(infobytes));
	}

	[[nodiscard]]
	auto WaitForIoResult() noexcept
	{
		return ioCompletionPort.WaitForIoResult();
	}

	void CancelWorkers() noexcept
	{
		workerCanceller.request_stop();
	}

	[[nodiscard]]
	bool IsWorkerCancelled() const noexcept
	{
		return workerCanceller.stop_requested();
	}

	friend void Worker(Framework& framework, size_t nth);

private:
	iconer::net::Socket serverListener;
	iconer::net::IoCompletionPort ioCompletionPort;

	iconer::app::UserManager userManager;
	std::vector<std::jthread> serverWorkers;
	std::stop_source workerCanceller;

	iconer::util::Logger myLogger;
};

export void Worker(Framework& framework, size_t nth);
