import Iconer.Net;
import Iconer.Net.ErrorCode;
import Iconer.Utility.Handler;
import Iconer.Coroutine;
import Iconer.Coroutine.Task;
import <iostream>;

using namespace iconer;

int main()
{
	util::Handler<int> handler{};
	handler = 5;

	std::cout << "Hello World!\n";

	const auto code = net::ErrorCode::WSAEPROVIDERFAILEDINIT;
	const auto txt = std::to_string(code);
	std::cout << "Code: " << txt << '\n';
}
