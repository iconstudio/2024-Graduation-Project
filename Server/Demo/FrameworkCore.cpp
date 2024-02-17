module;
#include <string>
#include <string_view>

module Demo.Framework;
import Iconer.Application.IContext;
import Iconer.Application.BorrowedSendContext;

bool
demo::Framework::RouteEvent(bool is_succeed
	, const std::uint64_t& io_id
	, const ptrdiff_t& io_bytes
	, iconer::app::IContext* ctx)
{
	switch (ctx->GetOperation())
	{
		// Phase 0
		case iconer::app::Operations::OpReserveSession:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();

			if (not is_succeed)
			{
				myLogger.LogError(L"\tReserving an acceptance has failed on user {}\n", id);
				OnFailedReservingAccept(*user);
			}
			else if (auto error = OnReserveAccept(*user); error.has_value())
			{
				myLogger.LogError(L"\tReserving an acceptance has failed on user {} due to {}\n", id, error.value());
				OnFailedReservingAccept(*user);
			}
			else
			{
				myLogger.Log(L"\tAcceptance is reserved on user {}\n", id);
			}

			user->Clear();
		}
		break;

		// Phase 1
		// an user is connected
		case iconer::app::Operations::OpAccept:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();

			if (not is_succeed)
			{
				myLogger.LogError(L"\ttConnection has failed on user {}\n", id);
				OnFailedUserConnect(*user);
			}
			else if (auto result = OnUserConnected(*user); not result.has_value())
			{
				myLogger.LogError(L"\tUser {} is connected, but acceptance has failed due to {}\n", id, result.error());
				OnFailedUserConnect(*user);
			}
			else
			{
				myLogger.Log(L"\tUser {} is connected\n", id);
			}

			user->Clear();
		}
		break;

		// Phase 2
		// received a nickname, and send an id of user
		case iconer::app::Operations::OpSignIn:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();

			if (not is_succeed)
			{
				myLogger.LogError(L"\tSigning In has failed on user {}\n", id);
				OnFailedUserSignIn(*user);
			}
			else if (auto result = OnUserSignedIn(*user, io_bytes); not result.has_value())
			{
				myLogger.LogError(L"\tSigning In has failed on user {} due to {}\n", id, result.error());
				OnFailedUserSignIn(*user);
			}
			else
			{
				myLogger.Log(L"\tUser {} is signed in\n", id);
			}

			user->Clear();
		}
		break;

		// Phase 3
		// sent an id of user
		case iconer::app::Operations::OpAssignID:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();

			if (not is_succeed)
			{
				myLogger.LogError(L"\tNotifying the id to user {} has failed\n", id);
				OnFailedNotifyId(*user);
			}
			else if (auto result = OnNotifyUserId(*user); not result.has_value())
			{
				myLogger.Log(L"\tThe Id is notified to user {}", id);
				myLogger.LogError(L"\t, but cannot start receiving due to {}\n", result.error());
				OnFailedNotifyId(*user);
			}
			else
			{
				myLogger.Log(L"\tUser {} has been notified id, now start receiving\n", id);
			}

			user->Clear();
		}
		break;

		// Phase 4~
		case iconer::app::Operations::OpRecv:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();

			if (not is_succeed)
			{
				myLogger.LogError(L"\tReceving has failed on user {}\n", id);
				OnFailedReceive(*user);
			}
			else if (auto error = OnReceived(*user, io_bytes); not error.has_value())
			{
				myLogger.LogError(L"\tReceving has failed on user {} due to {}\n", id, error.error());
				OnFailedReceive(*user);
			}
			else
			{
				myLogger.Log(L"\tReceving is proceed on user {}\n", id);
			}

			user->Clear();
		}
		break;

		case iconer::app::Operations::OpDisconnect:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();

			if (not is_succeed)
			{
				myLogger.LogError(L"\tUser {} has failed to disconnect\n", id);
			}
			else if (auto error = OnUserDisconnected(*user); error.has_value())
			{
				myLogger.LogError(L"\tUser {} would not be disconnected due to {}\n", id, error.value());
			}
			else
			{
				myLogger.Log(L"\tUser {} has been disconnected\n", id);
			}

			user->Clear();
		}
		break;

		case iconer::app::Operations::OpCreateRoom:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();

			if (not is_succeed)
			{
				myLogger.LogError(L"\tUser {} could not create a room\n", id);
			}
			else
			{
				myLogger.Log(L"\tUser {} created a room {}\n", id, 0);
			}

			user->Clear();
		}
		break;

		case iconer::app::Operations::OpEnterRoom:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();

			if (not is_succeed)
			{
				myLogger.LogError(L"\tUser {} could not enter to room {}\n", id, 0);
			}
			else
			{
				myLogger.Log(L"\tUser {} entered to room {}\n", id, 0);
			}

			user->Clear();
		}
		break;

		case iconer::app::Operations::OpLeaveRoom:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();


			user->Clear();
		}
		break;

		case iconer::app::Operations::OpReadyGame:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();

			user->Clear();
		}
		break;

		case iconer::app::Operations::OpEnterGame:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();


			user->Clear();
		}
		break;

		case iconer::app::Operations::OpStartGame:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();


			user->Clear();
		}
		break;

		case iconer::app::Operations::OpLeaveGame:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();


			user->Clear();
		}
		break;

		case iconer::app::Operations::OpEndWorkers:
		{
			return false;
		}

		default:
		{
			if (not is_succeed)
			{
				myLogger.LogError(L"\tUnknown operation '{}' has failed on {}\n", static_cast<int>(ctx->GetOperation()), reinterpret_cast<std::uintptr_t>(ctx));
			}
			else
			{
				myLogger.Log(L"\tAn unknown operation '{}' has been executed on {}\n", static_cast<int>(ctx->GetOperation()), reinterpret_cast<std::uintptr_t>(ctx));
			}
		}
		break;
	}

	return true;
}
