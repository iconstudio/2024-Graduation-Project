#pragma comment(lib, "Server.lib")
#include <iostream>

import Iconer.Net;
import Iconer.Net.IpAddress;
import Iconer.Net.EndPoint;
import Iconer.Net.Socket;

using namespace iconer;

net::Socket app_socket{};
net::IpAddress server_address{};
net::EndPoint server_ep{};

int main()
{
	std::cout << "Client initiated\n";

	std::cout << "Creating a socket...\n";
	auto startup_r = net::Startup();
	app_socket = net::Socket::CreateTcpSocket(net::IoCategory::Synchronous);

	std::cout << "Binding...\n";
	auto bind_r = app_socket.BindHost(40001);
	app_socket.IsAddressReusable = true;

	std::cout << "Connecting to host...\n";
	server_address = net::IpAddress{ net::IpAddressFamily::IPv4, "127.0.0.1" };
	server_ep = net::EndPoint{ server_address, 40000 };
	//auto connect_r = app_socket.Connect(server_ep);
	auto connect_r = app_socket.ConnectToHost(40000U);
	if (connect_r.has_value())
	{
		return 1;
	}

	std::cout << "Starting receiving...\n";

	std::byte recv_buffer[512]{};
	while (true)
	{
		auto recv = app_socket.Receive(recv_buffer);

		if (not recv.has_value())
		{
			std::cout << "Receive error: \n" << std::to_string(recv.error());
			break;
		}
		else
		{
		}
	}

	net::Cleanup();
	return 0;
}