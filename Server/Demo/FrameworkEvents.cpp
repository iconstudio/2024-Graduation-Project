module;
#include <string_view>

module Demo.Framework;
import Iconer.Application.User;
import Iconer.Application.Packet;
import Demo.Framework.PacketProcessor;
import <stdexcept>;

demo::Framework::AcceptResult
demo::Framework::OnReserveAccept(iconer::app::User& user)
{
	if (user.TryChangeState(iconer::app::UserStates::None, iconer::app::UserStates::Reserved))
	{
		user.SetOperation(iconer::app::Operations::OpAccept);
		return serverListener.BeginAccept(user, user.mySocket);
	}
	else
	{
		return iconer::net::ErrorCode::OPERATION_ABORTED;
	}
}

void
demo::Framework::OnFailedReservingAccept(iconer::app::User& user)
{
	throw std::runtime_error{ "Error when reserving acceptance of a socket." };
}

demo::Framework::IoResult
demo::Framework::OnUserConnected(iconer::app::User& user)
{
	if (auto fin = user.mySocket.EndAccept(serverListener); fin.has_value())
	{
		return std::unexpected{ fin.value() };
	}
	else if (user.TryChangeState(iconer::app::UserStates::Reserved, iconer::app::UserStates::Connected))
	{
		user.SetOperation(iconer::app::Operations::OpSignIn);

		return user.Receive(GetBuffer(user.GetID()));
	}
	else
	{
		return std::unexpected{ iconer::net::ErrorCode::OPERATION_ABORTED };
	}
}

void
demo::Framework::OnFailedUserConnect(iconer::app::User& user)
{
	user.Cleanup();
	user.Destroy();
}

demo::Framework::IoResult
demo::Framework::OnUserSignedIn(iconer::app::User& user, const ptrdiff_t& bytes)
{
	if (bytes <= 0)
	{
		return std::unexpected{ iconer::net::ErrorCode::OPERATION_ABORTED };
	}

	// Small receiving phase
	auto user_buffer = GetBuffer(user.GetID());
	auto& user_recv_offset = user.recvOffset;

	user_recv_offset += bytes;

	if (iconer::app::packets::CS_SignInPacket::SignedWannabeSize() <= user_recv_offset)
	{
		thread_local iconer::app::packets::CS_SignInPacket pk{};
		pk.Read(user_buffer.data(), user_recv_offset);

		if (pk.myProtocol != iconer::app::PacketProtocol::CS_SIGNIN or pk.mySize <= 0)
		{
			return std::unexpected{ iconer::net::ErrorCode::OPERATION_ABORTED };
		}

		if (true) [[likely]] { // The signing in is succeed
			// Don't necessary to pull back buffer of the receive buffer
			user_recv_offset -= iconer::app::packets::CS_SignInPacket::SignedWannabeSize();

			user.myName = pk.userName;

			while (not user.TryChangeState(iconer::app::UserStates::Connected, iconer::app::UserStates::PendingID));

			user.SetOperation(iconer::app::Operations::OpAssignID);

			return user.SendSignInPacket();
		}
		else [[unlikely]] {
			// TODO: send sign in failed packet
			return std::unexpected{ iconer::net::ErrorCode::OPERATION_ABORTED };
		};
	}
	else
	{
		// Restart remain packet bytes
		// Still at OpSignIn
		return user.Receive(user_buffer);
	}
}

void
demo::Framework::OnFailedUserSignIn(iconer::app::User& user)
{
	user.Cleanup();
	user.Destroy();
}

demo::Framework::IoResult
demo::Framework::OnNotifyUserId(iconer::app::User& user)
{
	if (user.TryChangeState(iconer::app::UserStates::PendingID, iconer::app::UserStates::Idle))
	{
		user.SetOperation(iconer::app::Operations::OpRecv);

		return user.Receive(GetBuffer(user.GetID()));
	}
	else
	{
		return std::unexpected{ iconer::net::ErrorCode::OPERATION_ABORTED };
	}
}

void
demo::Framework::OnFailedNotifyId(iconer::app::User& user)
{
	user.Cleanup();
	user.Destroy();
}

demo::Framework::IoResult
demo::Framework::OnReceived(iconer::app::User& user, const ptrdiff_t& bytes)
{
	const IdType& id = user.GetID();
	auto user_buffer = GetBuffer(id);
	auto& user_recv_offset = user.recvOffset;

	user_recv_offset += bytes;

	if (iconer::app::BasicPacket::MinSize() <= user_recv_offset)
	{
		auto transit_state = user.AcquireState();

		auto proceed_bytes = PacketProcessor(*this, user, id, transit_state, user_buffer, bytes);
		if (proceed_bytes < 0) [[unlikely]] {
			myLogger.LogWarning(L"Cannot assembly a packet due to `PacketProcessor`'s failure");

			user.ReleaseState(transit_state);
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

		user.ReleaseState(transit_state);
	}
	else
	{
		myLogger.DebugLogWarning(L"Cannot assembly a packet due to lack of bytes");
	}

	return user.Receive(GetBuffer(id));
}

void
demo::Framework::OnFailedReceive(iconer::app::User& user)
{
	user.Cleanup();
	user.Destroy();
}

demo::Framework::AcceptResult
demo::Framework::OnUserDisconnected(iconer::app::User& user)
{
	// Reserve the user again
	if (user.TryChangeState(iconer::app::UserStates::Dead, iconer::app::UserStates::None))
	{
		if (Schedule(user, user.GetID()))
		{
			user.SetOperation(iconer::app::Operations::OpReserveSession);
			return std::nullopt;
		}
	}

	return iconer::net::ErrorCode::OPERATION_ABORTED;
}
