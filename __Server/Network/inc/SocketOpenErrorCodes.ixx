export module Net.ErrorCode:Open;
import :General;
import <cstdint>;

export namespace net
{
	enum class SocketOpenErrorCodes : std::int32_t
	{
		NotInitializedSocketSystem = (std::int32_t)ErrorCodes::NotInitializedSocketSystem,
		NetworkIsDown = (std::int32_t)ErrorCodes::NetworkIsDown,
		CannotUseThisAddress = (std::int32_t)ErrorCodes::CannotUseThisAddress,
		YetInProgress = (std::int32_t)ErrorCodes::YetInProgress,
		WSAEINVAL = (std::int32_t)ErrorCodes::WSAEINVAL,
		AlreadyConnected = (std::int32_t)ErrorCodes::WSAEISCONN,
		NotASocket = (std::int32_t)ErrorCodes::NotASocket,
		CouldNotUseThis = (std::int32_t)ErrorCodes::WSAEMFILE,
		NoBufferStorage = (std::int32_t)ErrorCodes::NoBufferStorage,
		NoSupportOperation = (std::int32_t)ErrorCodes::NoSupportOperation
	};
}
