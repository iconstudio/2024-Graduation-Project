module;
#include <iostream>

export module Iconer.Network.User;
import Iconer.Declarations;
import Iconer.Network.Entity;
import Net.Handler;

export namespace iconer
{
	class [[nodiscard]] User : public NetworkEntity<user_id_t>
	{
	public:
		using super = NetworkEntity<user_id_t>;

		constexpr User() noexcept = default;
		constexpr ~User() noexcept override = default;

		void OnNetworkIntialized(bool succeed, net::ErrorCodes error_code) noexcept override
		{
			std::cout << "Print!\n";
		}
	};
}
