export module Net.ErrorCode:Option;
import :General;
import <cstdint>;

export namespace net
{
	enum class SocketOptionErrorCodes : std::int32_t
	{
		NotInitializedSocketSystem = (std::int32_t)ErrorCodes::NotInitializedSocketSystem,
		NetworkIsDown = (std::int32_t)ErrorCodes::NetworkIsDown,
		BlockingCallsInterrupted = (std::int32_t)ErrorCodes::BlockingCallsInterrupted,

		InvalidBuffer = (std::int32_t)ErrorCodes::WSAEFAULT,
		InvalidValueParameters = (std::int32_t)ErrorCodes::WSAEINVAL,
		YetInProgress = (std::int32_t)ErrorCodes::YetInProgress,
		WSAENETRESET = (std::int32_t)ErrorCodes::WSAENETRESET,
		WSAENOPROTOOPT = (std::int32_t)ErrorCodes::WSAENOPROTOOPT,
		NotConnected = (std::int32_t)ErrorCodes::NotConnected,
		NotASocket = (std::int32_t)ErrorCodes::NotASocket,
	};
}
