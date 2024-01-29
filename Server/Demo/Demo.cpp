#pragma comment(lib, "Server.lib")
import Demo.Framework;
import <iostream>;

demo::Framework serverFramework{};

int main()
{
	std::cout << ("=========$ Server $=========\n");

	std::cout << ("=========== Init ===========\n");
	serverFramework.Awake();

	std::cout << ("=========== Start ===========\n");
	serverFramework.Start();

	std::cout << ("=========== Update ===========\n");
	serverFramework.Update();

	std::cout << ("========== Destroy ===========\n");
	serverFramework.Destroy();

	std::cout << ("========== Clean up ==========\n");
	serverFramework.Cleanup();
}
