#include "Socket.h"
#undef min
#undef max

USocket::USocket()
	: myHandle()
	  , DoesReuseAddress(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}

USocket::~USocket()
noexcept
{
	if (myHandle.IsAvailable())
	{
		(void)myHandle.Close();
	}
}

void USocket::Attach(FNativeSocket& native_socket) noexcept
{
	myHandle = MoveTemp(native_socket);
	DoesReuseAddress = myHandle.ReusableAddress();
}

bool
USocket::Connect(const FEndpoint& endpoint)
const noexcept
{
	if (myHandle.IsAvailable())
	{
		return myHandle.Connect(endpoint);
	}
	else
	{
		return false;
	}
}

bool
USocket::ConnectTo(FString ip_address, int32 port)
const noexcept
{
	if (myHandle.IsAvailable())
	{
		return myHandle.Connect(FIpAddress{myHandle.myFamily, ip_address}, static_cast<uint16>(port));
	}
	else
	{
		return false;
	}
}

bool
USocket::Listen()
const noexcept
{
	if (myHandle.IsAvailable())
	{
		return myHandle.Open().HasValue();
	}
	else
	{
		return false;
	}
}

FNativeSocket
USocket::Accept()
const noexcept
{
	if (myHandle.IsAvailable())
	{
		return myHandle.Accept().ValueOr(FNativeSocket{});
	}
	else
	{
		return {};
	}
}

bool
USocket::ReserveAcceptByNativeSocket(FIoContext& context, FNativeSocket& native_socket)
const noexcept
{
	if (myHandle.IsAvailable())
	{
		return myHandle.ReserveAccept(context, native_socket).HasValue();
	}
	else
	{
		return false;
	}
}

bool
USocket::ReserveAccept(FIoContext& context, USocket* const socket_component)
const noexcept
{
	if (myHandle.IsAvailable())
	{
		return myHandle.ReserveAccept(context, socket_component->myHandle).HasValue();
	}
	else
	{
		return false;
	}
}

bool
USocket::Disconnect()
const noexcept
{
	if (myHandle.IsAvailable())
	{
		return myHandle.Close();
	}
	else
	{
		return false;
	}
}

bool
USocket::DisconnectAsync(FIoContext& context)
const noexcept
{
	if (myHandle.IsAvailable())
	{
		return myHandle.CloseAsync(context);
	}
	else
	{
		return false;
	}
}

const
FNativeSocket& USocket::GetNativeHandle()
const noexcept
{
	return myHandle;
}

void
USocket::BeginPlay()
{
	Super::BeginPlay();
}

void
USocket::SetReuseAddress(bool flag)
	noexcept
{
	myHandle.ReusableAddress(flag);

	DoesReuseAddress = flag;
}

bool
USocket::GetReuseAddress()
const noexcept
{
	return myHandle.ReusableAddress();
}

void USocket::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}