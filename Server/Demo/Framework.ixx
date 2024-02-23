module;
#include <vector>
#include <array>
#include <thread>
#include <stop_token>
#include <latch>

export module Demo.Framework;
import Iconer.Utility.Logger;
import Iconer.Utility.ColourfulConsole;
import Iconer.Utility.Concurrency.SpinLock;
import Iconer.Collection.FixedString;
import Iconer.Net.ErrorCode;
import Iconer.Net.IoContext;
import Iconer.Net.Socket;
import Iconer.Net.IoCompletionPort;
import Iconer.Application.IContext;
import Iconer.Application.User;
import Iconer.Application.Room;
import Iconer.Application.ISessionManager;
import Iconer.Application.IContext;
export import <memory>;
export import <expected>;
import <span>;
import <string>;
import <string_view>;

export namespace demo
{
	class DemoInitializerError : public std::exception
	{
	public:
		using exception::exception;
	};

	class FrameworkTaskContext : public iconer::app::IContext
	{
	public:
		using Super = iconer::app::IContext;

		explicit constexpr FrameworkTaskContext() noexcept
			: Super(iconer::app::AsyncOperations::OpEndWorkers)
		{
		}

		~FrameworkTaskContext() = default;
	};

	class Framework
	{
	public:
		using IdType = iconer::app::User::IdType;
		using AcceptResult = iconer::net::Socket::ActionResult;
		using IoResult = iconer::net::Socket::AsyncResult;

		static inline constexpr std::uint16_t lobbySidePort{ 40000 };
		static inline constexpr std::uint16_t gameSidePort{ 40001 };
		static inline constexpr size_t maxUsersNumber = 20;
		static inline constexpr size_t maxUsersInRoomNumber = 6;
		static inline constexpr size_t maxRoomsNumber = maxUsersNumber;
		static inline constexpr IdType lobbyServerID = 0;
		static inline constexpr IdType gameServerID = 1;
		static inline constexpr IdType beginUserID = 2;
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

		[[nodiscard]]
		bool Schedule(iconer::net::IoContext& context, const IdType id, unsigned long info_bytes = 0) noexcept
		{
			return ioCompletionPort.Schedule(context, static_cast<std::uintptr_t>(id), std::move(info_bytes));
		}

		[[nodiscard]]
		bool Schedule(iconer::net::IoContext* const context, const IdType id, unsigned long info_bytes = 0) noexcept
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
		iconer::app::User* FindUser(const IdType& id) const noexcept
		{
			return userManager->operator[](id);
		}

		[[nodiscard]]
		constexpr iconer::app::Room* FindRoom(const IdType& id) const noexcept
		{
			for (auto&& room : everyRoom)
			{
				if (room->GetID() == id)
				{
					return room;
				}
			}

			return nullptr;
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

		/// <summary>On Awake()</summary>
		[[nodiscard]]
		bool CreateListenerSockets() noexcept;
		/// <summary>On Awake()</summary>
		[[nodiscard]]
		bool InitializeLobbyListener() noexcept;
		/// <summary>On Awake()</summary>
		[[nodiscard]]
		bool InitializeGameListener() noexcept;
		/// <summary>On Awake()</summary>
		[[nodiscard]]
		bool InitializeCompletionPort(iconer::net::ErrorCode& error_code) noexcept;
		/// <summary>On Awake()</summary>
		[[nodiscard]]
		bool InitializeUsers();
		/// <summary>On Awake()</summary>
		[[nodiscard]]
		bool InitializeRooms();
		/// <summary>On Start()</summary>
		[[nodiscard]]
		bool StartAccepts();

		[[nodiscard]]
		bool RouteEvent(bool is_succeed, const std::uint64_t& io_id, const ptrdiff_t& io_bytes, iconer::app::IContext* ctx);
		[[nodiscard]]
		AcceptResult OnReserveAccept(iconer::app::User& user);
		[[noreturn]]
		void OnFailedReservingAccept();
		[[nodiscard]]
		IoResult OnUserConnected(iconer::app::User& user);
		void OnFailedUserConnect(iconer::app::User& user);
		[[nodiscard]]
		IoResult OnUserSignedIn(iconer::app::User& user, const ptrdiff_t& bytes);
		void OnFailedUserSignIn(iconer::app::User& user);
		[[nodiscard]]
		IoResult OnNotifyUserId(iconer::app::User& user);
		void OnFailedNotifyId(iconer::app::User& user);
		[[nodiscard]]
		IoResult OnReceived(iconer::app::User& user, const ptrdiff_t& bytes);
		void OnFailedReceive(iconer::app::User& user);
		[[nodiscard]]
		int OnCreatingRoom(iconer::app::Room& room, iconer::app::User& user);
		void OnFailedToCreateRoom(iconer::app::Room& room, iconer::app::User& user, int reason);
		[[nodiscard]]
		int OnJoiningRoom(iconer::app::Room& room, iconer::app::User& user);
		void OnFailedToJoinRoom(iconer::app::Room& room, iconer::app::User& user, int reason);
		bool OnLeavingRoom(iconer::app::User& user);
		[[nodiscard]]
		AcceptResult OnUserDisconnected(iconer::app::User& user);

		// import Iconer.Application.UserManager;
		alignas(std::hardware_constructive_interference_size) iconer::app::ISessionManager<iconer::app::User>* userManager;
		std::array<iconer::app::Room*, Framework::maxRoomsNumber> everyRoom;

		alignas(std::hardware_constructive_interference_size) std::unique_ptr<iconer::app::User[]> userSpace;
		alignas(std::hardware_constructive_interference_size) std::unique_ptr<std::byte[]> recvSpace;

		iconer::util::SpinLock roomsLock;

	private:
		friend void Worker(Framework& framework, size_t nth);
		static void LockPhase() noexcept;
		static void UnlockPhase() noexcept;

		iconer::util::Logger myLogger;
		std::vector<std::jthread> serverWorkers;
		std::latch workerAwakens{ workersCount };
		std::stop_source workerCanceller;

		iconer::net::Socket serverListener;
		iconer::net::Socket gameListener;
		iconer::net::IoCompletionPort ioCompletionPort;
	};

	void Worker(Framework& framework, size_t nth);
}
