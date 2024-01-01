#pragma once
#include "CoreMinimal.h"
#include "HandleObject.h"
#include "IpAddressFamily.h"
#include "IoSynchronousType.h"
#include "EndPoint.h"
#include "IProperty.h"
#include "ErrorCode.h"
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
	FNativeSocket() noexcept;
	~FNativeSocket() = default;

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
	void SetAddressReusable(FNativeSocket& target, bool& flag) noexcept;
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

USTRUCT(Atomic, BlueprintType)
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
