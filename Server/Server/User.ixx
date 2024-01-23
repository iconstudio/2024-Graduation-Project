export module Iconer.Application.User;
import Iconer.Application.ISession;
import Iconer.Utility.TypeTraits;
export import Iconer.Net.Socket;
import <cstdint>;

export namespace iconer::app
{
	class User : ISession<std::int32_t>
	{
	public:
		using Super = ISession<std::int32_t>;

		User() = default;

		virtual ~User() noexcept override
		{
			mySocket.Close();
		}

		iconer::net::Socket mySocket;
	};
}
