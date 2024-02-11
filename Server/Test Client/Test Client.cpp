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
constexpr std::uint16_t server_port = 40000;

static inline constexpr size_t recvMaxSize = 512;
static std::byte recv_space[recvMaxSize]{};
static std::span<std::byte, recvMaxSize> recv_buffer{ recv_space };
unsigned long received_bytes = 0;

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
void PullReceiveBuffer(const std::byte* last_offset);

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

	app_socket.IsAddressReusable = true;

	auto client_address = net::IpAddress{ net::IpAddressFamily::IPv4, "127.0.0.1" };
	auto client_ep = net::EndPoint{ client_address, 40001U };
	
	// NOTICE: 클라이언트는 바인드 금지
	//auto bind_r = app_socket.Bind(client_ep);
	////auto bind_r = app_socket.BindAny(40001);

	std::cout << "Connecting to host...\n";
	server_address = net::IpAddress{ net::IpAddressFamily::IPv4, "127.0.0.1" };
	server_ep = net::EndPoint{ server_address, server_port };

	//auto connect_r = app_socket.Connect(server_ep);
	//auto connect_r = app_socket.ConnectToAny(server_port);
	auto connect_r = app_socket.ConnectToHost(server_port);
	if (connect_r.has_value())
	{
		return 3;
	}

	std::cout << "Starting receiving...\n";

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

	send_ctx.Clear();

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
	std::byte temp_buffer[recvMaxSize]{};

	while (true)
	{
		auto recv = app_socket.Receive(recv_buffer.subspan(received_bytes));

		if (not recv.has_value())
		{
			std::cout << "Receive error: " << std::to_string(recv.error()) << '\n';
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
					std::cout << "Packet's size is zero!\n";
				}
				else if (const auto sz = static_cast<unsigned long>(basic_pk.mySize); received_bytes <= sz)
				{
					switch (basic_pk.myProtocol)
					{
						case app::PacketProtocol::SC_SIGNIN_SUCCESS:
						{
							app::packets::SC_SucceedSignInPacket pk{};
							//util::Deserialize(seek, clientId);
							auto offset = pk.Read(recv_space);

							std::cout << "Local player's id is " << pk.clientId << '\n';
							clientId = pk.clientId;

							PullReceiveBuffer(offset);
						}
						break;

						case app::PacketProtocol::SC_SIGNIN_FAILURE:
						{
							app::packets::SC_FailedSignInPacket pk{};
							//util::Deserialize(seek, clientId);
							auto offset = pk.Read(recv_space);

							std::cout << "Local player can't get an id from server due to {}" << pk.errCause << '\n';

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
