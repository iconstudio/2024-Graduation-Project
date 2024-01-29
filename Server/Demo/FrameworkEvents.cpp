module;
module Demo.Framework;

demo::Framework::SocketResult
demo::Framework::OnReserveAccept(iconer::app::User& user, iconer::app::UserStates& transit_state)
{
	switch (transit_state)
	{
		case iconer::app::UserStates::None:
		{
			user.SetOperation(iconer::app::UserOperations::Connect);
			transit_state = iconer::app::UserStates::Reserved;

			return serverListener.ReserveAccept(user, user.mySocket);
		}
		break;

		default:
		{
			return iconer::net::ErrorCode::OPERATION_ABORTED;
		}
	}
}

demo::Framework::SocketResult
demo::Framework::OnUserConnected(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state)
{
	switch (transit_state)
	{
		case iconer::app::UserStates::Reserved:
		{
			user.SetOperation(iconer::app::UserOperations::Recv);
			transit_state = iconer::app::UserStates::Idle;

			return user.Receive(GetBuffer(id));
		}
		break;

		default:
		{
			return iconer::net::ErrorCode::OPERATION_ABORTED;
		}
	}
}

demo::Framework::SocketResult
demo::Framework::OnReceived(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state, const size_t& bytes)
{
	auto user_buffer = GetBuffer(id);
	auto& user_recv_offset = user.recvOffset;

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
			return iconer::net::ErrorCode::OPERATION_ABORTED;
		}
	}
}

demo::Framework::SocketResult
demo::Framework::OnUserDisconnected(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state)
{
	
	
	return iconer::net::ErrorCode::OPERATION_ABORTED;
}
