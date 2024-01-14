#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "CoreMinimal.h"
#include "EndPoint.h"
#include "ErrorCode.h"
#include "Expected.h"
#include "HandleObject.h"
#include "IProperty.h"
#include "IoContext.h"
#include "IoSynchronousType.h"
#include "IpAddressFamily.h"
#include "SocketOptions.h"
#include "SocketTask.h"
#include <span>
#include "NativeSocket.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class [[nodiscard]] EInternetProtocol
{
	Unknown, TCP, UDP
};

USTRUCT(Atomic, BlueprintType, Blueprintable, meta = (DisplayName = "Socket Instance"))
struct [[nodiscard]] CPPDEMO202312280021_API FNativeSocket : public FHandleObject
{
	GENERATED_BODY()

public:
	// Type members

	using FactoryResult = Expected<FNativeSocket, EErrorCode>;
	using SocketResult = Expected<uint32, EErrorCode>;

	FNativeSocket() noexcept;
	FNativeSocket(const uint64& handle, const EInternetProtocol& protocol, const EIpAddressFamily family) noexcept;
	FNativeSocket(const int64& handle, const EInternetProtocol& protocol, const EIpAddressFamily family) noexcept;
	FNativeSocket(uint64&& handle, const EInternetProtocol& protocol, const EIpAddressFamily family) noexcept;
	FNativeSocket(int64&& handle, const EInternetProtocol& protocol, const EIpAddressFamily family) noexcept;
	~FNativeSocket() = default;

	// Opt-in Interfaces

	SocketResult Open() const noexcept;
	bool Close() const noexcept;
	bool Close(EErrorCode& error_code) const noexcept;
	bool CloseAsync(FIoContext& context) const noexcept;
	bool CloseAsync(FIoContext& context, EErrorCode& error_code) const noexcept;
	bool CloseAsync(FIoContext* const context) const noexcept;
	bool CloseAsync(FIoContext* const context, EErrorCode& error_code) const noexcept;

	SocketResult Bind(const FIpAddress& address, const uint16& port) const noexcept;
	SocketResult Bind(FIpAddress&& address, const uint16& port) const noexcept;
	SocketResult Bind(const FEndpoint& endpoint) const noexcept;
	SocketResult Bind(FEndpoint&& endpoint) const noexcept;
	SocketResult BindHost(const uint16& port) const noexcept;

	Expected<std::monostate, EErrorCode> ReusableAddress(bool flag) noexcept;
	bool ReusableAddress() const noexcept;

	// Opt-out Methods

	SocketResult Connect(const FIpAddress& address, const uint16& port) const noexcept;
	SocketResult Connect(FIpAddress&& address, const uint16& port) const noexcept;
	SocketResult Connect(const FEndpoint& endpoint) const noexcept;
	SocketResult Connect(FEndpoint&& endpoint) const noexcept;
	[[nodiscard]]
	FSocketTask ConnectAsync(const FEndpoint& endpoint) const noexcept;
	[[nodiscard]]
	FSocketTask ConnectAsync(FEndpoint&& endpoint) const noexcept;
	[[nodiscard]]
	FSocketTask ConnectAsync(const FIpAddress& address, const uint16& port) const noexcept;
	[[nodiscard]]
	FSocketTask ConnectAsync(FIpAddress&& address, const uint16& port) const noexcept;

	// Synchronous Accept

	[[nodiscard]]
	FactoryResult Accept() const noexcept;
	[[nodiscard]]
	FactoryResult Accept(FEndpoint& endpoint) const noexcept;

	// Asynchronous Accept

	SocketResult ReserveAccept(FIoContext& context, FNativeSocket& client) const;
	SocketResult ReserveAccept(FIoContext& context, FNativeSocket& client, std::span<uint8> accept_buffer) const;
	SocketResult ReserveAccept(FIoContext* const context, FNativeSocket& client) const;
	SocketResult ReserveAccept(FIoContext* const context, FNativeSocket& client, std::span<uint8> accept_buffer) const;
	SocketResult ReserveAccept(FIoContext& context, FNativeSocket& client, const TSharedPtr<uint8>& accept_buffer, size_t size) const;
	SocketResult ReserveAccept(FIoContext* const context, FNativeSocket& client, const TSharedPtr<uint8>& accept_buffer, size_t size) const;

	// Synchronous Send

