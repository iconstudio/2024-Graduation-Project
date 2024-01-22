#pragma comment(lib, "Server.lib")
#include "gtest/gtest.h"

import Iconer.Net;

TEST(TestCaseName, TestName)
{
  EXPECT_TRUE(iconer::net::Startup());

  
  EXPECT_EQ(1, 1);
  
  EXPECT_TRUE(iconer::net::Cleanup());
}
