module Iconer.Network.User;
import <iostream>;

//: myStatus(this, iconer::user_status::None{}, User::StateDelegate)

void
iconer::User::OnNetworkInitialized(bool succeed, net::ErrorCodes error_code) noexcept
{
	super::OnNetworkInitialized(succeed, error_code);

	std::cout << "Print!\n";
}

void
iconer::User::StateDelegate(User* user, state_data_t& state, void* arguments)
{
	state.Visit(
		[&]<typename T>(T&& value) noexcept{
			using U = std::decay_t<T>;
			if constexpr (std::same_as<U, user_status::None>)
			{
				//std::cout << "Player Status: None\n";
			}
			else if constexpr (std::same_as<U, user_status::Listening>)
			{
				//std::cout << "Player Status: Listening\n";
			}
			else if constexpr (std::same_as<U, user_status::Connecting>)
			{
				//std::cout << "Player Status: Connecting\n";
			}
			else if constexpr (std::same_as<U, user_status::Idle>)
			{
				//std::cout << "Player Status: Idle\n";
			}
			else if constexpr (std::same_as<U, user_status::Closing>)
			{
				//std::cout << "Player Status: Closing\n";
			}
		});
}
