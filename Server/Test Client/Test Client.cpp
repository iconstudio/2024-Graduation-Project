﻿#pragma comment(lib, "Server.lib")
import <cstdio>;
import <string_view>;
import <utility>;
import <memory>;
import <type_traits>;
import <expected>;
import <algorithm>;
import <print>;

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

struct FSagaPlayerCharacter
{
	// position
	float x, y, z;
	// orientation
	float look, up, right;
};

using IdType = int;
IdType my_id = -1;
net::IoContext send_ctx{};
FSagaPlayerCharacter player{};

char commands[256]{};
constexpr unsigned cmd_size = sizeof(commands);

coroutine::Coroutine Receiver();
void PullReceiveBuffer(const std::byte* last_offset);
bool SendPositionPacket()
{
	app::packets::CS_UpdatePositionPacket position_pk{ player.x, player.y, player.z };

	auto serialized = position_pk.Serialize();

	auto sent_signin_r = app_socket.Send(send_ctx, serialized.get(), app::packets::CS_UpdatePositionPacket::WannabeSize());
	if (not sent_signin_r.has_value())
	{
		return false;
	}

	send_ctx.Clear();

	return true;
}

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

	std::println("Starting receiving...");

	app::packets::CS_SignInPacket pk{};

	auto receiver = Receiver();
	//auto sender = Sender();

	receiver.StartAsync();
	//sender.StartAsync();

	constexpr app::packets::CS_SignInPacket sign_packet{ L"Iconer" };

	std::byte signin_buffer[recvMaxSize]{};
	sign_packet.Write(signin_buffer);
	auto it = pk.Read(signin_buffer, app::packets::CS_SignInPacket::WannabeSize());

	auto sent_signin_r = app_socket.Send(send_ctx, signin_buffer, app::packets::CS_SignInPacket::WannabeSize());
	if (not sent_signin_r.has_value())
	{
		return 2;
	}

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
				else if (cmd == 'w')
				{
					player.y = ++player.y;
					SendPositionPacket();
				}
				else if (cmd == 'a')
				{
					player.x = --player.x;
					SendPositionPacket();
				}
				else if (cmd == 's')
				{
					player.y = --player.y;
					SendPositionPacket();
				}
				else if (cmd == 'd')
				{
					player.x = ++player.x;
					SendPositionPacket();
				}
				else if (cmd == 'q')
				{
					player.z = ++player.z;
					SendPositionPacket();
				}
				else if (cmd == 'e')
				{
					player.z = --player.z;
					SendPositionPacket();
				}
			}

			auto cmd = std::string_view{ commands, static_cast<size_t>(inputs) };
			if ("move up" == cmd)
			{
				player.z = ++player.z;
				SendPositionPacket();
			}
			else if ("move dw" == cmd)
			{
				player.z = --player.z;
				SendPositionPacket();
			}
			else if ("move fw" == cmd)
			{
				player.y = ++player.y;
				SendPositionPacket();
			}
			else if ("move bw" == cmd)
			{
				player.y = --player.y;
				SendPositionPacket();
			}
			else if ("move lt" == cmd)
			{
				player.x = --player.x;
				SendPositionPacket();
			}
			else if ("move rt" == cmd)
			{
				player.x = ++player.x;
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

							PullReceiveBuffer(offset);
						}
						break;

						case app::PacketProtocol::SC_SIGNIN_FAILURE:
						{
							app::packets::SC_FailedSignInPacket pk{};
							//util::Deserialize(seek, my_id);
							auto offset = pk.Read(recv_space);

							std::println("Local player can't get an id from server due to {}", pk.errCause);

							PullReceiveBuffer(offset);
						}
						break;

						case app::PacketProtocol::SC_CREATE_PLAYER:
						{
						}
						break;

						case app::PacketProtocol::SC_MOVE_CHARACTER:
						{
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
