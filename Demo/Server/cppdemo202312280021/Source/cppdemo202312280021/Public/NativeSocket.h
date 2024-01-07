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
#include "SocketOptions.h"
#include <span>
#include <coroutine>
#include "NativeSocket.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class [[nodiscard]] EInternetProtocol
{
	Unknown, TCP, UDP
};

USTRUCT(Atomic, BlueprintType, Blueprintable, meta = (DisplayName = "Socket Task Instance"))
struct [[nodiscard]] CPPDEMO202312280021_API FSocketTask
{
	GENERATED_BODY()

public:
	struct promise_type;
	using handle_type = std::coroutine_handle<promise_type>;
	using result_type = Expected<uint32, EErrorCode>;

	struct promise_type
	{
		promise_type() noexcept = default;
		~promise_type() noexcept = default;

		[[nodiscard]]
		FSocketTask get_return_object() noexcept
		{
			return FSocketTask(handle_type::from_promise(*this));
		}

		template<typename U>
		void return_value(U&& value)
		{
			myValue = std::forward<U>(value);
		}

		static constexpr std::suspend_always initial_suspend() noexcept
		{
			return {};
		}

		static constexpr std::suspend_always final_suspend() noexcept
		{
			return {};
		}

		[[noreturn]]
		void unhandled_exception()
		{
			throw;
		}

		result_type myValue;
	};

	constexpr FSocketTask(const handle_type& handle) noexcept
		: myHandle(handle)
	{}

	constexpr FSocketTask(handle_type&& handle) noexcept
		: myHandle(std::move(handle))
	{}

	~FSocketTask() noexcept(noexcept(std::declval<handle_type>().destroy()))
	{
		if (myHandle)
		{
			myHandle.destroy();
		}
	}

	void Start() const;
	void StartAsync() const;

	result_type operator()() const
	{
		this->Start();

		return std::move(myHandle.promise().myValue);
	}

	auto operator co_await() const
	{
		struct awaiter
		{
			static constexpr bool await_ready() noexcept { return true; }
			static constexpr void await_suspend(std::coroutine_handle<void>) noexcept
			{}

			result_type await_resume()
			{
				coHandle();
				return std::move(coHandle.promise().myValue);
			}

			handle_type coHandle;
		};

		return awaiter{ .coHandle = myHandle };
	}

	[[nodiscard]]
	bool IsDone() const noexcept
	{
		return myHandle.done();
	}

	[[nodiscard]]
	constexpr bool operator==(const FSocketTask& other) const noexcept
	{
		return myHandle.address() == other.myHandle.address();
	}

private:
	const static inline std::runtime_error reservedError{ "Cannot acquire a value from the null promise" };

	handle_type myHandle;
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

	SocketResult Bind(const FIpAddress& address, const uint16& port) const noexcept;
	SocketResult Bind(FIpAddress&& address, const uint16& port) const noexcept;
	SocketResult Bind(const FEndpoint& endpoint) const noexcept;
	SocketResult Bind(FEndpoint&& endpoint) const noexcept;
	SocketResult BindHost(const uint16& port) const noexcept;

	bool Close() const noexcept;
	bool Close(EErrorCode& error_code) const noexcept;
	bool CloseAsync(FIoContext& context) const noexcept;
	bool CloseAsync(FIoContext& context, EErrorCode& error_code) const noexcept;
	bool CloseAsync(FIoContext* const context) const noexcept;
	bool CloseAsync(FIoContext* const context, EErrorCode& error_code) const noexcept;

	bool ReusableAddress() const noexcept;
	void ReusableAddress(bool flag) noexcept;

	// Opt-out Methods

	SocketResult Open() const noexcept;
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

	// Synchronous Send

	SocketResult Send(std::span<const uint8> memory) const noexcept;
	SocketResult Send(std::span<const uint8> memory, size_t size) const noexcept;
	SocketResult Send(_In_reads_bytes_(size)const uint8* const& memory, size_t size) const noexcept;
	bool Send(std::span<const uint8> memory, EErrorCode& error_code) const noexcept;
	bool Send(std::span<const uint8> memory, size_t size, EErrorCode& error_code) const noexcept;
	bool Send(_In_reads_bytes_(size)const uint8* const& memory, size_t size, EErrorCode& error_code) const noexcept;

	// Maybe asynchronous Send

	SocketResult Send(FIoContext& context, std::span<const uint8> memory) const noexcept;
	SocketResult Send(FIoContext& context, std::span<const uint8> memory, size_t size) const noexcept;
	SocketResult Send(FIoContext& context, _In_reads_bytes_(size)const uint8* const& memory, size_t size) const noexcept;
	bool Send(FIoContext& context, std::span<const uint8> memory, EErrorCode& error_code) const noexcept;
	bool Send(FIoContext& context, std::span<const uint8> memory, size_t size, EErrorCode& error_code) const noexcept;
	bool Send(FIoContext& context, _In_reads_bytes_(size)const uint8* const& memory, size_t size, EErrorCode& error_code) const noexcept;

