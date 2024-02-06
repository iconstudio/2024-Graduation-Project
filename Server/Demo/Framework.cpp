module;
#include <string>
#include <string_view>

module Demo.Framework;
import Iconer.Application.ISession;
import <atomic>;

bool
demo::Framework::CreateListenerSocket()
noexcept
{
	return iconer::net::Socket::TryCreate(iconer::net::IoCategory::Asynchronous, iconer::net::InternetProtocol::TCP, iconer::net::IpAddressFamily::IPv4, serverListener);
}

bool
demo::Framework::InitializeListener()
noexcept
{
	if (serverListener.BindHost(serverPort).has_value())
	{
		return false;
	}

	serverListener.IsAddressReusable = true;

	return true;
}

bool
demo::Framework::InitializeCompletionPort(iconer::net::ErrorCode& error_code)
noexcept
{
	return iconer::net::IoCompletionPort::Create(uint32_t(workersCount)).and_then(
		[&](iconer::net::IoCompletionPort&& port) noexcept -> std::expected<bool, iconer::net::ErrorCode> {
		ioCompletionPort = std::move(port);
		return true;
	}).transform_error(
		[&error_code](iconer::net::ErrorCode&& code) noexcept -> std::expected<bool, iconer::net::ErrorCode> {
		error_code = std::move(error_code);
		return false;
	}).value_or(false);
}

