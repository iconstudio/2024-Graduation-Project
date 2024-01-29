module;
module Demo.Framework;
import Iconer.Application.BasicPacket;
import <expected>;
import <bit>;
import <string>;
import <string_view>;

using namespace iconer;

demo::Framework::SocketResult
demo::Framework::OnReserveAccept(app::User& user, app::UserStates& transit_state)
{
	switch (transit_state)
	{
		case app::UserStates::None:
		{
			user.SetOperation(app::UserOperations::Connect);
			transit_state = app::UserStates::Reserved;

			return serverListener.ReserveAccept(user, user.mySocket);
		}

		default:
		{
			return net::ErrorCode::OPERATION_ABORTED;
		}
	}
}

demo::Framework::RecvResult
demo::Framework::OnUserConnected(app::User& user, const IdType& id, app::UserStates& transit_state)
{
	switch (transit_state)
	{
		case app::UserStates::Reserved:
		{
			user.SetOperation(app::UserOperations::Recv);
			transit_state = app::UserStates::Idle;

			return user.Receive(GetBuffer(id));
		}

		default:
		{
			return std::unexpected(net::ErrorCode::OPERATION_ABORTED);
		}
	}
}

demo::Framework::RecvResult
demo::Framework::OnReceived(app::User& user, const IdType& id, app::UserStates& transit_state, const ptrdiff_t& bytes)
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
			user_recv_offset -= PacketProcessor(*this, id, user_buffer, user_recv_offset);
		}

		// continue
		return user.Receive(user_buffer);

		switch (transit_state)
		{
			case app::UserStates::Idle:
			{

			}
			break;

			case app::UserStates::InLobby:
			{

			}
			break;

			case app::UserStates::InRoom:
			{

			}
			break;

			case app::UserStates::InGame:
			{

			}
			break;

			case app::UserStates::Dead:
			{

			}
			break;

			default:
			{
				return net::ErrorCode::OPERATION_ABORTED;
			}
		}
	}

	return std::unexpected(net::ErrorCode::OPERATION_ABORTED);
}

bool
demo::Framework::OnUserSignIn(app::User& user, const IdType& id, app::UserStates& transit_state)
{
	return false;
}

demo::Framework::SocketResult
demo::Framework::OnUserDisconnected(app::User& user, const IdType& id, app::UserStates& transit_state)
{


	return net::ErrorCode::OPERATION_ABORTED;
}
