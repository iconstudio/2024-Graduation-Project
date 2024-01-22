import Iconer.Net;
import Iconer.Net.ErrorCode;
import Iconer.Coroutine;
import Iconer.Coroutine.Task;
import Iconer.Net.Socket;
import Iconer.Net.IoCompletionPort;
import <iostream>;
//import <format>;

using namespace iconer;

int main()
{
	std::cout << "Hello World!\n";

	auto start_err = net::Startup();

	net::IoCompletionPort port;

	net::Socket socket;
	socket = net::Socket::Create(net::IoCategory::Synchronous, net::InternetProtocol::TCP, net::IpAddressFamily::IPv4);

	//std::cout << std::format("{}\n", socket.IsAddressReusable);
	auto bind = socket.BindHost(40000);

	net::IoContext context{};
	port.Schedule(context, 9, 0);

	auto end_err = net::Cleanup();
}
