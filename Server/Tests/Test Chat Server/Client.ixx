export module Test.Client;
import <cstdint>;
import <string>;
import Net.Socket;
import Test.Context;

export namespace test
{
	class Client
	{
	public:
		Client() noexcept = default;
		~Client() noexcept = default;

		std::uintptr_t myID;
		net::Socket* mySocket;
		test::ExContext myContext;

		std::string myName;
		std::string lastMessage;
	};
}
