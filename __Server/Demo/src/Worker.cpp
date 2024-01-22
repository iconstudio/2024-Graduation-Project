module;
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <MSWSock.h>

module Demo.Framework;

void
demo::Worker(Framework& framework, std::stop_token&& token)
{
	while (true)
	{
		if (token.stop_requested())
		{
			break;
		}

		
	}
}

