module;
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <MSWSock.h>

module Demo.Framework;
// ReSharper disable CppMemberFunctionMayBeStatic

demo::Framework::Framework(size_t clients_count, std::uint16_t port)
	: everyUsers(clients_count)
{
	
}

void
demo::Framework::Awake()
{
	
}

bool
demo::Framework::Start() noexcept
{
	return false;
}

void
demo::Framework::Update()
{
	
}

void
demo::Framework::Cleanup() noexcept
{
	
}
