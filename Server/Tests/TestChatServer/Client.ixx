export module Test.Client;
import <cstdint>;
import <string>;
import Iconer.Net.Socket;
import Test.Context;
import Test.ChatMsgContext;

export namespace test
{
	class Client
	{
	public:
		Client() noexcept = default;
		~Client() noexcept = default;

		std::uintptr_t myID;
		iconer::net::Socket* mySocket;
		test::ExContext myContext;

		std::string myName;
		std::string lastMessage;
	};
}
