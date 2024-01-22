export module Net.ErrorCode:Closing;
import :General;
import <cstdint>;

export namespace net
{
	enum class SocketClosingErrorCodes : std::int32_t
	{
		NotInitializedSocketSystem = (std::int32_t)ErrorCodes::NotInitializedSocketSystem,
		NetworkIsDown = (std::int32_t)ErrorCodes::NetworkIsDown,
		NotASocket = (std::int32_t)ErrorCodes::NotASocket,
		YetInProgress = (std::int32_t)ErrorCodes::YetInProgress,
		BlockingCallsInterrupted = (std::int32_t)ErrorCodes::BlockingCallsInterrupted,
		NonBlockedOperation = (std::int32_t)ErrorCodes::NonBlockedOperation,
	};
}
