export module Test.Framework;
export import Iconer.Net;
import Iconer.Net.ErrorCode;
import Iconer.Net.IpAddress;
export import Iconer.Net.EndPoint;
export import Iconer.Net.Socket;
import Iconer.Net.IoCompletionPort;
export import Test.IoOperation;
export import Test.Context;
export import Test.ChatMsgContext;
export import Test.Client;
export import Test.Packet;
import <cstdlib>;
import <array>;
import <atomic>;
import <expected>;
import <tuple>;
import <string>;
import <vector>;
import <span>;
import <thread>;
import <optional>;

export namespace test
{
	struct ServerPreset
	{
		std::uintptr_t serverID;
		iconer::net::EndPoint serverAddress;
	};

	struct EncapsuledSocket
	{
		[[nodiscard]]
		inline constexpr friend bool operator<(const EncapsuledSocket& lhs, const EncapsuledSocket& rhs) noexcept
		{
			return lhs.id < rhs.id;
		}

		iconer::net::Socket* sk;
		std::uint64_t id;
	};

	class Framework final
	{
	public:
		using ChatBroadcastingResult = std::expected<unsigned int, std::tuple<iconer::net::ErrorCode, std::uintptr_t>>;
		static constexpr std::size_t maxClientsNumber = 40;
		static constexpr std::size_t sizeRecvBuffer = 256;
		static constexpr std::size_t oneBufferSize = maxClientsNumber * sizeRecvBuffer;
		static constexpr std::uintptr_t clientIdOffset = 1;

		Framework() noexcept;
		~Framework() noexcept;

		/// <summary>
		/// Initialize the framework
		/// </summary>
		/// <param name="setup">Settings of server</param>
		void Awake(ServerPreset&& setup);
		/// <summary>
		/// Start update
		/// </summary>
		/// <param name="concurrent_hint">Number of workers</param>
		void Start(size_t concurrent_hint);
		/// <summary>
		/// Remove framework's resource
		/// </summary>
		void Destroy();
		/// <summary>
		/// Clean every system resources up
		/// </summary>
		void Cleanup();

		iconer::net::Socket::SocketResult ReserveAccept(const std::uintptr_t& id) const;
		bool CloseClient(const std::uintptr_t& id) const;

		iconer::net::Socket::SocketResult OnAccept(const std::uintptr_t& id);
		[[nodiscard]] iconer::net::Socket::SocketResult OnReceive(const std::uintptr_t& id, const size_t& bytes);
		// ChatBroadcastingResult
		[[nodiscard]] size_t OnChat(test::ChatMsgContext* sender);
		iconer::net::Socket::SocketResult OnClose(const std::uintptr_t& id);

		[[nodiscard]]
		constexpr test::Client& FindClient(const std::uintptr_t& id) const
		{
			return *everyClients[GetIndexByID(id)];
		}

		[[nodiscard]]
		static constexpr size_t GetIndexByID(const std::uintptr_t& id) noexcept
		{
			return id - clientIdOffset;
		}

		[[nodiscard]]
		static constexpr std::uintptr_t GetIDByIndex(const size_t& index) noexcept
		{
			return index + clientIdOffset;
		}

	private:
		using data_t = std::vector<EncapsuledSocket>;
		using iterator = data_t::iterator;
		using const_iterator = data_t::const_iterator;
		using view_t = std::span<EncapsuledSocket>;
		using const_view_t = std::span<const EncapsuledSocket>;
		using seek_t = std::ranges::subrange<iterator>;
		using const_seek_t = std::ranges::subrange<const_iterator>;
		using size_type = data_t::size_type;

		void AddSocket(iconer::net::Socket* const& socket_ptr, const std::uintptr_t id);
		[[nodiscard]]
		bool TryAddSocket(iconer::net::Socket* const& socket_ptr, const std::uintptr_t id) noexcept;
		iconer::net::Socket* const AllocateSocket(std::uintptr_t id, iconer::net::IoCategory type, const iconer::net::InternetProtocol& protocol, const iconer::net::IpAddressFamily& family);

		[[nodiscard]]
		bool Schedule(iconer::net::IoContext& context, std::uintptr_t id, unsigned long infobytes) noexcept
		{
			return myStation.Schedule(context, std::move(id), std::move(infobytes));
		}
		[[nodiscard]]
		bool Schedule(iconer::net::IoContext* const context, std::uintptr_t id, unsigned long infobytes) noexcept
		{
			return myStation.Schedule(context, std::move(id), std::move(infobytes));
		}
		[[nodiscard]]
		auto WaitForIoResult() noexcept
		{
			return myStation.WaitForIoResult();
		}

		[[nodiscard]]
		std::span<std::byte, Framework::sizeRecvBuffer>
			GetBuffer(const std::uintptr_t& id)
			noexcept
		{
			std::byte* buf = this->clientsRecvBuffer.data();
			auto* data = buf + GetIndexByID(id) * Framework::sizeRecvBuffer;
			return std::span<std::byte, Framework::sizeRecvBuffer>(data, sizeRecvBuffer);
		}

		[[nodiscard]]
		std::span<const std::byte, Framework::sizeRecvBuffer>
			GetBuffer(const std::uintptr_t& id)
			const noexcept
		{
			const std::byte* buf = clientsRecvBuffer.data();
			auto* data = buf + GetIndexByID(id) * Framework::sizeRecvBuffer;
			return std::span<const std::byte, Framework::sizeRecvBuffer>(data, sizeRecvBuffer);
		}

		friend void Worker(test::Framework&, size_t);

		Framework(const Framework&) = delete;
		Framework(Framework&&) = delete;
		void operator=(const Framework&) = delete;
		void operator=(Framework&&) = delete;

		iconer::net::Socket myListener;
		std::array<test::Client*, test::Framework::maxClientsNumber> everyClients;
		data_t everySockets;
		iconer::net::IoCompletionPort myStation;

		// all-in-one circular buffer
		std::array<std::byte, test::Framework::oneBufferSize> clientsRecvBuffer;
		volatile std::atomic_size_t clientsNumber;
		std::vector<std::jthread> myWorkers;
	};

	void Worker(test::Framework& framework, size_t nth);
}
