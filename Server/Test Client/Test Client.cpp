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

	app_socket = net::Socket::CreateTcpSocket(net::IoCategory::Synchronous);

	app_socket.BindHost(40001);
	app_socket.IsAddressReusable = true;

	server_address = net::IpAddress{ net::IpAddressFamily::IPv4, "127.0.0.1" };
	server_ep = net::EndPoint{ server_address, 40000 };
	app_socket.Connect(server_ep);

	std::byte recv_buffer[512]{};
	while (true)
	{
		auto recv = app_socket.Receive(recv_buffer);

		if (recv.has_value())
		{
			std::cout << "Receive error: \n" << std::to_string(recv.error());
			break;
		}
		else
		{
		}
	}
}