module TestClient;
import <print>;

int
test::Update()
{
	std::println("Starting receiving...");

	auto receiver = Receiver();
	receiver.StartAsync();

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
					if (auto sent_leave_r = SendCreateRoomPacket(L"Test Room"); not sent_leave_r.has_value())
					{
						return 3;
					}
				}
				else if (cmd == 'j') // join a room
				{
					if (auto sent_leave_r = SendJoinRoomPacket(22); not sent_leave_r.has_value())
					{
						return 3;
					}
				}
				else if (cmd == 'l') // leave room
				{
					if (auto sent_leave_r = SendLeaveRoomPacket(); not sent_leave_r.has_value())
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

	return 0;
}
