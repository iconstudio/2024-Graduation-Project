#pragma once
#pragma comment(lib, "Server.lib")
#include <cstdint>
#include <system_error>
#include <utility>
#include <expected>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

import Iconer.Net;
import Iconer.Net.ErrorCode;
import Iconer.Net.IpAddress;
import Iconer.Net.EndPoint;
import Iconer.Net.Socket;
import Iconer.Net.IoCompletionPort;
import Iconer.Application.User;
import Iconer.Application.UserManager;

void Worker(size_t index);
