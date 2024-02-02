export module Iconer.Net.Socket;
export import :SocketOption;
import Iconer.Utility.Handler;
import Iconer.Utility.Property;
export import Iconer.Net.ErrorCode;
export import Iconer.Net.InternetProtocol;
export import Iconer.Net.IpAddressFamily;
export import Iconer.Net.IoCategory;
export import Iconer.Net.IoContext;
import Iconer.Coroutine.Task;
import <cstdint>;
import <expected>;
import <optional>;
import <span>;

export namespace iconer::net
{
	struct IpAddress;
	struct EndPoint;

	class [[nodiscard]] Socket final : public iconer::util::Handler<std::uintptr_t>
	{
	public:
		// Type members

		using Super = iconer::util::Handler<std::uintptr_t>;
		using FactoryResult = std::expected<Socket, ErrorCode>;
		using ActionResult = std::optional<ErrorCode>;
		using SyncSendResult = std::expected<unsigned long, ErrorCode>;
		using SyncRecvResult = std::expected<int, ErrorCode>;
		using AsyncRecvResult = std::expected<unsigned int, ErrorCode>;
		using SocketTask = iconer::coroutine::Task<ActionResult>;
		using SendTask = iconer::coroutine::Task<SyncSendResult>;
		using RecvTask = iconer::coroutine::Task<AsyncRecvResult>;

		// Constructors, Destructors, Assignees

		explicit Socket() noexcept;
		~Socket() noexcept = default;

		// Opt-in Interfaces

		ActionResult Bind(const IpAddress& address, std::uint16_t port) const noexcept;
		ActionResult Bind(IpAddress&& address, std::uint16_t port) const noexcept;
		ActionResult Bind(const EndPoint& endpoint) const noexcept;
		ActionResult Bind(EndPoint&& endpoint) const noexcept;
		ActionResult BindAny(std::uint16_t port) const noexcept;
		ActionResult BindHost(std::uint16_t port) const noexcept;

		bool ReusableAddress() const noexcept;
		void ReusableAddress(bool flag) noexcept;
		bool Close() const noexcept;
		bool Close(ErrorCode& error_code) const noexcept;
		bool CloseAsync(IoContext& context) const noexcept;
		bool CloseAsync(IoContext& context, ErrorCode& error_code) const noexcept;
		bool CloseAsync(IoContext* const context) const noexcept;
		bool CloseAsync(IoContext* const context, ErrorCode& error_code) const noexcept;

		// Opt-out Methods

		ActionResult Open() const noexcept;
		ActionResult Connect(const IpAddress& address, std::uint16_t port) const noexcept;
		ActionResult Connect(IpAddress&& address, std::uint16_t port) const noexcept;
		ActionResult Connect(const EndPoint& endpoint) const noexcept;
		ActionResult Connect(EndPoint&& endpoint) const noexcept;
		ActionResult ConnectToAny(std::uint16_t port) const noexcept;
		ActionResult ConnectToHost(std::uint16_t port) const noexcept;
		[[nodiscard]]
		SocketTask ConnectAsync(const EndPoint& endpoint) const noexcept;
		[[nodiscard]]
		SocketTask ConnectAsync(EndPoint&& endpoint) const noexcept;
		[[nodiscard]]
		SocketTask ConnectAsync(const IpAddress& address, std::uint16_t port) const noexcept;
		[[nodiscard]]
		SocketTask ConnectAsync(IpAddress&& address, std::uint16_t port) const noexcept;

		// Synchronous Accept

		[[nodiscard]]
		FactoryResult Accept() const noexcept;
		[[nodiscard]]
		FactoryResult Accept(EndPoint& endpoint) const noexcept;

		// Asynchronous Accept

		ActionResult ReserveAccept(IoContext& context, Socket& client) const;
		ActionResult ReserveAccept(IoContext& context, Socket& client, std::span<std::byte> accept_buffer) const;
		ActionResult ReserveAccept(IoContext* const context, Socket& client) const;
		ActionResult ReserveAccept(IoContext* const context, Socket& client, std::span<std::byte> accept_buffer) const;

		// Synchronous Send

		SyncSendResult Send(std::span<const std::byte> memory) const noexcept;
		SyncSendResult Send(std::span<const std::byte> memory, size_t size) const noexcept;
		SyncSendResult Send(_In_reads_bytes_(size)const std::byte* const& memory, size_t size) const noexcept;
		bool Send(std::span<const std::byte> memory, ErrorCode& error_code) const noexcept;
		bool Send(std::span<const std::byte> memory, size_t size, ErrorCode& error_code) const noexcept;
		bool Send(_In_reads_bytes_(size)const std::byte* const& memory, size_t size, ErrorCode& error_code) const noexcept;

		// Maybe asynchronous Send

		SyncSendResult Send(IoContext& context, std::span<const std::byte> memory) const noexcept;
		SyncSendResult Send(IoContext& context, std::span<const std::byte> memory, size_t size) const noexcept;
		SyncSendResult Send(IoContext& context, _In_reads_bytes_(size)const std::byte* const& memory, size_t size) const noexcept;
		bool Send(IoContext& context, std::span<const std::byte> memory, ErrorCode& error_code) const noexcept;
		bool Send(IoContext& context, std::span<const std::byte> memory, size_t size, ErrorCode& error_code) const noexcept;
		bool Send(IoContext& context, _In_reads_bytes_(size)const std::byte* const& memory, size_t size, ErrorCode& error_code) const noexcept;

		// Synchronous Receive