	SocketResult Send(std::span<const uint8> memory) const noexcept;
	SocketResult Send(std::span<const uint8> memory, size_t size) const noexcept;
	SocketResult Send(_In_reads_bytes_(size)const uint8* const& memory, size_t size) const noexcept;
	bool Send(std::span<const uint8> memory, EErrorCode& error_code) const noexcept;
	bool Send(std::span<const uint8> memory, size_t size, EErrorCode& error_code) const noexcept;
	bool Send(_In_reads_bytes_(size)const uint8* const& memory, size_t size, EErrorCode& error_code) const noexcept;
	SocketResult Send(const TSharedPtr<uint8>& memory, size_t size) const noexcept;
	bool Send(const TSharedPtr<uint8>& memory, size_t size, EErrorCode& error_code) const noexcept;

	// Maybe asynchronous Send

	SocketResult Send(FIoContext& context, std::span<const uint8> memory) const noexcept;
	SocketResult Send(FIoContext& context, std::span<const uint8> memory, size_t size) const noexcept;
	SocketResult Send(FIoContext& context, _In_reads_bytes_(size)const uint8* const& memory, size_t size) const noexcept;
	bool Send(FIoContext& context, std::span<const uint8> memory, EErrorCode& error_code) const noexcept;
	bool Send(FIoContext& context, std::span<const uint8> memory, size_t size, EErrorCode& error_code) const noexcept;
	bool Send(FIoContext& context, _In_reads_bytes_(size)const uint8* const& memory, size_t size, EErrorCode& error_code) const noexcept;
	SocketResult Send(FIoContext& context, const TSharedPtr<uint8>& memory, size_t size) const noexcept;
	bool Send(FIoContext& context, const TSharedPtr<uint8>& memory, size_t size, EErrorCode& error_code) const noexcept;

	// Synchronous Receive

	SocketResult Receive(std::span<uint8> memory) const noexcept;
	SocketResult Receive(std::span<uint8> memory, size_t size) const noexcept;
	SocketResult Receive(_In_reads_bytes_(size)uint8* const& memory, size_t size) const noexcept;
	bool Receive(std::span<uint8> memory, EErrorCode& error_code) const noexcept;
	bool Receive(std::span<uint8> memory, size_t size, EErrorCode& error_code) const noexcept;
	bool Receive(_In_reads_bytes_(size)uint8* const& memory, size_t size, EErrorCode& error_code) const noexcept;
	SocketResult Receive(const TSharedPtr<uint8>& memory, size_t size) const noexcept;
	bool Receive(const TSharedPtr<uint8>& memory, size_t size, EErrorCode& error_code) const noexcept;

	// Maybe asynchronous Receive

	SocketResult Receive(FIoContext& context, std::span<uint8> memory) const noexcept;
	SocketResult Receive(FIoContext& context, std::span<uint8> memory, size_t size) const noexcept;
	SocketResult Receive(FIoContext& context, _In_reads_bytes_(size)uint8* const& memory, size_t size) const noexcept;
	bool Receive(FIoContext& context, std::span<uint8> memory, EErrorCode& error_code) const noexcept;
	bool Receive(FIoContext& context, std::span<uint8> memory, size_t size, EErrorCode& error_code) const noexcept;
	bool Receive(FIoContext& context, _In_reads_bytes_(size)uint8* const& memory, size_t size, EErrorCode& error_code) const noexcept;
	SocketResult Receive(FIoContext& context, const TSharedPtr<uint8>& memory, size_t size) const noexcept;
	bool Receive(FIoContext& context, const TSharedPtr<uint8>& memory, size_t size, EErrorCode& error_code) const noexcept;

	// Asynchronous Send & Receive

