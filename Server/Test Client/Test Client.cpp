#pragma comment(lib, "Server.lib")
#include <type_traits>
#include <expected>
#include <utility>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <algorithm>
#include <print>

import Iconer.Utility.Serializer;
import Iconer.Net;
import Iconer.Net.IpAddress;
import Iconer.Net.EndPoint;
import Iconer.Net.Socket;
import Iconer.Coroutine;
import Iconer.Application.Packet;

using namespace iconer;

net::Socket app_socket{};
net::IpAddress server_address{};
net::EndPoint server_ep{};
constexpr std::uint16_t server_port = 40000;

static inline constexpr size_t recvMaxSize = 512;
static std::byte recv_space[recvMaxSize]{};
static std::span<std::byte, recvMaxSize> recv_buffer{ recv_space };
unsigned long received_bytes = 0;

using IdType = int;
IdType my_id = -1;

struct FSagaPlayer
{
	IdType id;
	std::wstring nickname;

	// position
	float x, y, z;
	// orientation
	float look, up, right;
};
std::unordered_map<IdType, FSagaPlayer> everyClients{};
FSagaPlayer* localPlayer = nullptr;

constexpr app::packets::CS_SignInPacket sign_packet{ L"Iconer" };

char commands[256]{};
constexpr unsigned cmd_size = sizeof(commands);

coroutine::Coroutine Receiver();
void PullReceiveBuffer(const std::byte* last_offset);
bool SendPositionPacket();

int main()
{
	std::println("Client initiated");

	std::println("Creating a socket...");
	auto startup_r = net::Startup();
	if (startup_r.has_value())
	{
		return 5;
	}

	app_socket = net::Socket::CreateTcpSocket(net::IoCategory::Asynchronous);

	std::println("Binding...");

	app_socket.IsAddressReusable = true;

	auto client_address = net::IpAddress{ net::IpAddressFamily::IPv4, "127.0.0.1" };
	auto client_ep = net::EndPoint{ client_address, 40001U };

	// NOTICE: 클라이언트는 바인드 금지
	//auto bind_r = app_socket.Bind(client_ep);
	////auto bind_r = app_socket.BindAny(40001);

	std::println("Connecting to host...");
	server_address = net::IpAddress{ net::IpAddressFamily::IPv4, "127.0.0.1" };
	server_ep = net::EndPoint{ server_address, server_port };

	//auto connect_r = app_socket.Connect(server_ep);
	//auto connect_r = app_socket.ConnectToAny(server_port);
	auto connect_r = app_socket.ConnectToHost(server_port);
	if (connect_r.has_value())
	{
		return 3;
	}

	std::println("Sending nickname...");

	app::packets::CS_SignInPacket pk{};

	std::byte signin_buffer[recvMaxSize]{};
	sign_packet.Write(signin_buffer);

	net::IoContext send_signin_ctx{};
	auto sent_signin_r = app_socket.Send(send_signin_ctx, signin_buffer, app::packets::CS_SignInPacket::WannabeSize());
	if (not sent_signin_r.has_value())
	{
		return 2;
	}

	std::println("Starting receiving...");

	auto receiver = Receiver();
	//auto sender = Sender();

	receiver.StartAsync();
	//sender.StartAsync();

	while (true)
	{
		const auto inputs = ::scanf_s("%s", commands, cmd_size);
		if (EOF != inputs)
		{
			if (1 == inputs)
			{
				const auto& cmd = commands[0];
				if (cmd == 'q')
				{
					break;
				}
				else if (cmd == 'j') // join a room
				{
					app::packets::CS_EnterRoomPacket pk{ 0 };

					auto ptr = pk.Serialize();

					net::IoContext send_ctx{};
					auto sent_r = app_socket.Send(send_signin_ctx, ptr.get(), pk.WannabeSize());
					if (not sent_r.has_value())
					{
						return 3;
					}
				}
				else if (cmd == 'c') // create a room
				{
					app::packets::CS_EnterRoomPacket pk{ 0 };

					auto ptr = pk.Serialize();

					net::IoContext send_ctx{};
					auto sent_r = app_socket.Send(send_signin_ctx, ptr.get(), pk.WannabeSize());
					if (not sent_r.has_value())
					{
						return 3;
					}
				}
				else if (cmd == 'l') // leave room
				{
					app::packets::CS_EnterRoomPacket pk{ 0 };

					auto ptr = pk.Serialize();

					net::IoContext send_ctx{};
					auto sent_r = app_socket.Send(send_signin_ctx, ptr.get(), pk.WannabeSize());
					if (not sent_r.has_value())
					{
						return 3;
					}
				}
				else if (cmd == 'w')
				{
					localPlayer->y = ++localPlayer->y;
					SendPositionPacket();
				}
				else if (cmd == 'a')
				{
					localPlayer->x = --localPlayer->x;
					SendPositionPacket();
				}
				else if (cmd == 's')
				{
					localPlayer->y = --localPlayer->y;
					SendPositionPacket();
				}
				else if (cmd == 'd')
				{
					localPlayer->x = ++localPlayer->x;
					SendPositionPacket();
				}
				else if (cmd == 'z')
				{
					localPlayer->z = ++localPlayer->z;
					SendPositionPacket();
				}
				else if (cmd == 'x')
				{
					localPlayer->z = --localPlayer->z;
					SendPositionPacket();
				}
			}

			auto cmd = std::string_view{ commands, static_cast<size_t>(inputs) };
			if ("move up" == cmd)
			{
				localPlayer->z = ++localPlayer->z;
				SendPositionPacket();
			}
			else if ("move dw" == cmd)
			{
				localPlayer->z = --localPlayer->z;
				SendPositionPacket();
			}
			else if ("move fw" == cmd)
			{
				localPlayer->y = ++localPlayer->y;
				SendPositionPacket();
			}
			else if ("move bw" == cmd)
			{
				localPlayer->y = --localPlayer->y;
				SendPositionPacket();
			}
			else if ("move lt" == cmd)
			{
				localPlayer->x = --localPlayer->x;
				SendPositionPacket();
			}
			else if ("move rt" == cmd)
			{
				localPlayer->x = ++localPlayer->x;
				SendPositionPacket();
			}
			else if ("quit" == cmd)
			{
				break;
			}

			std::ranges::fill(commands, 0);
		}
	}

	app_socket.Close();

	net::Cleanup();
	return 0;
}

