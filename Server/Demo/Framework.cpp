module Demo.Framework;
import <atomic>;

bool
demo::Framework::CreateListenerSocket()
noexcept
{
	return iconer::net::Socket::TryCreate(iconer::net::IoCategory::Asynchronous, iconer::net::InternetProtocol::TCP, iconer::net::IpAddressFamily::IPv4, serverListener);
}

bool
demo::Framework::InitializeListener()
noexcept
{
	if (serverListener.BindHost(serverPort).has_value())
	{
		return false;
	}

	serverListener.IsAddressReusable = true;

	return true;
}

bool
demo::Framework::InitializeCompletionPort(iconer::net::ErrorCode& error_code)
noexcept
{
	return iconer::net::IoCompletionPort::Create(uint32_t(workersCount)).and_then(
		[&](iconer::net::IoCompletionPort&& port) noexcept -> std::expected<bool, iconer::net::ErrorCode> {
		ioCompletionPort = std::move(port);
		return true;
	}).transform_error(
		[&error_code](iconer::net::ErrorCode&& code) noexcept -> std::expected<bool, iconer::net::ErrorCode> {
		error_code = std::move(error_code);
		return false;
	}).value_or(false);
}

bool
demo::Framework::InitializeUsers()
{
	auto user_factory = iconer::app::SessionFactory<iconer::app::User>{};

	IdType id = beginUserID;
	for (size_t i = 0; i < maxUsersNumber; ++i)
	{
		if (iconer::net::Socket socket; iconer::net::Socket::TryCreate(iconer::net::IoCategory::Asynchronous, iconer::net::InternetProtocol::TCP, iconer::net::IpAddressFamily::IPv4, socket))
		{
			if (not ioCompletionPort.Register(socket, id).has_value())
			{
				auto user = user_factory.Create(id++, std::move(socket));
				userManager.Add(std::move(user));
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool
demo::Framework::StartAccepts()
{
	for (auto& [id, user] : userManager)
	{
		user.SetOperation(iconer::app::UserOperations::Accept);

		if (not Schedule(user, id, 0))
		{
			return false;
		}
	}

	return true;
}

void
demo::Framework::LockPhase()
noexcept
{
	std::atomic_thread_fence(std::memory_order_acquire);
}

void
demo::Framework::UnlockPhase()
noexcept
{
	std::atomic_thread_fence(std::memory_order_release);
}
