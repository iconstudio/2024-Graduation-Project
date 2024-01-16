module Iconer.Network.User;
import <iostream>;

iconer::User::User() noexcept
	: myStatus(this, iconer::user_status::None{}, User::_StateDelegate)
{}

void
iconer::User::OnNetworkInitialized(bool succeed, net::ErrorCodes error_code) noexcept
{
	super::OnNetworkInitialized(succeed, error_code);

	std::cout << "Print!\n";
}

void
iconer::User::_StateDelegate(User& user, state_data_t& state)
{
	state.Visit(
		[&]<typename T>(T&& value) noexcept {
			using U = std::decay_t<T>;
			if constexpr (std::same_as<U, user_status::None>)
			{}
			else if constexpr (std::same_as<U, user_status::Listening>)
			{}
			else if constexpr (std::same_as<U, user_status::Connecting>)
			{}
			else if constexpr (std::same_as<U, user_status::Idle>)
			{}
			else if constexpr (std::same_as<U, user_status::Closing>)
			{}
		});
}
