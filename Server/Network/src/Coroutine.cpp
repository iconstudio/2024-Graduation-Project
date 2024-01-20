module Net.Coroutine;
import <thread>;

net::coroutine::Coroutine::~Coroutine()
{
	if (triggerHandle)
	{
		delete triggerHandle;
	}
}

void
net::coroutine::Coroutine::Start()
const
{
	if (myHandle and not isTriggered)
	{
		isTriggered = true;

		myHandle();
	}
}

void
net::coroutine::Coroutine::StartAsync()
const
{
	if (myHandle and not isTriggered)
	{
		isTriggered = true;
		static const auto pred = [](std::coroutine_handle<void> handle) -> void {
			if (handle)
			{
				handle();
			}
		};

		std::thread{ pred, myHandle }.detach();
	}
}

void
net::coroutine::Coroutine::Resume()
const
{
	if (myHandle and isTriggered)
	{
		myHandle();
	}
}
void
net::coroutine::Coroutine::operator()()
const
{
	if (myHandle and isTriggered)
	{
		myHandle();
	}
}

void
net::coroutine::Action::Resume()
const
{
	if (myHandle)
	{
		myHandle();
	}
}

void
net::coroutine::Action::operator()()
const
{
	if (myHandle)
	{
		myHandle();
	}
}