bool
demo::Framework::InitializeUsers()
{
	auto user_factory = iconer::app::SessionFactory<iconer::app::User>{};

	IdType id = beginUserID;
	for (size_t i = 0; i < maxUsersNumber; ++i)
	{
		if (iconer::net::Socket socket; iconer::net::Socket::TryCreate(iconer::net::IoCategory::Asynchronous, iconer::net::InternetProtocol::TCP, iconer::net::IpAddressFamily::IPv4, socket))
		{
			if (not ioCompletionPort.Register(socket, id).has_value())
			{
				auto user = user_factory.Create(id++, std::move(socket));
				userManager->Add(std::move(user));
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool
demo::Framework::StartAccepts()
{
	for (auto& [id, user] : *userManager)
	{
		user.Awake();

		user.SetOperation(iconer::app::Operations::OpReserveSession);

		if (not Schedule(user, id, 0))
		{
			return false;
		}
	}

	return true;
}

void
demo::Framework::RouteOperation(bool is_succeed
	, const ptrdiff_t& io_bytes, const iconer::app::Operations& operation
	, iconer::app::User& user)
{
	//auto switcher = user.GetStateSwitcher();
	//iconer::app::UserStates& status = switcher.myValue;
	iconer::app::UserStates transit_state = user.AcquireState();

	const IdType id = user.GetID();

	switch (operation)
	{
		// Phase 0
		case iconer::app::Operations::OpReserveSession:
		{
			if (not is_succeed)
			{
				myLogger.LogError(L"\tReserving an acceptance has failed on user {}\n", id);
				OnFailedReservingAccept(user, transit_state);
			}
			else if (auto error = OnReserveAccept(user, transit_state); error.has_value())
			{
				myLogger.LogError(L"\tReserving an acceptance has failed on user {} due to {}\n", id, error.value());
				OnFailedReservingAccept(user, transit_state);
			}
			else
			{
				myLogger.Log(L"\tAcceptance is reserved on user {}\n", id);
			}
		}
		break;
		
		// Phase 1
		// an user is connected
		case iconer::app::Operations::OpAccept:
		{
			if (not is_succeed)
			{
				myLogger.LogError(L"\ttConnection has failed on user {}\n", id);
				OnFailedUserConnect(user, transit_state);
			}
			else if (auto error = OnUserConnected(user, id, transit_state); not error.has_value())
			{
				myLogger.LogError(L"\tUser {} is connected, but acceptance has failed due to {}\n", id, error.error());
				OnFailedUserConnect(user, transit_state);
			}
			else
			{
				myLogger.Log(L"\tUser {} is connected\n", id);
			}
		}
		break;

		// Phase 2
		// received a nickname, and send an id of user
		case iconer::app::Operations::OpSignIn:
		{
			if (not is_succeed)
			{
				myLogger.LogError(L"\tSigning In has failed on user {}\n", id);
				OnFailedUserSignIn(user, transit_state);
			}
			else if (auto error = OnUserSignedIn(user, id, transit_state, io_bytes); not error.has_value())
			{
				myLogger.LogError(L"\tSigning In has failed on user {} due to {}\n", id, error.error());
				OnFailedUserSignIn(user, transit_state);
			}
			else
			{
				myLogger.Log(L"\tUser {} is signed in\n", id);
			}
		}
		break;

		// Phase 3
		// sent an id of user
		case iconer::app::Operations::OpAssignID:
		{
			if (not is_succeed)
			{
				myLogger.LogError(L"\tNotifying the id to user {} has failed\n", id);
				OnFailedNotifyId(user, transit_state);
			}
			else if (auto error = OnNotifyUserId(user, id, transit_state); not error.has_value())
			{
				myLogger.LogError(L"\tUser {} cannot start receving due to {}\n", id, error.error());
				OnFailedNotifyId(user, transit_state);
			}
			else
			{
				myLogger.Log(L"\tThe Id is notified to user {}\n", id);
			}
		}
		break;

		// Phase 4~
		case iconer::app::Operations::OpRecv:
		{
			if (not is_succeed)
			{
				myLogger.LogError(L"\tReceving has failed on user {}\n", id);
				OnFailedReceive(user, transit_state);
			}
			else if (auto error = OnReceived(user, id, transit_state, io_bytes); not error.has_value())
			{
				myLogger.LogError(L"\tReceving has failed on user {} due to {}\n", id, error.error());
				OnFailedReceive(user, transit_state);
			}
			else
			{
				myLogger.Log(L"\tReceving is proceed on user {}\n", id);
			}
		}
		break;

		case iconer::app::Operations::OpDisconnect:
		{
			if (not is_succeed)
			{
				myLogger.LogError(L"\tUser {} has failed to disconnect\n", id);
			}
			else if (auto error = OnUserDisconnected(user, id, transit_state); error.has_value())
			{
				myLogger.LogError(L"\tUser {} would not be disconnected due to {}\n", id, error.value());
			}
			else
			{
				myLogger.Log(L"\tUser {} has been disconnected\n", id);
			}
		}
		break;

		case iconer::app::Operations::OpCreateRoom:
		{
			if (not is_succeed)
			{
				myLogger.LogError(L"\tUser {} could not create a room\n", id);
			}
			else
			{
				myLogger.Log(L"\tUser {} created a room {}\n", id, 0);
			}
		}
		break;

		case iconer::app::Operations::OpEnterRoom:
		{
			if (not is_succeed)
			{
				myLogger.LogError(L"\tUser {} could not enter to room {}\n", id, 0);
			}
			else
			{
				myLogger.Log(L"\tUser {} entered to room {}\n", id, 0);
			}
		}
		break;

		case iconer::app::Operations::OpLeaveRoom:
		{

		}
		break;

		case iconer::app::Operations::OpReadyGame:
		{

		}
		break;

		case iconer::app::Operations::OpEnterGame:
		{

		}
		break;

		case iconer::app::Operations::OpStartGame:
		{

		}
		break;

		case iconer::app::Operations::OpLeaveGame:
		{

		}
		break;

		default:
		{
			if (not is_succeed)
			{
				myLogger.LogError(L"\tUnknown operation '{}' has failed on user {}\n", static_cast<int>(operation), id);
			}
			else
			{
				myLogger.Log(L"\tAn unknown operation '{}' has been executed on user {}\n", static_cast<int>(operation), id);
			}
		}
		break;
	}

	user.ReleaseState(transit_state);
}
void
demo::Framework::LockPhase()
noexcept
{
	std::atomic_thread_fence(std::memory_order_acquire);
}

void
demo::Framework::UnlockPhase()
noexcept
{
	std::atomic_thread_fence(std::memory_order_release);
}
