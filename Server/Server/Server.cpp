import Iconer.Net;
import Iconer.Net.ErrorCode;
import Iconer.Coroutine;
import Iconer.Coroutine.Task;
import Iconer.Net.Socket;
import <iostream>;
import <format>;

using namespace iconer;

int main()
{
	std::cout << "Hello World!\n";

	auto start_err = net::Startup();

	net::Socket socket;


	auto end_err = net::Cleanup();
}
