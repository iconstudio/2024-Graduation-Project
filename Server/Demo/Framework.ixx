export module Demo.Framework;
import Iconer.Utility.Logger;
import Iconer.Utility.ColourfulConsole;
import Iconer.Net.ErrorCode;
import Iconer.Net.IoContext;
import Iconer.Net.Socket;
import Iconer.Net.IoCompletionPort;
import Iconer.Application.UserManager;
import <memory>;
import <vector>;
import <array>;
import <span>;
import <thread>;
import <latch>;
export import <string>;
export import <string_view>;

export namespace demo
{
	class DemoInitializerError : public std::exception
	{
	public:
		using exception::exception;
	};

	enum class FrameworkTaskCategory
	{
		None, EndTask
	};

	class FrameworkTaskContext : public iconer::net::IoContext
	{
	public:
		FrameworkTaskCategory myCategory;
	};

	class Framework
	{
	public:
		using IdType = iconer::app::UserManager::key_type;
		using SocketResult = iconer::net::Socket::SocketResult;
		using RecvResult = iconer::net::Socket::AsyncRecvResult;

		static inline constexpr std::string_view serverAddress{ "127.0.0.1" };
		static inline constexpr std::uint16_t serverPort{ 40000 };
		static inline constexpr size_t maxUsersNumber = 20;
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

		/// <summary>On Awake()</summary>
		[[nodiscard]]
		bool CreateListenerSocket() noexcept;
		/// <summary>On Awake()</summary>
		[[nodiscard]]
		bool InitializeListener() noexcept;
		/// <summary>On Awake()</summary>
		[[nodiscard]]
		bool InitializeCompletionPort(iconer::net::ErrorCode& error_code) noexcept;
		/// <summary>On Awake()</summary>
		[[nodiscard]]
		bool InitializeUsers();
		/// <summary>On Start()</summary>
		[[nodiscard]]
		bool StartAccepts();

		[[nodiscard]]
		SocketResult OnReserveAccept(iconer::app::User& user, iconer::app::UserStates& transit_state);
		[[nodiscard]]
		RecvResult OnUserConnected(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state);
		[[nodiscard]]
		RecvResult OnReceived(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state, const ptrdiff_t& bytes);
		[[nodiscard]]
		bool OnUserSignIn(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state);
		[[nodiscard]]
		SocketResult OnUserDisconnected(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state);

		[[nodiscard]]
		bool Schedule(iconer::net::IoContext& context, const IdType id, unsigned long info_bytes) noexcept
		{
			return ioCompletionPort.Schedule(context, static_cast<std::uintptr_t>(id), std::move(info_bytes));
		}

		[[nodiscard]]
		bool Schedule(iconer::net::IoContext* const context, const IdType id, unsigned long info_bytes) noexcept
		{
			return ioCompletionPort.Schedule(context, static_cast<std::uintptr_t>(id), std::move(info_bytes));
		}

		[[nodiscard]]
		auto WaitForIoResult() noexcept
		{
			return ioCompletionPort.WaitForIoResult();
		}

		void CancelWorkers() noexcept;

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
		friend ptrdiff_t PacketProcessor(Framework& framework, iconer::app::User& user, const IdType& user_id, iconer::app::UserStates& transit_state, std::span<std::byte, userRecvSize> packet_data, ptrdiff_t last_offset);
		static void LockPhase() noexcept;
		static void UnlockPhase() noexcept;

	private:
		iconer::net::Socket serverListener;
		iconer::net::IoCompletionPort ioCompletionPort;

		alignas(std::hardware_constructive_interference_size) iconer::app::UserManager userManager;

		alignas(std::hardware_constructive_interference_size) std::unique_ptr<iconer::app::User[]> userSpace;
		alignas(std::hardware_constructive_interference_size) std::unique_ptr<std::byte[]> recvSpace;

		std::vector<std::jthread> serverWorkers;
		std::latch workerAwakens{ workersCount };
		std::stop_source workerCanceller;

		iconer::util::Logger myLogger;
	};

	void Worker(Framework& framework, size_t nth);
	ptrdiff_t PacketProcessor(Framework& framework, const iconer::app::User& user, Framework::IdType& user_id, iconer::app::UserStates& transit_state, std::span<std::byte, Framework::userRecvSize> packet_data, ptrdiff_t last_offset);
}
