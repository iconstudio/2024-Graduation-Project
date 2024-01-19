#pragma comment(lib, "Modern Network.lib")

import Demo.Framework;

demo::Framework appFramework{ 50ULL, 40000U };

int
main()
{
	appFramework.Awake();
	appFramework.Start();
	appFramework.Update();
	appFramework.Cleanup();
}
