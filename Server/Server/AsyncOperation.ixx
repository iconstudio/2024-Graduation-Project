export module Iconer.Application.AsyncOperation;
import <cstdint>;
import <string>;
import <format>;

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
		OpRecv, OpSend, OpSendBorrowed, OpSendUniqueContext,

		/// <summary>Phase 5 ~ </summary>
		OpReserveRoom, OpCreateRoom, OpEnterRoom, OpLeaveRoom, OpCloseRoom,

		/// <summary>Phase 6 ~ </summary>
		OpNotifyMember, OpNotifyRoom,

		/// <summary>Phase 7 ~ </summary>
		OpCreateGame, OpReadyGame, OpStartGame, OpLeaveGame,

		/// <summary>Phase 10 - Sign out (Quit)</summary>
		OpDisconnect,

		/// <summary>Extras</summary>
		OpEndWorkers
	};
}

export namespace std
{
	[[nodiscard]]
	constexpr string to_string(const iconer::app::AsyncOperations& op)
	{
		using enum iconer::app::AsyncOperations;
		switch (op)
		{
			case None: return "None";
			case OpReserveSession: return "ReserveSession";
			case OpAccept: return "Accept";
			case OpSignIn: return "SignIn";
			case OpSignInFailed: return "SignInFailed";
			case OpAssignID: return "AssignID";
			case OpRecv: return "Recv";
			case OpSend: return "Send";
			case OpCreateRoom: return "CreateRoom";
			case OpEnterRoom: return "EnterRoom";
			case OpLeaveRoom: return "LeaveRoom";
			case OpNotifyMember: return "NotifyMember";
			case OpNotifyRoom: return "OpNotifyroom";
			case OpCreateGame: return "EnterGame";
			case OpReadyGame: return "ReadyGame";
			case OpStartGame: return "StartGame";
			case OpLeaveGame: return "LeaveGame";
			case OpDisconnect: return "Disconnect";
			case OpEndWorkers: return "EndWorkers";
			default: return "Unknown";
		}
	}

	[[nodiscard]]
	constexpr wstring to_wstring(const iconer::app::AsyncOperations& op)
	{
		using enum iconer::app::AsyncOperations;
		switch (op)
		{
			case None: return L"None";
			case OpReserveSession: return L"ReserveSession";
			case OpAccept: return L"Accept";
			case OpSignIn: return L"SignIn";
			case OpSignInFailed: return L"SignInFailed";
			case OpAssignID: return L"AssignID";
			case OpRecv: return L"Recv";
			case OpSend: return L"Send";
			case OpCreateRoom: return L"CreateRoom";
			case OpEnterRoom: return L"EnterRoom";
			case OpLeaveRoom: return L"LeaveRoom";
			case OpNotifyMember: return L"NotifyMember";
			case OpNotifyRoom: return L"OpNotifyroom";
			case OpCreateGame: return L"EnterGame";
			case OpReadyGame: return L"ReadyGame";
			case OpStartGame: return L"StartGame";
			case OpLeaveGame: return L"LeaveGame";
			case OpDisconnect: return L"Disconnect";
			case OpEndWorkers: return L"EndWorkers";
			default: return L"Unknown";
		}
	}
}

export template<>
struct std::formatter<iconer::app::AsyncOperations, char>
{
	static constexpr
		format_parse_context::iterator
		parse(format_parse_context& context)
	{
		return context.begin();
	}

