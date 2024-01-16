export module Iconer.Network.View;
import Iconer.Declarations;
import Iconer.Utility.RecursiveTemplateClass;
import Net.Constraints;
export import Net.ErrorCode;
import <utility>;

export namespace iconer
{
	class [[nodiscard]] NetworkView
	{
	public:
		constexpr NetworkView() noexcept = default;
		virtual constexpr ~NetworkView() noexcept = default;

#define CONSTRUCT_EVENT(name, ...) virtual constexpr void (name)(##__VA_ARGS__) { }
		CONSTRUCT_EVENT(OnNetworkInitialized, bool succeed, net::ErrorCodes error_code);
		CONSTRUCT_EVENT(OnNetworkDestructed);
		CONSTRUCT_EVENT(OnConnected);
		CONSTRUCT_EVENT(OnConnectionFailed, net::ErrorCodes error_code);
		CONSTRUCT_EVENT(OnDisconnected);
		CONSTRUCT_EVENT(OnRoomCreated, room_id_t room_id);
		CONSTRUCT_EVENT(OnRoomDestroyed, room_id_t room_id);
		CONSTRUCT_EVENT(OnRoomJoined, room_id_t room_id, user_id_t user_id);
		CONSTRUCT_EVENT(OnRoomLeft, user_id_t user_id);
		CONSTRUCT_EVENT(OnGameReady);
		CONSTRUCT_EVENT(OnGameLoadingStarted);
		CONSTRUCT_EVENT(OnGameStarted);
		CONSTRUCT_EVENT(OnGameStartingFailed, int cause);
		CONSTRUCT_EVENT(OnGameEnded, int cause);
		CONSTRUCT_EVENT(OnGameQuit, user_id_t user_id, int cause);

		constexpr NetworkView(const NetworkView&) noexcept = default;
		constexpr NetworkView(NetworkView&&) noexcept = default;
		constexpr NetworkView& operator=(const NetworkView&) noexcept = default;
		constexpr NetworkView& operator=(NetworkView&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const NetworkView&) const noexcept = default;
	};
}
