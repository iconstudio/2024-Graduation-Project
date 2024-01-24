#include "Framework.hpp"

using namespace iconer;

net::Socket serverListener{};
net::IoCompletionPort ioCompletionPort{};
constexpr std::uint16_t serverPort{ 40000 };
constexpr app::User::HandleType serverID = 0;

std::vector<std::jthread> serverWorkers{};
constexpr size_t workersCount = 6;

app::UserManager userManager{};
constexpr size_t userNumber = 3000;

app::User localUser{ net::Socket{}, 0 };
constexpr app::User::HandleType beginUserID = 1;

int main()
{
	std::cout << ("=========$ Server $=========\n");
	const auto startup_err = net::Startup();

	const net::IpAddress ip = net::IpAddress{ net::IpAddressFamily::IPv4, "127.0.0.1" };
	const net::EndPoint serverAddress = net::EndPoint{ ip, 40000 };

	std::cout << ("=========== Init ===========\n");
	std::cout << ("\tcreating the listener...\n");

	if (not net::Socket::TryCreate(net::IoCategory::Asynchronous, net::InternetProtocol::TCP, net::IpAddressFamily::IPv4, ::serverListener))
	{
		throw std::exception{ "Error when creating the listener socket." };
	}

	std::cout << std::format("\tbinding the listener to port {}...\n", ::serverPort);

	::serverListener.BindHost(::serverPort).and_then(
		[](net::ErrorCode&& code) -> std::optional<bool> {
		const std::string msg = std::format("Error when binding a address to the listener socket ({})", code);
		throw msg;
	});

	auto result = net::IoCompletionPort::Create(uint32_t(::workersCount)).and_then(
		[&](net::IoCompletionPort&& port) noexcept -> std::expected<bool, net::ErrorCode> {
		::ioCompletionPort = std::move(port);
		return true;
	}).transform_error([](net::ErrorCode&& code) noexcept -> std::expected<bool, net::ErrorCode> {
		return false;
	});

	if (not result.value())
	{
		throw std::exception{ "Error when creating the io completion port." };
	}

	std::cout << "\tallocating memory of buffers...\n";

	::userManager.Reserve(::userNumber);
	::serverWorkers.reserve(::workersCount);

	auto user_factory = app::SessionFactory<app::User>{};

	std::cout << std::format("\tcreating {} users...\n", ::userNumber);

	app::User::HandleType id = ::beginUserID;
	for (size_t i = 0; i < ::userNumber; ++i)
	{
		net::Socket socket;
		if (not net::Socket::TryCreate(net::IoCategory::Asynchronous, net::InternetProtocol::TCP, net::IpAddressFamily::IPv4, socket))
		{
			throw std::exception{ "Error when creating a socket" };
		}

		if (not ioCompletionPort.Register(socket, id))
		{
			//auto user = user_factory.Create(std::move(socket), id++);
			app::User user{ std::move(socket), id++ };
			userManager.Add(std::move(user));
		}
		else
		{
			throw std::exception{ "Error when registering a socket" };
		}
	}

	std::cout << std::format("\tgenerating {} workers...\n", ::workersCount);

	for (size_t i = 0; i < ::workersCount; ++i)
	{
		::serverWorkers.emplace_back(::Worker, i);
	}

	std::cout << ("\tawakening workers...\n");

	for (auto& [id, user] : ::userManager)
	{
		if (not user.OnAwake())
		{
			throw std::exception{ "Error when awakening a user." };
		}
	}

	std::cout << ("=========== Start ===========\n");
	std::cout << ("\topening the listener...\n");

	if (serverListener.Open().has_value())
	{
		std::cout << "The listener is opened.\n";
	}

	std::cout << ("\treserving acceptance of users...\n");

	for (auto& [id, user] : ::userManager)
	{
		auto& ctx = user.myContext;
		//ctx.ResetOperation(test::IoOperation::Accept);

		auto acceptance = serverListener.ReserveAccept(ctx, user.mySocket);
		if (acceptance)
		{
			throw std::exception{ "Error when reserving acceptance of a socket." };
		}
	}

	std::cout << ("=========== Update ===========\n");

	char command[256]{};
	constexpr unsigned cmd_size = sizeof(command);

	while (true)
	{
		auto input = ::scanf_s("%s", command, cmd_size);
		if (EOF != input)
		{
			if (command[0] == 'q')
			{
				break;
			}
		}
	}

	std::cout << ("========== Destroy ===========\n");

	std::cout << ("========== Clean up ==========\n");
	const auto cleanup_err = net::Cleanup();
}
