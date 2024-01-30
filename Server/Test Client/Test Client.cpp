﻿#pragma comment(lib, "Server.lib")
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

app::packets::SignInPacket sign_packet{};

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
	app_socket = net::Socket::CreateTcpSocket(net::IoCategory::Asynchronous);

	std::cout << "Binding...\n";
	auto bind_r = app_socket.BindHost(40001);
	app_socket.IsAddressReusable = true;

	std::cout << "Connecting to host...\n";
	//server_address = net::IpAddress{ net::IpAddressFamily::IPv4, "127.0.0.1" };
	//server_ep = net::EndPoint{ server_address, 40000 };
	//auto connect_r = app_socket.Connect(server_ep);

	auto connect_r = app_socket.ConnectToHost(40000U);
	if (connect_r.has_value())
	{
		return 1;
	}

	std::cout << "Starting receiving...\n";
	
	std::byte signin_buffer[512]{};

	constexpr auto&& nickname = L"Iconer";
	std::copy_n(nickname, sizeof(nickname) / sizeof(wchar_t), sign_packet.userName);

	sign_packet.Write(signin_buffer);

	app::packets::SignInPacket pk{};

	auto it = pk.Read(signin_buffer, app::packets::SignInPacket::ByteSize());

	auto receiver = Receiver();
	//auto sender = Sender();
	
	receiver.StartAsync();
	//sender.StartAsync();

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