module TestClient;
import Iconer.Application.BasicPacket;
import Iconer.Application.Packet;

iconer::net::Socket::AsyncResult
test::SendSignInPacket()
{
	const iconer::app::packets::CS_SignInPacket sign_packet{ my_name.data(), my_name.size() };

	auto ptr = sign_packet.Serialize();

	iconer::net::IoContext send_ctx{};
	return app_socket.Send(send_ctx, ptr.get(), sign_packet.WannabeSize());
}

iconer::net::Socket::AsyncResult
test::SendCreateRoomPacket(std::wstring_view title)
{
	const iconer::app::packets::CS_CreateRoomPacket pk{ title.data(), title.length() };

	auto ptr = pk.Serialize();

	iconer::net::IoContext send_ctx{};
	return app_socket.Send(send_ctx, ptr.get(), pk.WannabeSize());
}

iconer::net::Socket::AsyncResult
test::SendJoinRoomPacket(IdType room_id)
{
	const iconer::app::packets::CS_EnterRoomPacket pk{ room_id };

	auto ptr = pk.Serialize();

	iconer::net::IoContext send_ctx{};
	return app_socket.Send(send_ctx, ptr.get(), pk.WannabeSize());
}

iconer::net::Socket::AsyncResult
test::SendLeaveRoomPacket()
{
	iconer::app::packets::CS_LeaveRoomPacket pk{};

	auto ptr = pk.Serialize();

	iconer::net::IoContext send_ctx{};
	return app_socket.Send(send_ctx, ptr.get(), pk.WannabeSize());
}

bool
test::SendPositionPacket()
{
	iconer::app::packets::CS_UpdatePositionPacket position_pk{ localPlayer->x, localPlayer->y, localPlayer->z };

	auto serialized = position_pk.Serialize();

	iconer::net::IoContext send_position_ctx{};
	auto sent_position_r = app_socket.Send(send_position_ctx, serialized.get(), iconer::app::packets::CS_UpdatePositionPacket::WannabeSize());
	if (not sent_position_r.has_value())
	{
		return false;
	}

	send_position_ctx.Clear();

	return true;
}
