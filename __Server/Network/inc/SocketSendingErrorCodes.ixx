export module Net.ErrorCode:Sending;
import :General;
import <cstdint>;

export namespace net
{
	enum class SendingErrorCodes : std::int32_t
	{
		ConnectionAborted = (std::int32_t)ErrorCodes::ConnectionAborted,
		ConnectionStateReset = (std::int32_t)ErrorCodes::ConnectionStateReset,
		WSAEFAULT = (std::int32_t)ErrorCodes::WSAEFAULT,
		BlockingCallsInterrupted = (std::int32_t)ErrorCodes::BlockingCallsInterrupted,
		YetInProgress = (std::int32_t)ErrorCodes::YetInProgress,
		WSAEINVAL = (std::int32_t)ErrorCodes::WSAEINVAL,
		WSAEMSGSIZE = (std::int32_t)ErrorCodes::WSAEMSGSIZE,
		NetworkIsDown = (std::int32_t)ErrorCodes::NetworkIsDown,
		WSAENETRESET = (std::int32_t)ErrorCodes::WSAENETRESET,
		NoBufferStorage = (std::int32_t)ErrorCodes::NoBufferStorage,
		NotConnected = (std::int32_t)ErrorCodes::NotConnected,
		NotASocket = (std::int32_t)ErrorCodes::NotASocket,
		CannotSend = (std::int32_t)ErrorCodes::NoSupportOperation,
		ClosedSocket = (std::int32_t)ErrorCodes::ClosedSocket,
		NonBlockedOperation = (std::int32_t)ErrorCodes::NonBlockedOperation,
		NotInitializedSocketSystem = (std::int32_t)ErrorCodes::NotInitializedSocketSystem,
		PendedIoOperation = (std::int32_t)ErrorCodes::PendedIoOperation,
		OPERATION_ABORTED = (std::int32_t)ErrorCodes::OPERATION_ABORTED,
	};
}
