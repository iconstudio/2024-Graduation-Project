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
		OpRecv, OpSend, OpSendBorrowed,

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
		switch (op)
		{
			case iconer::app::AsyncOperations::None: return "None";
			case iconer::app::AsyncOperations::OpReserveSession: return "ReserveSession";
			case iconer::app::AsyncOperations::OpAccept: return "Accept";
			case iconer::app::AsyncOperations::OpSignIn: return "SignIn";
			case iconer::app::AsyncOperations::OpSignInFailed: return "SignInFailed";
			case iconer::app::AsyncOperations::OpAssignID: return "AssignID";
			case iconer::app::AsyncOperations::OpRecv: return "Recv";
			case iconer::app::AsyncOperations::OpSend: return "Send";
			case iconer::app::AsyncOperations::OpCreateRoom: return "CreateRoom";
			case iconer::app::AsyncOperations::OpEnterRoom: return "EnterRoom";
			case iconer::app::AsyncOperations::OpLeaveRoom: return "LeaveRoom";
			case iconer::app::AsyncOperations::OpNotifyMember: return "NotifyMember";
			case iconer::app::AsyncOperations::OpNotifyRoom: return "OpNotifyroom";
			case iconer::app::AsyncOperations::OpCreateGame: return "EnterGame";
			case iconer::app::AsyncOperations::OpReadyGame: return "ReadyGame";
			case iconer::app::AsyncOperations::OpStartGame: return "StartGame";
			case iconer::app::AsyncOperations::OpLeaveGame: return "LeaveGame";
			case iconer::app::AsyncOperations::OpDisconnect: return "Disconnect";
			case iconer::app::AsyncOperations::OpEndWorkers: return "EndWorkers";
			default: return "Unknown";
		}
	}

	[[nodiscard]]
	constexpr wstring to_wstring(const iconer::app::AsyncOperations& op)
	{
		switch (op)
		{
			case iconer::app::AsyncOperations::None: return L"None";
			case iconer::app::AsyncOperations::OpReserveSession: return L"ReserveSession";
			case iconer::app::AsyncOperations::OpAccept: return L"Accept";
			case iconer::app::AsyncOperations::OpSignIn: return L"SignIn";
			case iconer::app::AsyncOperations::OpSignInFailed: return L"SignInFailed";
			case iconer::app::AsyncOperations::OpAssignID: return L"AssignID";
			case iconer::app::AsyncOperations::OpRecv: return L"Recv";
			case iconer::app::AsyncOperations::OpSend: return L"Send";
			case iconer::app::AsyncOperations::OpCreateRoom: return L"CreateRoom";
			case iconer::app::AsyncOperations::OpEnterRoom: return L"EnterRoom";
			case iconer::app::AsyncOperations::OpLeaveRoom: return L"LeaveRoom";
			case iconer::app::AsyncOperations::OpNotifyMember: return L"NotifyMember";
			case iconer::app::AsyncOperations::OpNotifyRoom: return L"OpNotifyroom";
			case iconer::app::AsyncOperations::OpCreateGame: return L"EnterGame";
			case iconer::app::AsyncOperations::OpReadyGame: return L"ReadyGame";
			case iconer::app::AsyncOperations::OpStartGame: return L"StartGame";
			case iconer::app::AsyncOperations::OpLeaveGame: return L"LeaveGame";
			case iconer::app::AsyncOperations::OpDisconnect: return L"Disconnect";
			case iconer::app::AsyncOperations::OpEndWorkers: return L"EndWorkers";
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
		switch (op)
		{
			case iconer::app::AsyncOperations::None:
			{
				return std::format_to(context.out(), "{}", "No operation");
			}

			case iconer::app::AsyncOperations::OpReserveSession:
			{
				return std::format_to(context.out(), "{}", "Reserving sessions");
			}

			case iconer::app::AsyncOperations::OpAccept:
			{
				return std::format_to(context.out(), "{}", "Accepting a sessions");
			}

			case iconer::app::AsyncOperations::OpSignIn:
			{
				return std::format_to(context.out(), "{}", "A session is signing in");
			}

			case iconer::app::AsyncOperations::OpSignInFailed:
			{
				return std::format_to(context.out(), "{}", "A session has failed to sign in");
			}

			case iconer::app::AsyncOperations::OpAssignID:
			{
				return std::format_to(context.out(), "{}", "Assigning id to the session");
			}

			case iconer::app::AsyncOperations::OpRecv:
			{
				return std::format_to(context.out(), "{}", "Receiving");
			}

			case iconer::app::AsyncOperations::OpSend:
			{
				return std::format_to(context.out(), "{}", "Sending");
			}

			case iconer::app::AsyncOperations::OpCreateRoom:
			{
				return std::format_to(context.out(), "{}", "Creating a room");
			}

			case iconer::app::AsyncOperations::OpEnterRoom:
			{
				return std::format_to(context.out(), "{}", "Entering a room");
			}

			case iconer::app::AsyncOperations::OpLeaveRoom:
			{
				return std::format_to(context.out(), "{}", "Leaving a room");
			}

			case iconer::app::AsyncOperations::OpNotifyMember:
			{
				return std::format_to(context.out(), "{}", "Notifying members to the session");
			}
			
			case iconer::app::AsyncOperations::OpNotifyRoom:
			{
				return std::format_to(context.out(), "{}", "Notifying room to the session");
			}

			case iconer::app::AsyncOperations::OpCreateGame:
			{
				return std::format_to(context.out(), "{}", "Entering a game");
			}

			case iconer::app::AsyncOperations::OpReadyGame:
			{
				return std::format_to(context.out(), "{}", "Getting ready for a game");
			}

			case iconer::app::AsyncOperations::OpStartGame:
			{
				return std::format_to(context.out(), "{}", "Starting a game");
			}

			case iconer::app::AsyncOperations::OpLeaveGame:
			{
				return std::format_to(context.out(), "{}", "Leaving a game");
			}

			case iconer::app::AsyncOperations::OpDisconnect:
			{
				return std::format_to(context.out(), "{}", "A session is disconnecting");
			}

			case iconer::app::AsyncOperations::OpEndWorkers:
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
		switch (op)
		{
			case iconer::app::AsyncOperations::None:
			{
				return std::format_to(context.out(), L"{}", L"No operation");
			}

			case iconer::app::AsyncOperations::OpReserveSession:
			{
				return std::format_to(context.out(), L"{}", L"Reserving sessions");
			}

			case iconer::app::AsyncOperations::OpAccept:
			{
				return std::format_to(context.out(), L"{}", L"Accepting a sessions");
			}

			case iconer::app::AsyncOperations::OpSignIn:
			{
				return std::format_to(context.out(), L"{}", L"A session is signing in");
			}

			case iconer::app::AsyncOperations::OpSignInFailed:
			{
				return std::format_to(context.out(), L"{}", L"A session has failed to sign in");
			}

			case iconer::app::AsyncOperations::OpAssignID:
			{
				return std::format_to(context.out(), L"{}", L"Assigning id to the session");
			}

			case iconer::app::AsyncOperations::OpRecv:
			{
				return std::format_to(context.out(), L"{}", L"Receiving");
			}

			case iconer::app::AsyncOperations::OpSend:
			{
				return std::format_to(context.out(), L"{}", L"Sending");
			}

			case iconer::app::AsyncOperations::OpCreateRoom:
			{
				return std::format_to(context.out(), L"{}", L"Creating a room");
			}

			case iconer::app::AsyncOperations::OpEnterRoom:
			{
				return std::format_to(context.out(), L"{}", L"Entering a room");
			}

			case iconer::app::AsyncOperations::OpLeaveRoom:
			{
				return std::format_to(context.out(), L"{}", L"Leaving a room");
			}
			case iconer::app::AsyncOperations::OpNotifyMember:
			{
				return std::format_to(context.out(), L"{}", L"Notifying members to the session");
			}

			case iconer::app::AsyncOperations::OpNotifyRoom:
			{
				return std::format_to(context.out(), L"{}", L"Notifying room to the session");
			}

			case iconer::app::AsyncOperations::OpCreateGame:
			{
				return std::format_to(context.out(), L"{}", L"Entering a game");
			}

			case iconer::app::AsyncOperations::OpReadyGame:
			{
				return std::format_to(context.out(), L"{}", L"Getting ready for a game");
			}

			case iconer::app::AsyncOperations::OpStartGame:
			{
				return std::format_to(context.out(), L"{}", L"Starting a game");
			}

			case iconer::app::AsyncOperations::OpLeaveGame:
			{
				return std::format_to(context.out(), L"{}", L"Leaving a game");
			}

			case iconer::app::AsyncOperations::OpDisconnect:
			{
				return std::format_to(context.out(), L"{}", L"A session is disconnecting");
			}

			case iconer::app::AsyncOperations::OpEndWorkers:
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