coroutine::Coroutine Receiver()
{
	std::byte temp_buffer[recvMaxSize]{};

	while (true)
	{
		auto recv = app_socket.Receive(recv_buffer.subspan(received_bytes));

		if (not recv.has_value())
		{
			std::println("Receive error: {}", recv.error());
			break;
		}
		else
		{
			const auto& bytes = recv.value();

			received_bytes += bytes;

			if (app::BasicPacket::MinSize() <= received_bytes)
			{
				app::BasicPacket basic_pk{};
				const auto seek = basic_pk.Read(recv_space);

				if (basic_pk.mySize <= 0)
				{
					//throw "error!";
					std::println("Packet's size is zero!");
				}
				else if (const auto sz = static_cast<unsigned long>(basic_pk.mySize); received_bytes <= sz)
				{
					switch (basic_pk.myProtocol)
					{
						case app::PacketProtocol::SC_SIGNIN_SUCCESS:
						{
							app::packets::SC_SucceedSignInPacket pk{};
							//util::Deserialize(seek, my_id);
							auto offset = pk.Read(recv_space);

							std::println("Local player's id is {}", pk.clientId);
							my_id = pk.clientId;

							auto r = everyClients.emplace(std::make_pair(pk.clientId, FSagaPlayer{}));

							localPlayer = std::addressof(r.first->second);
							localPlayer->id = pk.clientId;
							localPlayer->nickname = sign_packet.userName;

							PullReceiveBuffer(offset);
						}
						break;

						case app::PacketProtocol::SC_SIGNIN_FAILURE:
						{
							app::packets::SC_FailedSignInPacket pk{};
							auto offset = pk.Read(recv_space);

							std::println("Local player can't get an id from server due to {}", pk.errCause);

							PullReceiveBuffer(offset);
						}
						break;

						case app::PacketProtocol::SC_CREATE_PLAYER:
						{
							app::packets::SC_CreatePlayerPacket pk{};
							auto offset = pk.Read(recv_space);

							std::println("A player {} is created",  pk.clientId);
							everyClients.emplace(std::make_pair(pk.clientId, FSagaPlayer{}));

							PullReceiveBuffer(offset);
						}
						break;

						case app::PacketProtocol::SC_REMOVE_PLAYER:
						{
							app::packets::SC_DestroyPlayerPacket pk{};
							auto offset = pk.Read(recv_space);

							std::println("A player {} is destroyed(disconnected)", pk.clientId);

							PullReceiveBuffer(offset);
						}
						break;

						case app::PacketProtocol::SC_MOVE_CHARACTER:
						{
							app::packets::SC_UpdatePositionPacket pk{ 0, 0, 0, 0 };
							auto offset = pk.Read(recv_space);

							std::println("Player id {}: pos({},{},{})", pk.clientId, pk.x, pk.y, pk.z);

							PullReceiveBuffer(offset);
						}
						break;

						case app::PacketProtocol::SC_UPDATE_CHARACTER:
						{
						}
						break;
					}
				}
			}
		}
	}

	co_return;
}

void
PullReceiveBuffer(const std::byte* last_offset)
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

bool SendPositionPacket()
{
	app::packets::CS_UpdatePositionPacket position_pk{ localPlayer->x, localPlayer->y, localPlayer->z };

	auto serialized = position_pk.Serialize();

	net::IoContext send_position_ctx{};
	auto sent_position_r = app_socket.Send(send_position_ctx, serialized.get(), app::packets::CS_UpdatePositionPacket::WannabeSize());
	if (not sent_position_r.has_value())
	{
		return false;
	}

	send_position_ctx.Clear();

	return true;
}
