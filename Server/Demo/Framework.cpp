module;
#include <cstdio>

module Demo.Framework;
import <atomic>;

void
demo::Framework::Update()
{
	LockPhase();

	char command[256]{};
	constexpr unsigned cmd_size = sizeof(command);

	while (true)
	{
		auto input = ::scanf_s("%s", command, cmd_size);
		if (EOF != input)
		{
			if (command[0] == 'q')
			{
				CancelWorkers();

				break;
			}
		}
	}

	UnlockPhase();
}

void
demo::Framework::LockPhase()
noexcept
{
	std::atomic_thread_fence(std::memory_order_acquire);
}

void
demo::Framework::UnlockPhase()
noexcept
{
	std::atomic_thread_fence(std::memory_order_release);
}