	[[nodiscard]]
	FSocketTask MakeSendTask(FIoContext& context, std::span<const uint8> memory) const noexcept;
	[[nodiscard]]
	FSocketTask MakeSendTask(FIoContext& context, std::span<const uint8> memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeSendTask(FIoContext& context, const _In_reads_bytes_(size) uint8* const& memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeSendTask(FIoContext& context, const TSharedPtr<uint8>& memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeReceiveTask(FIoContext& context, std::span<uint8> memory) const noexcept;
	[[nodiscard]]
	FSocketTask MakeReceiveTask(FIoContext& context, std::span<uint8> memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeReceiveTask(FIoContext& context, _In_reads_bytes_(size) uint8* const& memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeReceiveTask(FIoContext& context, const TSharedPtr<uint8>& memory, size_t size) const noexcept;

	[[nodiscard]]
	FSocketTask MakeSendTask(const TSharedPtr<FIoContext>& context, std::span<const uint8> memory) const noexcept;
	[[nodiscard]]
	FSocketTask MakeSendTask(const TSharedPtr<FIoContext>& context, std::span<const uint8> memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeSendTask(const TSharedPtr<FIoContext>& context, const _In_reads_bytes_(size) uint8* const& memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeReceiveTask(const TSharedPtr<FIoContext>& context, std::span<uint8> memory) const noexcept;
	[[nodiscard]]
	FSocketTask MakeReceiveTask(const TSharedPtr<FIoContext>& context, std::span<uint8> memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeReceiveTask(const TSharedPtr<FIoContext>& context, _In_reads_bytes_(size) uint8* const& memory, size_t size) const noexcept;

	// Asynchronous Send & Receive

	[[nodiscard]]
	FSocketTask AsyncSend(FIoContext& context, std::span<const uint8> memory) const noexcept;
	[[nodiscard]]
	FSocketTask AsyncSend(FIoContext& context, std::span<const uint8> memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask AsyncSend(FIoContext& context, const _In_reads_bytes_(size) uint8* const& memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask AsyncSend(FIoContext& context, const TSharedPtr<FIoContext>& memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask AsyncRecv(FIoContext& context, std::span<uint8> memory) const noexcept;
	[[nodiscard]]
	FSocketTask AsyncRecv(FIoContext& context, std::span<uint8> memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask AsyncRecv(FIoContext& context, _In_reads_bytes_(size) uint8* const& memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask AsyncRecv(FIoContext& context, const TSharedPtr<FIoContext>&, size_t size) const noexcept;

	// Observers

	[[nodiscard]]
	bool IsAvailable() const noexcept;

	// Static methods

	[[nodiscard]]
	static FNativeSocket Create(const EIoSynchronousType& type, const EInternetProtocol& protocol, const EIpAddressFamily& family) noexcept;
	[[nodiscard]]
	static FNativeSocket Create(const EIoSynchronousType& type, const EInternetProtocol& protocol, const EIpAddressFamily& family, EErrorCode& error_code) noexcept;
	[[nodiscard]]
	static bool TryCreate(const EIoSynchronousType& type, const EInternetProtocol& protocol, const EIpAddressFamily& family, FNativeSocket& out) noexcept;
	[[nodiscard]]
	static bool TryCreate(const EIoSynchronousType& type, const EInternetProtocol& protocol, const EIpAddressFamily& family, FNativeSocket& out, EErrorCode& error_code) noexcept;
	[[nodiscard]]
	static Expected<FNativeSocket, EErrorCode> TryCreate(const EIoSynchronousType& type, const EInternetProtocol& protocol, const EIpAddressFamily& family) noexcept;

protected:
	static void InternalSetAddressReusable(FNativeSocket& target, bool& flag) noexcept;

public:
	// Fields

	UPROPERTY(NoClear, VisibleInstanceOnly, BlueprintReadOnly, meta = (DisplayName = "Internet Protocol"))
	EInternetProtocol myProtocol;
	UPROPERTY(NoClear, VisibleInstanceOnly, BlueprintReadOnly, meta = (DisplayName = "Internet Address Family"))
	EIpAddressFamily myFamily;
	//UPROPERTY(NoClear, VisibleAnywhere, BlueprintGetter = GetAddressReusable)
	//bool IsAddressReusable;
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

UCLASS(ClassGroup = (Iconer))
class CPPDEMO202312280021_API USocketFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Iconer")
	static bool InitializeSocketFunctions(const FNativeSocket& fsocket) noexcept;

	UFUNCTION(BlueprintCallable, Category = "Iconer")
	static FNativeSocket CreateNativeSocket(int32 io_type, int32 protocol, int32 family) noexcept;

	UFUNCTION(BlueprintCallable, Category = "Iconer")
	static bool TryCreateNativeSocket(int32 type, int32 protocol, int32 family, FNativeSocket& out, int32& error_code) noexcept;
};

namespace net
{
	using NativeSocket = ::FNativeSocket;
	using InternetProtocol = ::EInternetProtocol;
}
