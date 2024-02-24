module TestClient;
import <print>;
import <thread>;

int
test::Update()
{
	std::println("Starting receiving...");

	std::thread th{ Receiver };

	char commands[256]{};
	constexpr unsigned cmd_size = sizeof(commands);

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
				else if (cmd == 'c') // create a room
				{
					if (auto sr = SendCreateRoomPacket(L"Test Room"); not sr.has_value())
					{
						return 3;
					}
				}
				else if (cmd == 'j') // join a room
				{
					if (auto sr = SendJoinRoomPacket(22); not sr.has_value())
					{
						return 3;
					}
				}
				else if (cmd == 'l') // leave room
				{
					if (auto sr = SendLeaveRoomPacket(); not sr.has_value())
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

	th.join();

	return 0;
}