		SyncRecvResult Receive(std::span<std::byte> memory) const noexcept;
		SyncRecvResult Receive(std::span<std::byte> memory, size_t size) const noexcept;
		SyncRecvResult Receive(_In_reads_bytes_(size)std::byte* const& memory, size_t size) const noexcept;
		bool Receive(std::span<std::byte> memory, ErrorCode& error_code) const noexcept;
		bool Receive(std::span<std::byte> memory, size_t size, ErrorCode& error_code) const noexcept;
		bool Receive(_In_reads_bytes_(size)std::byte* const& memory, size_t size, ErrorCode& error_code) const noexcept;

		// Maybe asynchronous Receive

		AsyncRecvResult Receive(IoContext& context, std::span<std::byte> memory) const noexcept;
		AsyncRecvResult Receive(IoContext& context, std::span<std::byte> memory, size_t size) const noexcept;
		AsyncRecvResult Receive(IoContext& context, _In_reads_bytes_(size)std::byte* const& memory, size_t size) const noexcept;
		bool Receive(IoContext& context, std::span<std::byte> memory, ErrorCode& error_code) const noexcept;
		bool Receive(IoContext& context, std::span<std::byte> memory, size_t size, ErrorCode& error_code) const noexcept;
		bool Receive(IoContext& context, _In_reads_bytes_(size)std::byte* const& memory, size_t size, ErrorCode& error_code) const noexcept;

		// Asynchronous Send & Receive

		[[nodiscard]]
		SendTask MakeSendTask(IoContext& context, std::span<const std::byte> memory) const noexcept;
		[[nodiscard]]
		SendTask MakeSendTask(IoContext& context, std::span<const std::byte> memory, size_t size) const noexcept;
		[[nodiscard]]
		SendTask MakeSendTask(IoContext& context, const _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;
		[[nodiscard]]
		RecvTask MakeReceiveTask(IoContext& context, std::span<std::byte> memory) const noexcept;
		[[nodiscard]]
		RecvTask MakeReceiveTask(IoContext& context, std::span<std::byte> memory, size_t size) const noexcept;
		[[nodiscard]]
		RecvTask MakeReceiveTask(IoContext& context, _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;

		[[nodiscard]]
		SendTask MakeSendTask(const std::shared_ptr<IoContext>& context, std::span<const std::byte> memory) const noexcept;
		[[nodiscard]]
		SendTask MakeSendTask(const std::shared_ptr<IoContext>& context, std::span<const std::byte> memory, size_t size) const noexcept;
		[[nodiscard]]
		SendTask MakeSendTask(const std::shared_ptr<IoContext>& context, const _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;
		[[nodiscard]]

		RecvTask MakeReceiveTask(const std::shared_ptr<IoContext>& context, std::span<std::byte> memory) const noexcept;
		[[nodiscard]]
		RecvTask MakeReceiveTask(const std::shared_ptr<IoContext>& context, std::span<std::byte> memory, size_t size) const noexcept;
		[[nodiscard]]
		RecvTask MakeReceiveTask(const std::shared_ptr<IoContext>& context, _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;

		// Asynchronous Send & Receive

		[[nodiscard]]
		SendTask AsyncSend(IoContext& context, std::span<const std::byte> memory) const noexcept;
		[[nodiscard]]
		SendTask AsyncSend(IoContext& context, std::span<const std::byte> memory, size_t size) const noexcept;
		[[nodiscard]]
		SendTask AsyncSend(IoContext& context, const _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;
		[[nodiscard]]
		RecvTask AsyncRecv(IoContext& context, std::span<std::byte> memory) const noexcept;
		[[nodiscard]]
		RecvTask AsyncRecv(IoContext& context, std::span<std::byte> memory, size_t size) const noexcept;
		[[nodiscard]]
		RecvTask AsyncRecv(IoContext& context, _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;

		// Observers

		[[nodiscard]]
		bool IsAvailable() const noexcept;

		// Static methods

		[[nodiscard]]
		static Socket Create(IoCategory type, const InternetProtocol& protocol, const IpAddressFamily& family) noexcept;
		[[nodiscard]]
		static Socket Create(IoCategory type, const InternetProtocol& protocol, const IpAddressFamily& family, ErrorCode& error_code) noexcept;
		[[nodiscard]]
		static bool TryCreate(IoCategory type, const InternetProtocol& protocol, const IpAddressFamily& family, Socket& out) noexcept;
		[[nodiscard]]
		static bool TryCreate(IoCategory type, const InternetProtocol& protocol, const IpAddressFamily& family, Socket& out, ErrorCode& error_code) noexcept;
		[[nodiscard]]
		static FactoryResult TryCreate(IoCategory type, const InternetProtocol& protocol, const IpAddressFamily& family) noexcept;

		[[nodiscard]]
		static Socket CreateTcpSocket(IoCategory type, const IpAddressFamily& family = IpAddressFamily::IPv4) noexcept;
		[[nodiscard]]
		static Socket CreateUdpSocket(IoCategory type, const IpAddressFamily& family = IpAddressFamily::IPv4) noexcept;

		static void SetAddressReusable(Socket& target, bool flag) noexcept;

		// Default methods

		constexpr Socket(Socket&&) noexcept = default;
		constexpr Socket& operator=(Socket&&) noexcept = default;
		[[nodiscard]] constexpr bool operator==(const Socket&) const noexcept = default;

		// Fields

		InternetProtocol myProtocol;
		IpAddressFamily myFamily;
		iconer::util::CustomProperty<bool, Socket> IsAddressReusable;

	private:
		struct ErrorTransfer
		{
			constexpr std::expected<bool, net::ErrorCode> operator()(ErrorCode&& error_code) const noexcept
			{
				errorOutput = std::exchange(error_code, {});
				return false;
			}

			ErrorCode& errorOutput;
		};

		Socket(HandleType sock, InternetProtocol protocol, IpAddressFamily family) noexcept;

		Socket(const Socket&) = delete;
		Socket& operator=(const Socket&) = delete;
	};
}
