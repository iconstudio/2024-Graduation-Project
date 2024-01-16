module;
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <MSWSock.h>

module Demo.Framework;
import <memory>;
// ReSharper disable CppMemberFunctionMayBeStatic

demo::Framework::Framework(size_t clients_count, std::uint16_t port)
	: listenSocket()
	, listenContext()
	, everyUsers(clients_count)
	, cancellationSource()
{}

void
demo::Framework::Awake()
{
	iconer::user_id_t id = startUserID;

	for (size_t i = 0; i < everyUsers.GetCapacity(); ++i)
	{
		auto ptr = std::make_unique<iconer::User>(id++);
		if (not ptr)
		{
			throw "Cannot allocate an user entity";
		}

		ptr->SetState<iconer::user_status::None>();

		everyUsers.Add(std::move(ptr));
	}
}

bool
demo::Framework::Start() noexcept
{
	for (auto& user_ptr : everyUsers)
	{
		auto user = user_ptr.get();

		if (user->SetState<iconer::user_status::Listening>())
		{}
	}

	return false;
}

void
demo::Framework::Update()
{}

void
demo::Framework::Cleanup() noexcept
{}
