module;
#pragma comment(lib, "Server.lib")

module TestClient;
import Iconer.Application.BasicPacket;
import <print>;

namespace test
{
	void PullReceiveBuffer(const std::byte* last_offset);
}

void
test::Receiver()
{
	while (true)
	{
		auto recv_result = app_socket.Receive(recv_buffer.subspan(received_bytes));
		//auto recv = app_socket.MakeReceiveTask(recv_ctx, recv_space + received_bytes, recvMaxSize - received_bytes);
		//auto recv_result = co_await recv;

		if (not recv_result.has_value())
		{
			std::println("Receive error: {}", recv_result.error());
			break;
		}
		else
		{
			const auto& bytes = recv_result.value();

			received_bytes += bytes;

			if (iconer::app::BasicPacket::MinSize() <= received_bytes)
			{
				iconer::app::BasicPacket basic_pk{};
				const auto seek = basic_pk.Read(recv_space);

				if (basic_pk.mySize <= 0)
				{
					//throw "error!";
					std::println("Packet's size is zero!");
				}
				else if (const auto sz = static_cast<unsigned long>(basic_pk.mySize); sz <= received_bytes)
				{
					switch (basic_pk.myProtocol)
					{
						case iconer::app::PacketProtocol::SC_SIGNIN_SUCCESS:
						{
							auto offset = ReceiveSignInSucceedPacket(recv_space);
							std::println("Local player's id is {}", my_id);

							PullReceiveBuffer(offset);
						}
						break;

						case iconer::app::PacketProtocol::SC_SIGNIN_FAILURE:
						{
							int error{};
							auto offset = ReceiveSignInFailurePacket(recv_space, error);
							std::println("Local player can't get an id from server due to {}", error);

							PullReceiveBuffer(offset);
						}
						break;

						case iconer::app::PacketProtocol::SC_ROOM_CREATED:
						{
							auto offset = ReceiveRoomCreatedPacket(recv_space, roomId);

							std::println("A room {} is created", roomId);

							PullReceiveBuffer(offset);
						}
						break;
						
						case iconer::app::PacketProtocol::SC_ROOM_CREATE_FAILED:
						{
							iconer::app::RoomContract error{};
							auto offset = ReceiveRoomCreationFailedPacket(recv_space, error);
							std::println("Could not create a room due to {}", error);

							PullReceiveBuffer(offset);
						}
						break;

						case iconer::app::PacketProtocol::SC_ROOM_JOINED:
						{
							IdType newbie{};
							auto offset = ReceiveRoomJoinedPacket(recv_space, newbie);

							std::println("Client {} is joined to the room {}", newbie, roomId);

							PullReceiveBuffer(offset);
						}
						break;

						case iconer::app::PacketProtocol::SC_ROOM_JOIN_FAILED:
						{
							iconer::app::RoomContract error{};
							auto offset = ReceiveRoomJoinFailedPacket(recv_space, error);
							std::println("Failed to join to a room due to {}", error);

							PullReceiveBuffer(offset);
						}
						break;

						case iconer::app::PacketProtocol::SC_ROOM_LEFT:
						{
							std::int32_t left_client{};
							auto offset = ReceiveRoomLeftPacket(recv_space, left_client);

							std::println("Client {} has been left from room", left_client);

							PullReceiveBuffer(offset);
						}
						break;

						case iconer::app::PacketProtocol::SC_CREATE_PLAYER:
						{
							//iconer::app::packets::SC_CreatePlayerPacket pk{};
							//auto offset = pk.Read(recv_space);

							//std::println("A player {} is created",  pk.clientId);
							//everyClients.emplace(std::make_pair(pk.clientId, FSagaPlayer{}));

							//PullReceiveBuffer(offset);
						}
						break;

						case iconer::app::PacketProtocol::SC_REMOVE_PLAYER:
						{
							//iconer::app::packets::SC_DestroyPlayerPacket pk{};
							//auto offset = pk.Read(recv_space);

							//std::println("A player {} is destroyed(disconnected)", pk.clientId);
							//std::println("A player is destroyed(disconnected)");

							//PullReceiveBuffer(offset);
						}
						break;

						case iconer::app::PacketProtocol::SC_MOVE_CHARACTER:
						{
							//iconer::app::packets::SC_UpdatePositionPacket pk{ 0, 0, 0, 0 };
							//auto offset = pk.Read(recv_space);

							//std::println("Player id {}: pos({},{},{})", pk.clientId, pk.x, pk.y, pk.z);
							//std::println("Player id pos");

							//PullReceiveBuffer(offset);
						}
						break;

						case iconer::app::PacketProtocol::SC_UPDATE_CHARACTER:
						{
						}
						break;
					}
				}
			}
		}

		recv_ctx.Clear();
	}
}

void
test::PullReceiveBuffer(const std::byte* last_offset)
{
	const auto offset = (last_offset - recv_space);

	std::memcpy(recv_space, last_offset, recvMaxSize - static_cast<size_t>(offset));

	//unsigned long decrement = 0;
	//for (std::byte* it = recv_space; it != recv_space + offset; ++it)
	{
		//*(it++) = *(last_offset++);
		//++decrement;
	}
	received_bytes -= static_cast<unsigned long>(offset);
}
