module;
#include <string_view>
#include <atomic>

module Demo.Framework;
import Iconer.Net.IpAddress;
import Iconer.Net.EndPoint;
import Iconer.Application.IObject;

bool
demo::Framework::CreateListenerSockets()
noexcept
{
	const bool lobby_sk_created = iconer::net::Socket::TryCreate(iconer::net::IoCategory::Asynchronous, iconer::net::InternetProtocol::TCP, iconer::net::IpAddressFamily::IPv4, serverListener);

	const bool game_sk_created = iconer::net::Socket::TryCreate(iconer::net::IoCategory::Asynchronous, iconer::net::InternetProtocol::UDP, iconer::net::IpAddressFamily::IPv4, gameListener);

	return lobby_sk_created and game_sk_created;
}

bool
demo::Framework::InitializeLobbyListener()
noexcept
{
	auto server_address = iconer::net::IpAddress{ iconer::net::IpAddressFamily::IPv4, "127.0.0.1" };
	auto server_ep = iconer::net::EndPoint{ server_address, lobbySidePort };

	//if (serverListener.Bind(server_ep).has_value())
	//if (serverListener.BindHost(lobbySidePort).has_value())
	if (serverListener.BindAny(lobbySidePort).has_value())
	{
		return false;
	}

	serverListener.IsAddressReusable = true;

	return true;
}

bool
demo::Framework::InitializeGameListener()
noexcept
{
	if (gameListener.BindAny(gameSidePort).has_value())
	{
		return false;
	}

	gameListener.IsAddressReusable = true;

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
				userManager->Add(std::move(user));
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
demo::Framework::InitializeRooms()
{
	auto room_factory = iconer::app::SessionFactory<iconer::app::Room>{};

	IdType id = beginRoomID;
	for (size_t i = 0; i < maxRoomsNumber; ++i)
	{
		auto room = room_factory.Allocate(1);
		if (nullptr == room)
		{
			return false;
		}

		everyRoom[i] = room_factory.ConstructAt(room, id++);
	}

	return true;
}

bool
demo::Framework::StartAccepts()
{
	for (auto& [id, user] : *userManager)
	{
		user.SetOperation(iconer::app::AsyncOperations::OpReserveSession);

		if (not Schedule(user, id))
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
