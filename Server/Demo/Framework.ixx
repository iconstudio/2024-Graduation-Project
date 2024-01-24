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
import Iconer.Net.Socket;
import <memory>;
import <span>;

export class Framework
{
public:
	using IdType = iconer::app::UserManager::key_type;

	static inline constexpr size_t userRecvSize = 512;
	static inline constexpr size_t workersCount = 6;
	static inline constexpr size_t userNumber = 3000;
	static inline constexpr IdType beginUserID = 1;

	Framework() = default;
	~Framework() = default;

	void Awake();
	void Start();
	void Update();
	void Destroy();
	void Cleanup();

	[[nodiscard]]
	bool Schedule(iconer::net::IoContext& context, const IdType id, unsigned long infobytes) noexcept
	{
		return ioCompletionPort.Schedule(context, static_cast<std::uintptr_t>(id), std::move(infobytes));
	}

	[[nodiscard]]
	bool Schedule(iconer::net::IoContext* const context, const IdType id, unsigned long infobytes) noexcept
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
	constexpr std::span<std::byte, userRecvSize>
		GetBuffer(const IdType& id)
		noexcept
	{
		std::byte* buf = this->recvBuffer.get();
		auto* data = buf + static_cast<ptrdiff_t>(id - beginUserID) * userRecvSize;

		return std::span<std::byte, userRecvSize>{ data, userRecvSize };
	}

	[[nodiscard]]
	constexpr std::span<const std::byte, userRecvSize>
		GetBuffer(const IdType& id)
		const noexcept
	{
		std::byte* buf = recvBuffer.get();
		std::byte* data = buf + static_cast<ptrdiff_t>(id - beginUserID) * userRecvSize;

		return std::span<const std::byte, userRecvSize>{ data, userRecvSize };
	}

	[[nodiscard]]
	bool IsWorkerCancelled() const noexcept
	{
		return workerCanceller.stop_requested();
	}

	friend void Worker(Framework& framework, size_t nth);
	friend void PacketProcessor(Framework& framework, std::uintptr_t session_raw_id, void* packet_handle, size_t handle_size);

private:
	iconer::net::Socket serverListener;
	iconer::net::IoCompletionPort ioCompletionPort;

	iconer::app::UserManager userManager;
	std::vector<std::jthread> serverWorkers;
	std::stop_source workerCanceller;

	std::unique_ptr<std::byte[]> recvBuffer;

	iconer::util::Logger myLogger;
};

export void Worker(Framework& framework, size_t nth);
export void PacketProcessor(Framework& framework, std::uintptr_t session_raw_id, void* packet_handle, size_t handle_size);
