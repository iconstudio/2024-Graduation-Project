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
			user.SetOperation(app::Operations::Recv);
			transit_state = app::UserStates::Idle;

			return user.Receive(GetBuffer(id));
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
	if (0 < bytes)
	{
		if (bytes <= 0)
		{
			throw "Error";
		}

		auto& user_recv_offset = user.recvOffset;

		user_recv_offset += bytes;
		if (user_recv_offset <= 0 or userRecvSize < static_cast<size_t>(user_recv_offset))
		{
			throw "Error";
		}

		constexpr ptrdiff_t minimal_size = app::BasicPacket::SignedMinSize();
		auto user_buffer = GetBuffer(id);

		if (minimal_size <= user_recv_offset)
		{
			user_recv_offset -= PacketProcessor(*this, user, id, transit_state, user_buffer, user_recv_offset);
		}

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
