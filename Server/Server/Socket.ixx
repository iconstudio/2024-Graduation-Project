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
		using SocketResult = std::optional<ErrorCode>;
		using SocketTask = iconer::coroutine::Task<SocketResult>;

		// Constructors, Destructors, Assignees

		explicit Socket() noexcept;
		~Socket() noexcept = default;

		// Opt-in Interfaces

		SocketResult Bind(const IpAddress& address, std::uint16_t port) const noexcept;
		SocketResult Bind(IpAddress&& address, std::uint16_t port) const noexcept;
		SocketResult Bind(const EndPoint& endpoint) const noexcept;
		SocketResult Bind(EndPoint&& endpoint) const noexcept;
		SocketResult BindHost(std::uint16_t port) const noexcept;

		bool ReusableAddress() const noexcept;
		void ReusableAddress(bool flag) noexcept;
		bool Close() const noexcept;
		bool Close(ErrorCode& error_code) const noexcept;
		bool CloseAsync(IoContext& context) const noexcept;
		bool CloseAsync(IoContext& context, ErrorCode& error_code) const noexcept;
		bool CloseAsync(IoContext* const context) const noexcept;
		bool CloseAsync(IoContext* const context, ErrorCode& error_code) const noexcept;

		// Opt-out Methods

		SocketResult Open() const noexcept;
		SocketResult Connect(const IpAddress& address, std::uint16_t port) const noexcept;
		SocketResult Connect(IpAddress&& address, std::uint16_t port) const noexcept;
		SocketResult Connect(const EndPoint& endpoint) const noexcept;
		SocketResult Connect(EndPoint&& endpoint) const noexcept;
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

		SocketResult ReserveAccept(IoContext& context, Socket& client) const;
		SocketResult ReserveAccept(IoContext& context, Socket& client, std::span<std::byte> accept_buffer) const;
		SocketResult ReserveAccept(IoContext* const context, Socket& client) const;
		SocketResult ReserveAccept(IoContext* const context, Socket& client, std::span<std::byte> accept_buffer) const;

		// Synchronous Send

		SocketResult Send(std::span<const std::byte> memory) const noexcept;
		SocketResult Send(std::span<const std::byte> memory, size_t size) const noexcept;
		SocketResult Send(_In_reads_bytes_(size)const std::byte* const& memory, size_t size) const noexcept;
		bool Send(std::span<const std::byte> memory, ErrorCode& error_code) const noexcept;
		bool Send(std::span<const std::byte> memory, size_t size, ErrorCode& error_code) const noexcept;
		bool Send(_In_reads_bytes_(size)const std::byte* const& memory, size_t size, ErrorCode& error_code) const noexcept;

		// Maybe asynchronous Send

		SocketResult Send(IoContext& context, std::span<const std::byte> memory) const noexcept;
		SocketResult Send(IoContext& context, std::span<const std::byte> memory, size_t size) const noexcept;
		SocketResult Send(IoContext& context, _In_reads_bytes_(size)const std::byte* const& memory, size_t size) const noexcept;
		bool Send(IoContext& context, std::span<const std::byte> memory, ErrorCode& error_code) const noexcept;
		bool Send(IoContext& context, std::span<const std::byte> memory, size_t size, ErrorCode& error_code) const noexcept;
		bool Send(IoContext& context, _In_reads_bytes_(size)const std::byte* const& memory, size_t size, ErrorCode& error_code) const noexcept;

		// Synchronous Receive

		SocketResult Receive(std::span<std::byte> memory) const noexcept;
		SocketResult Receive(std::span<std::byte> memory, size_t size) const noexcept;
		SocketResult Receive(_In_reads_bytes_(size)std::byte* const& memory, size_t size) const noexcept;
		bool Receive(std::span<std::byte> memory, ErrorCode& error_code) const noexcept;
		bool Receive(std::span<std::byte> memory, size_t size, ErrorCode& error_code) const noexcept;
		bool Receive(_In_reads_bytes_(size)std::byte* const& memory, size_t size, ErrorCode& error_code) const noexcept;

		// Maybe asynchronous Receive

		SocketResult Receive(IoContext& context, std::span<std::byte> memory) const noexcept;
		SocketResult Receive(IoContext& context, std::span<std::byte> memory, size_t size) const noexcept;
		SocketResult Receive(IoContext& context, _In_reads_bytes_(size)std::byte* const& memory, size_t size) const noexcept;
		bool Receive(IoContext& context, std::span<std::byte> memory, ErrorCode& error_code) const noexcept;
		bool Receive(IoContext& context, std::span<std::byte> memory, size_t size, ErrorCode& error_code) const noexcept;
		bool Receive(IoContext& context, _In_reads_bytes_(size)std::byte* const& memory, size_t size, ErrorCode& error_code) const noexcept;

		// Asynchronous Send & Receive

		[[nodiscard]]
		SocketTask MakeSendTask(IoContext& context, std::span<const std::byte> memory) const noexcept;
		[[nodiscard]]
		SocketTask MakeSendTask(IoContext& context, std::span<const std::byte> memory, size_t size) const noexcept;
		[[nodiscard]]
		SocketTask MakeSendTask(IoContext& context, const _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;
		[[nodiscard]]
		SocketTask MakeReceiveTask(IoContext& context, std::span<std::byte> memory) const noexcept;
		[[nodiscard]]
		SocketTask MakeReceiveTask(IoContext& context, std::span<std::byte> memory, size_t size) const noexcept;
		[[nodiscard]]
		SocketTask MakeReceiveTask(IoContext& context, _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;

		[[nodiscard]]
		SocketTask MakeSendTask(const std::shared_ptr<IoContext>& context, std::span<const std::byte> memory) const noexcept;
		[[nodiscard]]
		SocketTask MakeSendTask(const std::shared_ptr<IoContext>& context, std::span<const std::byte> memory, size_t size) const noexcept;
		[[nodiscard]]
		SocketTask MakeSendTask(const std::shared_ptr<IoContext>& context, const _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;
		[[nodiscard]]

		SocketTask MakeReceiveTask(const std::shared_ptr<IoContext>& context, std::span<std::byte> memory) const noexcept;
		[[nodiscard]]
		SocketTask MakeReceiveTask(const std::shared_ptr<IoContext>& context, std::span<std::byte> memory, size_t size) const noexcept;
		[[nodiscard]]
		SocketTask MakeReceiveTask(const std::shared_ptr<IoContext>& context, _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;

		// Asynchronous Send & Receive

		[[nodiscard]]
		SocketTask AsyncSend(IoContext& context, std::span<const std::byte> memory) const noexcept;
		[[nodiscard]]
		SocketTask AsyncSend(IoContext& context, std::span<const std::byte> memory, size_t size) const noexcept;
		[[nodiscard]]
		SocketTask AsyncSend(IoContext& context, const _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;
		[[nodiscard]]
		SocketTask AsyncRecv(IoContext& context, std::span<std::byte> memory) const noexcept;
		[[nodiscard]]
		SocketTask AsyncRecv(IoContext& context, std::span<std::byte> memory, size_t size) const noexcept;
		[[nodiscard]]
		SocketTask AsyncRecv(IoContext& context, _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;

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
		Socket(HandleType sock, InternetProtocol protocol, IpAddressFamily family) noexcept;

		Socket(const Socket&) = delete;
		Socket& operator=(const Socket&) = delete;
	};
}
