#pragma comment(lib, "Server.lib")
#include <cstdio>
#include <iostream>

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

static std::byte recv_space[512]{};
static std::span<std::byte, 512> recv_buffer{ recv_space };
unsigned long received_bytes = 0;

net::IoContext recv_ctx{};
net::IoContext send_ctx{};

using IdType = int;
IdType clientId = -1;

volatile bool cmd_assigned = false;
char command[256]{};
constexpr unsigned cmd_size = sizeof(command);

struct FSagaPlayerCharacter
{
	// position
	float x, y, z;
	// orientation
	float look, up, right;
};

coroutine::Coroutine Receiver();
coroutine::Coroutine Sender();
void PullReceiveBuffer(const unsigned long size);

int main()
{
	std::cout << "Client initiated\n";

	std::cout << "Creating a socket...\n";
	auto startup_r = net::Startup();
	if (startup_r.has_value())
	{
		return 5;
	}

	app_socket = net::Socket::CreateTcpSocket(net::IoCategory::Asynchronous);

	std::cout << "Binding...\n";
	auto bind_r = app_socket.BindHost(40001);
	if (bind_r.has_value())
	{
		return 4;
	}

	app_socket.IsAddressReusable = true;

	std::cout << "Connecting to host...\n";
	//server_address = net::IpAddress{ net::IpAddressFamily::IPv4, "127.0.0.1" };
	//server_ep = net::EndPoint{ server_address, 40000 };
	//auto connect_r = app_socket.Connect(server_ep);

	auto connect_r = app_socket.ConnectToHost(40000U);
	if (connect_r.has_value())
	{
		return 3;
	}

	std::cout << "Starting receiving...\n";

	app::packets::SignInPacket pk{};

	auto receiver = Receiver();
	//auto sender = Sender();
	
	receiver.StartAsync();
	//sender.StartAsync();

	constexpr app::packets::SignInPacket sign_packet{ L"Iconer" };

	std::byte signin_buffer[512]{};
	sign_packet.Write(signin_buffer);
	auto it = pk.Read(signin_buffer, app::packets::SignInPacket::WannabeSize());

	auto sent_signin_r = app_socket.Send(send_ctx, signin_buffer, app::packets::SignInPacket::WannabeSize());
	if (not sent_signin_r.has_value())
	{
		return 2;
	}

	while (true)
	{
		auto input = ::scanf_s("%s", command, cmd_size);
		if (EOF != input)
		{
			if (command[0] == 'q')
			{
				cmd_assigned = true;
				break;
			}
		}
	}

	app_socket.Close();

	net::Cleanup();
	return 0;
}

coroutine::Coroutine Receiver()
{
	std::byte temp_buffer[512]{};

	while (true)
	{
		auto recv = co_await app_socket.MakeReceiveTask(recv_ctx, recv_buffer.subspan(received_bytes));

		if (not recv.has_value())
		{
			std::cout << "Receive error: \n" << std::to_string(recv.error());
			break;
		}
		else
		{
			const auto& bytes = recv.value();

			received_bytes += bytes;

			if (received_bytes <= app::BasicPacket::MinSize())
			{
				app::BasicPacket basic_pk{};
				const auto seek = basic_pk.Read(recv_space);

				if (basic_pk.mySize <= 0)
				{
					throw "error!";
				}
				else if (const auto sz = static_cast<unsigned long>(basic_pk.mySize); received_bytes <= sz)
				{
					switch (basic_pk.myProtocol)
					{
						case app::PacketProtocol::SC_SIGNIN_SUCCESS:
						{
							util::Deserialize(seek, clientId);

							std::cout << "Local player's id is " << clientId << '\n';

							const unsigned long wanna_size = sz + sizeof(clientId);
							PullReceiveBuffer(wanna_size);
						}
						break;

						case app::PacketProtocol::SC_SIGNIN_FAILURE:
						{
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

		recv_ctx.Clear();
	}

	co_return;
}

coroutine::Coroutine Sender()
{
	while (true)
	{
		if (cmd_assigned)
		{
			break;
		}
		//auto recv = co_await app_socket.MakeSendTask(send_ctx, recv_buffer);

		//if (not recv.has_value())
		{
			//std::cout << "Receive error: \n" << std::to_string(recv.error());
			//break;
		}

		//send_ctx.Clear();
	}

	co_return;
}

void
PullReceiveBuffer(const unsigned long size)
{
}
