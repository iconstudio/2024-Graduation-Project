import <cstdio>;
//import <print>;
import <iostream>;

import Test.Framework;

test::Framework serverFramework{};

int main()
{
	std::cout << ("=========$ Server $=========\n");
	test::ServerPreset my_setup
	{
		.serverID = 0,
		.serverAddress = iconer::net::EndPoint{ iconer::net::IpAddress{ iconer::net::IpAddressFamily::IPv4, "127.0.0.1" }, 40000 }
	};

	std::cout << ("=========== Init ===========\n");
	serverFramework.Awake(std::move(my_setup));

	std::cout << ("=========== Start ===========\n");
	serverFramework.Start(6);

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
	serverFramework.Destroy();

	std::cout << ("========== Clean up ==========\n");
	serverFramework.Cleanup();
}
