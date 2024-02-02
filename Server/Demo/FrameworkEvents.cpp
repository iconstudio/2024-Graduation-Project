module;
#include <string_view>

module Demo.Framework;
import Iconer.Application.User;

demo::Framework::SocketResult
demo::Framework::OnReserveAccept(iconer::app::User& user, iconer::app::UserStates& transit_state)
{
	switch (transit_state)
	{
		case iconer::app::UserStates::None:
		{
			user.SetOperation(iconer::app::Operations::OpAccept);
			transit_state = iconer::app::UserStates::Reserved;

			return serverListener.ReserveAccept(user, user.mySocket);
		}

		default:
		{
			return iconer::net::ErrorCode::OPERATION_ABORTED;
		}
	}
}

demo::Framework::RecvResult
demo::Framework::OnUserConnected(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state)
{
	switch (transit_state)
	{
		case iconer::app::UserStates::Reserved:
		{
			user.SetOperation(iconer::app::Operations::OpSignIn);

			auto recv_r = user.Receive(GetBuffer(id));
			if (recv_r)
			{
				transit_state = iconer::app::UserStates::Connected;
			}

			return recv_r;
		}

		default:
		{
			return std::unexpected(iconer::net::ErrorCode::OPERATION_ABORTED);
		}
	}
}

demo::Framework::SendResult
demo::Framework::OnUserSignedIn(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state)
{
	switch (transit_state)
	{
		case iconer::app::UserStates::Connected:
		{
			user.SetOperation(iconer::app::Operations::OpAssignID);
			transit_state = iconer::app::UserStates::Idle;

			//return user.Receive(GetBuffer(id));
		}

		default:
		{
			return std::unexpected(iconer::net::ErrorCode::OPERATION_ABORTED);
		}
	}
}

demo::Framework::RecvResult
demo::Framework::OnNotifyUserId(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state)
{
	switch (transit_state)
	{
		case iconer::app::UserStates::Idle:
		{
			user.SetOperation(iconer::app::Operations::OpAssignID);
			transit_state = iconer::app::UserStates::InLobby;

			auto recv_r = user.Receive(GetBuffer(id));
			if (recv_r)
			{
				transit_state = iconer::app::UserStates::InLobby;
			}

			return recv_r;
		}

		default:
		{
			return std::unexpected(iconer::net::ErrorCode::OPERATION_ABORTED);
		}
	}
}

demo::Framework::RecvResult
demo::Framework::OnReceived(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state, const ptrdiff_t& bytes)
{
	auto user_buffer = GetBuffer(id);
	auto& user_recv_offset = user.recvOffset;

	auto recently_recv_buffer = user_buffer.subspan(user_recv_offset);

	switch (transit_state)
	{
		case iconer::app::UserStates::Idle:
		{

		}
		break;

		case iconer::app::UserStates::InLobby:
		{

		}
		break;

		case iconer::app::UserStates::InRoom:
		{

		}
		break;

		case iconer::app::UserStates::InGame:
		{

		}
		break;

		case iconer::app::UserStates::Dead:
		{

		}
		break;

		default:
		{
			return std::unexpected{ iconer::net::ErrorCode::OPERATION_ABORTED };
		}
	}

	return std::unexpected{ iconer::net::ErrorCode::OPERATION_ABORTED };
}

bool
demo::Framework::OnUserSignIn(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state)
{
	return false;
}

demo::Framework::SocketResult
demo::Framework::OnUserDisconnected(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state)
{
	
	
	return iconer::net::ErrorCode::OPERATION_ABORTED;
}
