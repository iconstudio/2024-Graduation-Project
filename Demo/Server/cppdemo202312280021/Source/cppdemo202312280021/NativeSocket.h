#pragma once
#include "CoreMinimal.h"
#include "HandleObject.h"
#include "IpAddressFamily.h"
#include "IoSynchronousType.h"
#include "EndPoint.h"
#include "IProperty.h"
#include "ErrorCode.h"
#include "IoContext.h"
#include "Expected.h"
#include "NativeSocket.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class [[nodiscard]] EInternetProtocol
{
	Unknown, TCP, UDP
};

UENUM(BlueprintType, Blueprintable)
enum class [[nodiscard]] ESocketOptions
{
	SO_UNKNOWN = 0x0000 UMETA(DisplayName = "Unknown"),
	SO_DEBUG = 0x0001 UMETA(DisplayName = "Debug"),
	SO_REUSEADDR = 0x0004 UMETA(DisplayName = "Recyclable"),
	SO_DONTROUTE = 0x0010 UMETA(DisplayName = "Don't Route"),
	SO_BROADCAST = 0x0020 UMETA(DisplayName = "Broadcast"),
	SO_USELOOPBACK = 0x0040 UMETA(DisplayName = "Use Loopback"),
	SO_LINGER = 0x0080 UMETA(DisplayName = "Linger"),
	TCP_NODELAY = 0x0001 UMETA(DisplayName = "No Delay"),
	SO_DONTLINGER = static_cast<int32>(~0x0080) UMETA(DisplayName = "Don't Linger"),
	SO_KEEPALIVE = 0x0008 UMETA(DisplayName = "Keep Alive"),
	SO_UPDATE_ACCEPT_CONTEXT = 0x700B UMETA(DisplayName = "Update"), // MSWSock.h
};

struct FAttentSocket;

USTRUCT(Atomic, BlueprintType, Blueprintable, meta = (DisplayName = "Native Socket Instance"))
struct [[nodiscard]] CPPDEMO202312280021_API FNativeSocket : public FHandleObject
{
	GENERATED_BODY()

public:
	// Type members

	using FactoryResult = Expected<Socket, EErrorCode>;
	using SocketResult = Expected<uint32, EErrorCode>;

	FNativeSocket() noexcept;
	~FNativeSocket() = default;

	// Opt-in Interfaces

	SocketResult Bind(const IpAddress& address, const std::uint16_t& port) const noexcept;
	SocketResult Bind(IpAddress&& address, const std::uint16_t& port) const noexcept;
	SocketResult Bind(const EndPoint& endpoint) const noexcept;
	SocketResult Bind(EndPoint&& endpoint) const noexcept;
	SocketResult BindHost(const std::uint16_t& port) const noexcept;

	bool ReusableAddress() const noexcept;
	void ReusableAddress(bool flag) noexcept;
	bool Close() const noexcept;
	bool Close(SocketClosingErrorCodes& error_code) const noexcept;
	bool CloseAsync(io::Context& context) const noexcept;
	bool CloseAsync(io::Context& context, SocketClosingErrorCodes& error_code) const noexcept;
	bool CloseAsync(io::Context* const context) const noexcept;
	bool CloseAsync(io::Context* const context, SocketClosingErrorCodes& error_code) const noexcept;

	// Opt-out Methods

	SocketListeningResult Open() const noexcept;
	SocketResult Connect(const IpAddress& address, const std::uint16_t& port) const noexcept;
	SocketResult Connect(IpAddress&& address, const std::uint16_t& port) const noexcept;
	SocketResult Connect(const EndPoint& endpoint) const noexcept;
	SocketResult Connect(EndPoint&& endpoint) const noexcept;
	[[nodiscard]]
	Task<SocketResult> ConnectAsync(const EndPoint& endpoint) const noexcept;
	[[nodiscard]]
	Task<SocketResult> ConnectAsync(EndPoint&& endpoint) const noexcept;
	[[nodiscard]]
	Task<SocketResult> ConnectAsync(const IpAddress& address, const std::uint16_t& port) const noexcept;
	[[nodiscard]]
	Task<SocketResult> ConnectAsync(IpAddress&& address, const std::uint16_t& port) const noexcept;

	// Synchronous Accept

	[[nodiscard]]
	AcceptingResult Accept() const noexcept;
	[[nodiscard]]
	AcceptingResult Accept(EndPoint& endpoint) const noexcept;

