export module Iconer.Application.AsyncOperation;
import <cstdint>;

export namespace iconer::app
{
	enum class [[nodiscard]] AsyncOperations : std::uint8_t
	{
		None,

		/// <summary>Phase 0</summary>
		OpReserveSession = 10,

		/// <summary>Phase 1</summary>
		OpAccept,

		/// <summary>Phase 2 - Sign in</summary>
		OpSignIn, OpSignInFailed,

		/// <summary>Phase 3</summary>
		OpAssignID,

		/// <summary>Phase 4 ~ </summary>
		OpRecv, OpSend,

		/// <summary>Phase 5 ~ </summary>
		OpCreateRoom, OpEnterRoom, OpLeaveRoom,

		/// <summary>Phase 6 ~ </summary>
		OpNotifyMember, OpEnterGame, OpReadyGame, OpStartGame, OpLeaveGame,

		/// <summary>Phase 10 - Sign out (Quit)</summary>
		OpDisconnect,

		/// <summary>Extras</summary>
		OpEndWorkers
	};
}