	// Synchronous Receive

	SocketResult Receive(std::span<uint8> memory) const noexcept;
	SocketResult Receive(std::span<uint8> memory, size_t size) const noexcept;
	SocketResult Receive(_In_reads_bytes_(size)uint8* const& memory, size_t size) const noexcept;
	bool Receive(std::span<uint8> memory, EErrorCode& error_code) const noexcept;
	bool Receive(std::span<uint8> memory, size_t size, EErrorCode& error_code) const noexcept;
	bool Receive(_In_reads_bytes_(size)uint8* const& memory, size_t size, EErrorCode& error_code) const noexcept;

	// Maybe asynchronous Receive

	SocketResult Receive(FIoContext& context, std::span<uint8> memory) const noexcept;
	SocketResult Receive(FIoContext& context, std::span<uint8> memory, size_t size) const noexcept;
	SocketResult Receive(FIoContext& context, _In_reads_bytes_(size)uint8* const& memory, size_t size) const noexcept;
	bool Receive(FIoContext& context, std::span<uint8> memory, EErrorCode& error_code) const noexcept;
	bool Receive(FIoContext& context, std::span<uint8> memory, size_t size, EErrorCode& error_code) const noexcept;
	bool Receive(FIoContext& context, _In_reads_bytes_(size)uint8* const& memory, size_t size, EErrorCode& error_code) const noexcept;

	// Asynchronous Send & Receive

	[[nodiscard]]
	FSocketTask MakeSendTask(FIoContext& context, std::span<const uint8> memory) const noexcept;
	[[nodiscard]]
	FSocketTask MakeSendTask(FIoContext& context, std::span<const uint8> memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeSendTask(FIoContext& context, const _In_reads_bytes_(size) uint8* const& memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeReceiveTask(FIoContext& context, std::span<uint8> memory) const noexcept;
	[[nodiscard]]
	FSocketTask MakeReceiveTask(FIoContext& context, std::span<uint8> memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeReceiveTask(FIoContext& context, _In_reads_bytes_(size) uint8* const& memory, size_t size) const noexcept;

	[[nodiscard]]
	FSocketTask MakeSendTask(const std::shared_ptr<FIoContext>& context, std::span<const uint8> memory) const noexcept;
	[[nodiscard]]
	FSocketTask MakeSendTask(const std::shared_ptr<FIoContext>& context, std::span<const uint8> memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeSendTask(const std::shared_ptr<FIoContext>& context, const _In_reads_bytes_(size) uint8* const& memory, size_t size) const noexcept;
	[[nodiscard]]

	FSocketTask MakeReceiveTask(const std::shared_ptr<FIoContext>& context, std::span<uint8> memory) const noexcept;
	[[nodiscard]]
	FSocketTask MakeReceiveTask(const std::shared_ptr<FIoContext>& context, std::span<uint8> memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask MakeReceiveTask(const std::shared_ptr<FIoContext>& context, _In_reads_bytes_(size) uint8* const& memory, size_t size) const noexcept;

	// Asynchronous Send & Receive

	[[nodiscard]]
	FSocketTask AsyncSend(FIoContext& context, std::span<const uint8> memory) const noexcept;
	[[nodiscard]]
	FSocketTask AsyncSend(FIoContext& context, std::span<const uint8> memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask AsyncSend(FIoContext& context, const _In_reads_bytes_(size) uint8* const& memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask AsyncRecv(FIoContext& context, std::span<uint8> memory) const noexcept;
	[[nodiscard]]
	FSocketTask AsyncRecv(FIoContext& context, std::span<uint8> memory, size_t size) const noexcept;
	[[nodiscard]]
	FSocketTask AsyncRecv(FIoContext& context, _In_reads_bytes_(size) uint8* const& memory, size_t size) const noexcept;

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
	void SetAddressReusable(const bool flag) const noexcept;
	bool GetAddressReusable() const noexcept;

public:
	// Fields

	UPROPERTY(NoClear, VisibleInstanceOnly, BlueprintReadOnly)
	EInternetProtocol myProtocol;
	UPROPERTY(NoClear, VisibleInstanceOnly, BlueprintReadOnly)
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
	static bool InitializeSocketSystem(const FNativeSocket& fsocket) noexcept;

	UFUNCTION(BlueprintCallable, Category = "Iconer")
	static FNativeSocket CreateNativeSocket(int32 io_type, int32 protocol, int32 family) noexcept;

	UFUNCTION(BlueprintCallable, Category = "Iconer")
	static bool TryCreateNativeSocket(int32 type, int32 protocol, int32 family, FNativeSocket& out, int32& error_code) noexcept;
};

namespace net
{
	using NativeSocket = ::FNativeSocket;
	using InternetProtocol = ::EInternetProtocol;
	using SocketOptions = ::ESocketOptions;
}
