#pragma comment(lib, "Server.lib")
import Demo.Framework;
import <print>;

demo::Framework serverFramework{};

int main()
{
	std::println("=========$ Server $=========");

	std::println("=========== Init ===========");
	serverFramework.Awake();

	std::println("=========== Start ===========");
	serverFramework.Start();

	std::println("=========== Update ===========");
	serverFramework.Update();

	std::println("========== Destroy ===========");
	serverFramework.Destroy();

	std::println("========== Clean up ==========");
	serverFramework.Cleanup();
}
