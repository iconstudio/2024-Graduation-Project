#pragma comment(lib, "Server.lib")
#include <iostream>

import Iconer.Net;
import Iconer.Net.ErrorCode;
import Iconer.Net.IpAddress;
import Iconer.Net.EndPoint;
import Iconer.Net.Socket;
import Iconer.Net.IoCompletionPort;
import Iconer.Application.User;
import Iconer.Application.UserManager;

using namespace iconer;

constexpr size_t serverID = 0;
app::User localUser{ net::Socket{}, 0 };
app::UserManager userManager{};

int main()
{
	std::cout << ("=========$ Server $=========\n");
	const auto startup_err = net::Startup();

	const net::IpAddress ip = net::IpAddress{ net::IpAddressFamily::IPv4, "127.0.0.1" };
	const net::EndPoint serverAddress = net::EndPoint{ ip, 40000 };

	std::cout << ("=========== Init ===========\n");
	userManager.Reserve(3000);

	std::cout << ("=========== Start ===========\n");

	auto find_it = userManager.Find(0);
	auto seek_it = userManager.Search([](const app::User& user) noexcept -> bool {
		return user.GetHandle() == 2;
	});

	std::cout << ("=========== Update ===========\n");

	char command[256]{};
	constexpr unsigned cmd_size = sizeof(command);

	while (true)
	{
		auto input = ::scanf_s("%s", command, cmd_size);
		if (EOF != input)
		{
			if (command[0] == 'q')
			{
				break;
			}
		}
	}

	std::cout << ("========== Destroy ===========\n");

	std::cout << ("========== Clean up ==========\n");
	const auto cleanup_err = net::Cleanup();
}