	static format_context::iterator
		format(const iconer::app::AsyncOperations& op, format_context& context)
	{
		using enum iconer::app::AsyncOperations;
		switch (op)
		{
			case None:
			{
				return std::format_to(context.out(), "{}", "No operation");
			}

			case OpReserveSession:
			{
				return std::format_to(context.out(), "{}", "Reserving sessions");
			}

			case OpAccept:
			{
				return std::format_to(context.out(), "{}", "Accepting a sessions");
			}

			case OpSignIn:
			{
				return std::format_to(context.out(), "{}", "A session is signing in");
			}

			case OpSignInFailed:
			{
				return std::format_to(context.out(), "{}", "A session has failed to sign in");
			}

			case OpAssignID:
			{
				return std::format_to(context.out(), "{}", "Assigning id to the session");
			}

			case OpRecv:
			{
				return std::format_to(context.out(), "{}", "Receiving");
			}

			case OpSend:
			{
				return std::format_to(context.out(), "{}", "Sending");
			}

			case OpCreateRoom:
			{
				return std::format_to(context.out(), "{}", "Creating a room");
			}

			case OpEnterRoom:
			{
				return std::format_to(context.out(), "{}", "Entering a room");
			}

			case OpLeaveRoom:
			{
				return std::format_to(context.out(), "{}", "Leaving a room");
			}

			case OpNotifyMember:
			{
				return std::format_to(context.out(), "{}", "Notifying members to the session");
			}

			case OpNotifyRoom:
			{
				return std::format_to(context.out(), "{}", "Notifying room to the session");
			}

			case OpCreateGame:
			{
				return std::format_to(context.out(), "{}", "Entering a game");
			}

			case OpReadyGame:
			{
				return std::format_to(context.out(), "{}", "Getting ready for a game");
			}

			case OpStartGame:
			{
				return std::format_to(context.out(), "{}", "Starting a game");
			}

			case OpLeaveGame:
			{
				return std::format_to(context.out(), "{}", "Leaving a game");
			}

			case OpDisconnect:
			{
				return std::format_to(context.out(), "{}", "A session is disconnecting");
			}

			case OpEndWorkers:
			{
				return std::format_to(context.out(), "{}", "Doom");
			}

			default:
			{
				return std::format_to(context.out(), "{}", "Unknown operation");
			}
		}
	}
};

export template<>
struct std::formatter<iconer::app::AsyncOperations, wchar_t>
{
	static constexpr
		wformat_parse_context::iterator
		parse(wformat_parse_context& context)
	{
		return context.begin();
	}

	static wformat_context::iterator
		format(const iconer::app::AsyncOperations& op, wformat_context& context)
	{
		using enum iconer::app::AsyncOperations;
		switch (op)
		{
			case None:
			{
				return std::format_to(context.out(), L"{}", L"No operation");
			}

			case OpReserveSession:
			{
				return std::format_to(context.out(), L"{}", L"Reserving sessions");
			}

			case OpAccept:
			{
				return std::format_to(context.out(), L"{}", L"Accepting a sessions");
			}

			case OpSignIn:
			{
				return std::format_to(context.out(), L"{}", L"A session is signing in");
			}

			case OpSignInFailed:
			{
				return std::format_to(context.out(), L"{}", L"A session has failed to sign in");
			}

			case OpAssignID:
			{
				return std::format_to(context.out(), L"{}", L"Assigning id to the session");
			}

			case OpRecv:
			{
				return std::format_to(context.out(), L"{}", L"Receiving");
			}

			case OpSend:
			{
				return std::format_to(context.out(), L"{}", L"Sending");
			}

			case OpCreateRoom:
			{
				return std::format_to(context.out(), L"{}", L"Creating a room");
			}

			case OpEnterRoom:
			{
				return std::format_to(context.out(), L"{}", L"Entering a room");
			}

			case OpLeaveRoom:
			{
				return std::format_to(context.out(), L"{}", L"Leaving a room");
			}
			case OpNotifyMember:
			{
				return std::format_to(context.out(), L"{}", L"Notifying members to the session");
			}

			case OpNotifyRoom:
			{
				return std::format_to(context.out(), L"{}", L"Notifying room to the session");
			}

			case OpCreateGame:
			{
				return std::format_to(context.out(), L"{}", L"Entering a game");
			}

			case OpReadyGame:
			{
				return std::format_to(context.out(), L"{}", L"Getting ready for a game");
			}

			case OpStartGame:
			{
				return std::format_to(context.out(), L"{}", L"Starting a game");
			}

			case OpLeaveGame:
			{
				return std::format_to(context.out(), L"{}", L"Leaving a game");
			}

			case OpDisconnect:
			{
				return std::format_to(context.out(), L"{}", L"A session is disconnecting");
			}

			case OpEndWorkers:
			{
				return std::format_to(context.out(), L"{}", L"Doom");
			}

			default:
			{
				return std::format_to(context.out(), L"{}", L"Unknown operation");
			}
		}
	}
};
