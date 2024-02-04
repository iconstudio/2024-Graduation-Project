module;
#include <string_view>

module Demo.Framework;
import Iconer.Application.User;
import Iconer.Application.BasicPacket;
import Demo.Framework.PacketProcessor;

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

			auto send_r = user.SendSignInPacket();
			if (send_r)
			{
				transit_state = iconer::app::UserStates::PendingID;
			}

			return send_r;
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
		case iconer::app::UserStates::PendingID:
		{
			user.SetOperation(iconer::app::Operations::OpRecv);

			auto recv_r = user.Receive(GetBuffer(id));
			if (recv_r)
			{
				transit_state = iconer::app::UserStates::Idle;
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

	user_recv_offset += bytes;

	if (iconer::app::BasicPacket::MinSize() <= user_recv_offset)
	{
		auto proceed_bytes = PacketProcessor(*this, user, id, transit_state, user_buffer, bytes);
		if (proceed_bytes < 0) [[unlikely]]
		{
			myLogger.LogWarning(L"Cannot assembly a packet due to `PacketProcessor`'s failure");

			return std::unexpected(iconer::net::ErrorCode::NoBufferStorage);
		}
		else if (0 == proceed_bytes)
		{
			myLogger.DebugLogWarning(L"Cannot assembly a packet in `PacketProcessor` due to lack of bytes");
		}
		else
		{
			myLogger.DebugLog(L"A packet is assembled");

			user_recv_offset -= proceed_bytes;
		};
	}
	else
	{
		myLogger.DebugLogWarning(L"Cannot assembly a packet due to lack of bytes");
	}

	return user.Receive(GetBuffer(id));
}
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

demo::Framework::SocketResult
demo::Framework::OnUserDisconnected(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state)
{
	
	
	return iconer::net::ErrorCode::OPERATION_ABORTED;
}
