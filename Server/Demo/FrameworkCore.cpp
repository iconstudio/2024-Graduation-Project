module;
#include <string>
#include <string_view>

module Demo.Framework;
import Iconer.Application.IContext;
import Iconer.Application.BlobSendContext;

bool
demo::Framework::RouteEvent(bool is_succeed
	, const std::uint64_t& io_id
	, const ptrdiff_t& io_bytes
	, iconer::app::IContext* ctx)
{
	switch (ctx->GetOperation())
	{
		// Phase 0
		case iconer::app::AsyncOperations::OpReserveSession:
		{
			auto&& user = *std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user.GetID();

			if (not is_succeed)
			{
				myLogger.LogError(L"\tReserving an acceptance has failed on user {}\n", id);
				OnFailedReservingAccept();
			}
			else if (auto error = OnReserveAccept(user); error.has_value())
			{
				myLogger.LogError(L"\tReserving an acceptance has failed on user {} due to {}\n", id, error.value());
				OnFailedReservingAccept();
			}
			else
			{
				myLogger.Log(L"\tAcceptance is reserved on user {}\n", id);
			}

			user.Clear();
		}
		break;

		// Phase 1
		// an user is connected
		case iconer::app::AsyncOperations::OpAccept:
		{
			auto&& user = *std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user.GetID();

			if (not is_succeed)
			{
				myLogger.LogError(L"\ttConnection has failed on user {}\n", id);
				OnFailedUserConnect(user);
			}
			else if (auto result = OnUserConnected(user); not result.has_value())
			{
				myLogger.LogError(L"\tUser {} is connected, but acceptance has failed due to {}\n", id, result.error());
				OnFailedUserConnect(user);
			}
			else
			{
				myLogger.Log(L"\tUser {} is connected\n", id);
			}

			user.Clear();
		}
		break;

		// Phase 2
		// received a nickname, and send an id of user
		case iconer::app::AsyncOperations::OpSignIn:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();

			if (not is_succeed)
			{
				myLogger.LogError(L"\tSigning In has failed on user {}\n", id);
				OnFailedUserSignIn(*user);
			}
			else if (0 == io_bytes)
			{
				myLogger.LogWarning(L"\tUser {} is just disconnected when they are signing in\n", id);
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
		case iconer::app::AsyncOperations::OpAssignID:
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
				myLogger.LogError(L", but cannot start receiving due to {}\n", result.error());
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
		case iconer::app::AsyncOperations::OpRecv:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();

			if (not is_succeed)
			{
				myLogger.LogError(L"\tReceving has failed on user {}\n", id);
				OnFailedReceive(*user);
			}
			else if (0 == io_bytes)
			{
				myLogger.LogWarning(L"\tUser {} is just disconnected\n", id);
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

		case iconer::app::AsyncOperations::OpSend:
		{
			if (not is_succeed)
			{
				myLogger.LogError(L"\tSending has failed on user {}\n", io_id);
			}
			else if (0 == io_bytes)
			{
				myLogger.LogError(L"\tSending has failed on user {} due to 0 bytes\n", io_id);
			}
			else
			{
				myLogger.Log(L"\tUser {} has sent {} bytes\n", io_id, io_bytes);
			}

			auto sender = static_cast<iconer::app::BlobSendContext*>(ctx);
			
			delete sender;
		}
		break;

		case iconer::app::AsyncOperations::OpDisconnect:
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

		case iconer::app::AsyncOperations::OpReserveRoom:
		{
			auto room = std::launder(static_cast<iconer::app::Room*>(ctx));
			const IdType& room_id = room->GetID();
			const IdType user_id = static_cast<IdType>(io_id);
			auto user = FindUser(user_id);

			if (not is_succeed)
			{
				myLogger.LogError(L"\tUser {} could not reserve room {}\n", user_id, room_id);
				OnFailedToReserveRoom(*room, *user, iconer::app::RoomContract::ServerError);
			}
			else if (auto result = OnReservingRoom(*room, *user); iconer::app::RoomContract::Success != result)
			{
				myLogger.LogError(L"\tUser {} could not reserve {} due to {}\n", user_id, room_id, result);
				OnFailedToReserveRoom(*room, *user, result);
			}
			else
			{
				myLogger.Log(L"\tUser {} reserved room {}\n", user_id, room_id);
			}

			room->Clear();
		}
		break;

		case iconer::app::AsyncOperations::OpCreateRoom:
		{
			const IdType user_id = static_cast<IdType>(io_id);
			auto user = FindUser(user_id);
			const IdType room_id = user->myRoomId;
			auto room = FindRoom(room_id);

			if (not is_succeed)
			{
				myLogger.LogError(L"\tUser {} could not create a room\n", user_id);
				OnFailedToCreateRoom(*room, *user, iconer::app::RoomContract::ServerError);
			}
			else if (auto result = OnCreatingRoom(*room, *user); iconer::app::RoomContract::Success != result)
			{
				myLogger.LogError(L"\tUser {} could not create room at {} due to {}\n", user_id, room_id, result);
				OnFailedToCreateRoom(*room, *user, result);
			}
			else
			{
				myLogger.Log(L"\tUser {} created a room at {}\n", user_id, room_id);
			}

			user->roomContext.Clear();
		}
		break;

		case iconer::app::AsyncOperations::OpEnterRoom:
		{
			auto room = std::launder(static_cast<iconer::app::Room*>(ctx));
			const IdType& room_id = room->GetID();
			const IdType user_id = static_cast<IdType>(io_id);
			auto user = FindUser(user_id);

			if (not is_succeed)
			{
				myLogger.LogError(L"\tUser {} could not enter to room {}\n", user_id, room_id);
				OnFailedToJoinRoom(*room, *user, iconer::app::RoomContract::ServerError);
			}
			else if (auto result = OnJoiningRoom(*room, *user); iconer::app::RoomContract::Success != result)
			{
				myLogger.LogError(L"\tUser {} could not enter to room {} due to {}\n", user_id, room_id, result);
				OnFailedToJoinRoom(*room, *user, result);
			}
			else
			{
				myLogger.Log(L"\tUser {} entered to room {}\n", user_id, room_id);
			}

			room->Clear();
		}
		break;

		case iconer::app::AsyncOperations::OpLeaveRoom:
		{
			const IdType user_id = static_cast<IdType>(io_id);
			auto user = FindUser(user_id);

			if (not is_succeed)
			{
				myLogger.LogError(L"\tUser {} did not left from the room\n", user_id);
			}
			else if (auto result = OnLeavingRoom(*user); not result)
			{
				myLogger.LogError(L"\tUser {} did not left from the room\n", user_id);
			}
			else
			{
				myLogger.Log(L"\tUser {} has been left from the room\n", user_id);
			}

			auto sender = static_cast<iconer::app::BlobSendContext*>(ctx);
			delete sender;
		}
		break;

		case iconer::app::AsyncOperations::OpReadyGame:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();

			user->Clear();
		}
		break;

		case iconer::app::AsyncOperations::OpEnterGame:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();


			user->Clear();
		}
		break;

		case iconer::app::AsyncOperations::OpStartGame:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();


			user->Clear();
		}
		break;

		case iconer::app::AsyncOperations::OpLeaveGame:
		{
			auto user = std::launder(static_cast<iconer::app::User*>(ctx));
			const IdType& id = user->GetID();


			user->Clear();
		}
		break;

		case iconer::app::AsyncOperations::OpEndWorkers:
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
