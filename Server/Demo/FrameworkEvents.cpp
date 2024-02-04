module;
#include <string_view>

module Demo.Framework;
import Iconer.Application.User;
import Iconer.Application.BasicPacket;
import Demo.Framework.PacketProcessor;

demo::Framework::AcceptResult
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

demo::Framework::IoResult
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

demo::Framework::IoResult
demo::Framework::OnUserSignedIn(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state, const ptrdiff_t& bytes)
{
	switch (transit_state)
	{
		case iconer::app::UserStates::Connected:
		{
			// Small receiving phase
			auto user_buffer = GetBuffer(id);
			auto& user_recv_offset = user.recvOffset;

			user_recv_offset += bytes;

			if (iconer::app::BasicPacket::MinSize() <= user_recv_offset)
			{
			}
			else
			{
			}

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

demo::Framework::IoResult
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

demo::Framework::IoResult
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

demo::Framework::AcceptResult
demo::Framework::OnUserDisconnected(iconer::app::User& user, const IdType& id, iconer::app::UserStates& transit_state)
{
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
	}

	return iconer::net::ErrorCode::OPERATION_ABORTED;
}
