#pragma comment(lib, "Server.lib")
#include <cstdio>
#include <iostream>

import Iconer.Coroutine;
import Iconer.Net;
import Iconer.Net.IpAddress;
import Iconer.Net.EndPoint;
import Iconer.Net.Socket;
import Iconer.Application.Packet;

using namespace iconer;

net::Socket app_socket{};
net::IpAddress server_address{};
net::EndPoint server_ep{};

std::byte recv_buffer[512]{};
net::IoContext recv_ctx{};
net::IoContext send_ctx{};

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
	while (true)
	{
		auto recv = co_await app_socket.MakeReceiveTask(recv_ctx, recv_buffer);

		if (not recv.has_value())
		{
			std::cout << "Receive error: \n" << std::to_string(recv.error());
			break;
		}
		else
		{
		}

		recv_ctx.Clear();
	}
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