	// Asynchronous Accept

	SocketResult ReserveAccept(io::Context& context, Socket& client) const;
	SocketResult ReserveAccept(io::Context& context, Socket& client, std::span<std::byte> accept_buffer) const;
	SocketResult ReserveAccept(io::Context* const context, Socket& client) const;
	SocketResult ReserveAccept(io::Context* const context, Socket& client, std::span<std::byte> accept_buffer) const;

	// Synchronous Send

	SocketSendingResult Send(std::span<const std::byte> memory) const noexcept;
	SocketSendingResult Send(std::span<const std::byte> memory, size_t size) const noexcept;
	SocketSendingResult Send(_In_reads_bytes_(size)const std::byte* const& memory, size_t size) const noexcept;
	bool Send(std::span<const std::byte> memory, SendingErrorCodes& error_code) const noexcept;
	bool Send(std::span<const std::byte> memory, size_t size, SendingErrorCodes& error_code) const noexcept;
	bool Send(_In_reads_bytes_(size)const std::byte* const& memory, size_t size, SendingErrorCodes& error_code) const noexcept;

	// Maybe asynchronous Send

	SocketSendingResult Send(io::Context& context, std::span<const std::byte> memory) const noexcept;
	SocketSendingResult Send(io::Context& context, std::span<const std::byte> memory, size_t size) const noexcept;
	SocketSendingResult Send(io::Context& context, _In_reads_bytes_(size)const std::byte* const& memory, size_t size) const noexcept;
	bool Send(io::Context& context, std::span<const std::byte> memory, SendingErrorCodes& error_code) const noexcept;
	bool Send(io::Context& context, std::span<const std::byte> memory, size_t size, SendingErrorCodes& error_code) const noexcept;
	bool Send(io::Context& context, _In_reads_bytes_(size)const std::byte* const& memory, size_t size, SendingErrorCodes& error_code) const noexcept;

	// Synchronous Receive

	SocketReceivingResult Receive(std::span<std::byte> memory) const noexcept;
	SocketReceivingResult Receive(std::span<std::byte> memory, size_t size) const noexcept;
	SocketReceivingResult Receive(_In_reads_bytes_(size)std::byte* const& memory, size_t size) const noexcept;
	bool Receive(std::span<std::byte> memory, ReceivingErrorCodes& error_code) const noexcept;
	bool Receive(std::span<std::byte> memory, size_t size, ReceivingErrorCodes& error_code) const noexcept;
	bool Receive(_In_reads_bytes_(size)std::byte* const& memory, size_t size, ReceivingErrorCodes& error_code) const noexcept;

	// Maybe asynchronous Receive

	SocketReceivingResult Receive(io::Context& context, std::span<std::byte> memory) const noexcept;
	SocketReceivingResult Receive(io::Context& context, std::span<std::byte> memory, size_t size) const noexcept;
	SocketReceivingResult Receive(io::Context& context, _In_reads_bytes_(size)std::byte* const& memory, size_t size) const noexcept;
	bool Receive(io::Context& context, std::span<std::byte> memory, ReceivingErrorCodes& error_code) const noexcept;
	bool Receive(io::Context& context, std::span<std::byte> memory, size_t size, ReceivingErrorCodes& error_code) const noexcept;
	bool Receive(io::Context& context, _In_reads_bytes_(size)std::byte* const& memory, size_t size, ReceivingErrorCodes& error_code) const noexcept;

	// Asynchronous Send & Receive

