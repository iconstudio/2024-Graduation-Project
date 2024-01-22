module;
#include <array>
#include <atomic>

export module Test.Framework;
import <cstdlib>;
import <expected>;
import <tuple>;
import <string>;
import <vector>;
import <span>;
import <thread>;

import Net;
import Net.IpAddress;
export import Net.EndPoint;
export import Net.Socket;
export import Net.SocketPool;
export import Net.IpAddress.IPv4;

export import Test.IoOperation;
export import Test.Context;
export import Test.ChatMsgContext;
export import Test.Client;
export import Test.Packet;

export namespace test
{
	struct ServerPreset
	{
		std::uintptr_t serverID;
		net::EndPoint serverAddress{ net::EndPoint::EmptyEndPoint };
	};

	class Framework final
	{
	public:
		using ChatBroadcastingResult = std::expected<unsigned int, std::tuple<net::SendingErrorCodes, std::uintptr_t>>;
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

		net::SocketResult ReserveAccept(const std::uintptr_t& id) const;
		bool CloseClient(const std::uintptr_t& id) const;

		net::SocketReceivingResult OnAccept(const std::uintptr_t& id);
		[[nodiscard]] net::SocketReceivingResult OnReceive(const std::uintptr_t& id, const size_t& bytes);
		// ChatBroadcastingResult
		[[nodiscard]] size_t OnChat(test::ChatMsgContext* sender);
		net::SocketResult OnClose(const std::uintptr_t& id);

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

		net::Socket myListener;
		std::array<test::Client*, test::Framework::maxClientsNumber> everyClients;
		net::SocketPool everySockets;
		// all-in-one circular buffer
		std::array<std::byte, test::Framework::oneBufferSize> clientsRecvBuffer;
		volatile std::atomic_size_t clientsNumber;
		std::vector<std::jthread> myWorkers{};
	};

	void Worker(test::Framework& framework, size_t nth);
}
