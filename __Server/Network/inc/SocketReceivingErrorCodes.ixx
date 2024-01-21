export module Net.ErrorCode:Receiving;
import :General;
import <cstdint>;

export namespace net
{
	enum class ReceivingErrorCodes : std::int32_t
	{
		ConnectionAborted = (std::int32_t)ErrorCodes::ConnectionAborted,
		ConnectionStateReset = (std::int32_t)ErrorCodes::ConnectionStateReset,
		WSAEDISCON = (std::int32_t)ErrorCodes::WSAEDISCON,
		WSAEFAULT = (std::int32_t)ErrorCodes::WSAEFAULT,
		YetInProgress = (std::int32_t)ErrorCodes::YetInProgress,
		BlockingCallsInterrupted = (std::int32_t)ErrorCodes::BlockingCallsInterrupted,
		WSAEINVAL = (std::int32_t)ErrorCodes::WSAEINVAL,
		WSAEMSGSIZE = (std::int32_t)ErrorCodes::WSAEMSGSIZE,
		NetworkIsDown = (std::int32_t)ErrorCodes::NetworkIsDown,
		WSAENETRESET = (std::int32_t)ErrorCodes::WSAENETRESET,
		NoBufferStorage = (std::int32_t)ErrorCodes::NoBufferStorage,
		NotConnected = (std::int32_t)ErrorCodes::NotConnected,
		NotASocket = (std::int32_t)ErrorCodes::NotASocket,
		CannotReceive = (std::int32_t)ErrorCodes::NoSupportOperation,
		ClosedSocket = (std::int32_t)ErrorCodes::ClosedSocket,
		NetworkTimeOut = (std::int32_t)ErrorCodes::NetworkTimeOut,
		NonBlockedOperation = (std::int32_t)ErrorCodes::NonBlockedOperation,
		NotInitializedSocketSystem = (std::int32_t)ErrorCodes::NotInitializedSocketSystem,
		PendedIoOperation = (std::int32_t)ErrorCodes::PendedIoOperation,
		OPERATION_ABORTED = (std::int32_t)ErrorCodes::OPERATION_ABORTED,
	};
}