	[[nodiscard]]
	Task<SocketSendingResult> MakeSendTask(io::Context& context, std::span<const std::byte> memory) const noexcept;
	[[nodiscard]]
	Task<SocketSendingResult> MakeSendTask(io::Context& context, std::span<const std::byte> memory, size_t size) const noexcept;
	[[nodiscard]]
	Task<SocketSendingResult> MakeSendTask(io::Context& context, const _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;
	[[nodiscard]]
	Task<SocketReceivingResult> MakeReceiveTask(io::Context& context, std::span<std::byte> memory) const noexcept;
	[[nodiscard]]
	Task<SocketReceivingResult> MakeReceiveTask(io::Context& context, std::span<std::byte> memory, size_t size) const noexcept;
	[[nodiscard]]
	Task<SocketReceivingResult> MakeReceiveTask(io::Context& context, _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;

	[[nodiscard]]
	Task<SocketSendingResult> MakeSendTask(const std::shared_ptr<io::Context>& context, std::span<const std::byte> memory) const noexcept;
	[[nodiscard]]
	Task<SocketSendingResult> MakeSendTask(const std::shared_ptr<io::Context>& context, std::span<const std::byte> memory, size_t size) const noexcept;
	[[nodiscard]]
	Task<SocketSendingResult> MakeSendTask(const std::shared_ptr<io::Context>& context, const _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;
	[[nodiscard]]

	Task<SocketReceivingResult> MakeReceiveTask(const std::shared_ptr<io::Context>& context, std::span<std::byte> memory) const noexcept;
	[[nodiscard]]
	Task<SocketReceivingResult> MakeReceiveTask(const std::shared_ptr<io::Context>& context, std::span<std::byte> memory, size_t size) const noexcept;
	[[nodiscard]]
	Task<SocketReceivingResult> MakeReceiveTask(const std::shared_ptr<io::Context>& context, _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;

	// Asynchronous Send & Receive

	[[nodiscard]]
	Task<SocketSendingResult> AsyncSend(io::Context& context, std::span<const std::byte> memory) const noexcept;
	[[nodiscard]]
	Task<SocketSendingResult> AsyncSend(io::Context& context, std::span<const std::byte> memory, size_t size) const noexcept;
	[[nodiscard]]
	Task<SocketSendingResult> AsyncSend(io::Context& context, const _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;
	[[nodiscard]]
	Task<SocketReceivingResult> AsyncRecv(io::Context& context, std::span<std::byte> memory) const noexcept;
	[[nodiscard]]
	Task<SocketReceivingResult> AsyncRecv(io::Context& context, std::span<std::byte> memory, size_t size) const noexcept;
	[[nodiscard]]
	Task<SocketReceivingResult> AsyncRecv(io::Context& context, _In_reads_bytes_(size) std::byte* const& memory, size_t size) const noexcept;

	// Observers

	[[nodiscard]]
	bool IsAvailable() const noexcept;

	// Static methods

	[[nodiscard]]
	static FNativeSocket Create(EIoSynchronousType type, const EInternetProtocol& protocol, const EIpAddressFamily& family) noexcept;
	[[nodiscard]]
	static FNativeSocket Create(EIoSynchronousType type, const EInternetProtocol& protocol, const EIpAddressFamily& family, EErrorCode& error_code) noexcept;
	[[nodiscard]]
	static bool TryCreate(EIoSynchronousType type, const EInternetProtocol& protocol, const EIpAddressFamily& family, FAttentSocket& out) noexcept;
	[[nodiscard]]
	static bool TryCreate(EIoSynchronousType type, const EInternetProtocol& protocol, const EIpAddressFamily& family, FAttentSocket& out, EErrorCode& error_code) noexcept;
	[[nodiscard]]
	static Expected<FNativeSocket, EErrorCode> TryCreate(EIoSynchronousType type, const EInternetProtocol& protocol, const EIpAddressFamily& family) noexcept;

protected:
	static void InternalSetAddressReusable(FNativeSocket& target, bool& flag) noexcept;
	void SetAddressReusable(const bool flag) noexcept;
	bool GetAddressReusable() const noexcept;

public:
	// Fields

	UPROPERTY(NoClear, VisibleInstanceOnly, BlueprintReadOnly)
	EInternetProtocol myProtocol;
	UPROPERTY(NoClear, VisibleInstanceOnly, BlueprintReadOnly)
	EIpAddressFamily myFamily;
	//UPROPERTY(NoClear, VisibleAnywhere, BlueprintGetter = GetAddressReusable)
	//bool IsAddressReusable;

	friend struct AttentSocket;

protected:
};

USTRUCT(Atomic, BlueprintType, Blueprintable, meta = (DisplayName = "Native Socket Wrapper"))
struct [[nodiscard]] CPPDEMO202312280021_API FAttentSocket
{
	GENERATED_BODY()

public:
	UPROPERTY(NoClear, EditInstanceOnly, BlueprintReadWrite)
	FNativeSocket Socket;
};

template<>
struct std::hash<FNativeSocket>
{
	[[nodiscard]]
	size_t operator()(const FNativeSocket& sk) const noexcept
	{
		static const std::hash<int64> hasher{};

		return hasher(sk.GetHandle());
	}
};

namespace net
{
	using NativeSocket = ::FNativeSocket;
	using InternetProtocol = ::EInternetProtocol;
	using SocketOptions = ::ESocketOptions;
}
