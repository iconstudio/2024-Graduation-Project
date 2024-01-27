module;
#include <vector>
#include <array>
#include <thread>
#include <memory>
#include <span>

export module Demo.Framework;
import Iconer.Utility.Logger;
import Iconer.Utility.ColourfulConsole;
import Iconer.Net.ErrorCode;
import Iconer.Net.IoContext;
import Iconer.Net.Socket;
import Iconer.Net.IoCompletionPort;
import Iconer.Application.UserManager;

export namespace demo
{
	class DemoInitializerError : public std::exception
	{
	public:
		using exception::exception;
	};

	class Framework
	{
	public:
		using IdType = iconer::app::UserManager::key_type;

		static inline constexpr std::string_view serverAddress{ "127.0.0.1" };
		static inline constexpr std::uint16_t serverPort{ 40000 };
		static inline constexpr size_t maxUsersNumber = 100;
		static inline constexpr size_t maxRoomsNumber = 500;
		static inline constexpr IdType serverID = 0;
		static inline constexpr IdType beginUserID = 1;
		static inline constexpr IdType beginRoomID = beginUserID + static_cast<IdType>(maxUsersNumber);
		static inline constexpr size_t userRecvSize = 512;
		static inline constexpr size_t workersCount = 6;
		static inline constexpr iconer::util::cfc::Colour sessionIdColor = iconer::util::cfc::colors::LightGreen;

		Framework() = default;
		~Framework() = default;

		void Awake();
		void Start();
		void Update();
		void Destroy();
		void Cleanup();

		void CancelWorkers() noexcept;

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

		[[nodiscard]]
		constexpr std::span<std::byte, userRecvSize>
			GetBuffer(const IdType& id)
			noexcept
		{
			std::byte* buf = this->recvSpace.get();
			auto* data = buf + static_cast<ptrdiff_t>(MakeUidToIndex(id)) * userRecvSize;

			return std::span<std::byte, userRecvSize>{ data, userRecvSize };
		}

		[[nodiscard]]
		constexpr std::span<const std::byte, userRecvSize>
			GetBuffer(const IdType& id)
			const noexcept
		{
			std::byte* buf = recvSpace.get();
			std::byte* data = buf + static_cast<ptrdiff_t>(MakeUidToIndex(id)) * userRecvSize;

			return std::span<const std::byte, userRecvSize>{ data, userRecvSize };
		}

		[[nodiscard]]
		bool IsWorkerCancelled() const noexcept
		{
			return workerCanceller.stop_requested();
		}

		[[nodiscard]]
		static constexpr IdType MakeUidToIndex(const IdType& id) noexcept
		{
			return id - beginUserID;
		}

		[[nodiscard]]
		static constexpr IdType MakeUidToIndex(IdType&& id) noexcept
		{
			return std::move(id) - beginUserID;
		}

		friend void Worker(Framework& framework, size_t nth);
		friend void PacketProcessor(Framework& framework, std::uintptr_t session_raw_id, void* packet_handle, size_t handle_size);
		static void LockPhase() noexcept;
		static void UnlockPhase() noexcept;

	private:
		iconer::net::Socket serverListener;
		iconer::net::IoCompletionPort ioCompletionPort;

		alignas(std::hardware_constructive_interference_size) iconer::app::UserManager userManager;

		alignas(std::hardware_constructive_interference_size) std::unique_ptr<iconer::app::User[]> userSpace;
		alignas(std::hardware_constructive_interference_size) std::unique_ptr<std::byte[]> recvSpace;

		std::vector<std::jthread> serverWorkers;
		std::stop_source workerCanceller;

		iconer::util::Logger myLogger;
	};

	void Worker(Framework& framework, size_t nth);
	void PacketProcessor(Framework& framework, std::uintptr_t session_raw_id, void* packet_handle, size_t handle_size);
}
