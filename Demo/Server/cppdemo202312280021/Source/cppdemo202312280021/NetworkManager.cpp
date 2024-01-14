#pragma comment(lib, "Ws2_32.lib")
#include "NetworkManager.h"
#include "Engine/GameEngine.h"
#include "NativeSocket.h"
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <WinSock2.h>
#include <utility>

#define DBG_MSG_VA(fmt, ...) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT(fmt), __VA_ARGS__)); }
#define DBG_ERRMSG_VA(fmt, ...) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(fmt), __VA_ARGS__)); }
#define DBG_OKMSG_VA(fmt, ...) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT(fmt), __VA_ARGS__)); }

#define DBG_MSG(str) DBG_MSG_VA("%s", str)
#define DBG_ERRMSG(str) DBG_ERRMSG_VA("%s", str)
#define DBG_OKMSG(str) DBG_OKMSG_VA("%s", str)

FNativeSocket internalSocket{};
EErrorCode internalErrorCode{};

UNetworkManager::UNetworkManager()
	: IsReady(false), IsConnected(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}

UNetworkManager::~UNetworkManager()
noexcept
{
}

bool UNetworkManager::InitializeNetworkSystem() noexcept
{
	::WSADATA data{};
	if (0 != ::WSAStartup(MAKEWORD(2, 2), std::addressof(data)))
	{
		OnNetworkInitializationFailed();
		return false;
	}

	if (FNativeSocket::TryCreate(EIoSynchronousType::Synchronous, EInternetProtocol::TCP, EIpAddressFamily::IPv4,
	                             internalSocket, internalErrorCode))
	{
		OnNetworkInitialized();
		return true;
	}
	else
	{
		OnNetworkInitializationFailed();
		return false;
	}
}

bool UNetworkManager::CleanupNetworkSystem()
{
	if (0 == ::WSACleanup())
	{
		if (internalSocket.Close())
		{
			OnNetworkDestructed();
			return true;
		}
		else
		{
			OnNetworkDestructionFailed();
			return false;
		}
	}
	else
	{
		OnNetworkDestructionFailed();
		return false;
	}
}

void UNetworkManager::BeginPlay()
{
	Super::BeginPlay();
}

void UNetworkManager::OnNetworkInitialized_Implementation() noexcept
{
	DBG_OKMSG("Network system is initiated");
}

void UNetworkManager::OnNetworkInitializationFailed_Implementation() noexcept
{
	DBG_ERRMSG("Network system has failed on initialization");
}

void UNetworkManager::OnNetworkDestructed_Implementation() noexcept
{
	DBG_OKMSG("Network system has been destructed successfully");
}

void UNetworkManager::OnNetworkDestructionFailed_Implementation() noexcept
{
	DBG_ERRMSG("Network system has been failed on destruction");
}

void UNetworkManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FInternalNetworkWorker::FInternalNetworkWorker(int32 target)
noexcept
	: isCancelled(false)
{
}

FInternalNetworkWorker::~FInternalNetworkWorker()
noexcept
{
}
