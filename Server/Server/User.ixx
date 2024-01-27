export module Iconer.Application.User;
import Iconer.Utility.Constraints;
import Iconer.Net.Socket;
import Iconer.Application.IContext;
import Iconer.Application.ISession;
import <cstdint>;
import <atomic>;

export namespace iconer::app
{
	enum class [[nodiscard]] UserStates
	{
		None, Listening, Connecting, Idle, Closing, Dead
	};

	class [[nodiscard]] User : protected ISession<std::int32_t>, public IContext<UserStates>
	{
	public:
		using Super = ISession<std::int32_t>;
		using Super::IdType;
		using Super::GetID;
		using ContextType = IContext<UserStates>;

		explicit constexpr User(const IdType& id, iconer::net::Socket&& socket)
			noexcept(nothrow_constructible<Super, const IdType&> and nothrow_default_constructibles<ContextType> and nothrow_move_constructibles<iconer::net::Socket>)
			: Super(id), ContextType()
			, mySocket(std::exchange(socket, iconer::net::Socket{}))
		{
		}

		explicit constexpr User(IdType&& id, iconer::net::Socket&& socket)
			noexcept(nothrow_constructible<Super, IdType&&> and nothrow_default_constructibles<ContextType> and nothrow_move_constructibles<iconer::net::Socket>)
			: Super(std::move(id)), ContextType()
			, mySocket(std::exchange(socket, iconer::net::Socket{}))
		{
		}

		~User() noexcept(nothrow_destructibles<Super, ContextType, iconer::net::Socket> and noexcept(std::declval<iconer::net::Socket>().Close()))
		{
			if (mySocket.IsAvailable())
			{
				std::exchange(mySocket, iconer::net::Socket{}).Close();
			}
		}

		bool OnAwake()
		{
			return mySocket.IsAvailable();
		}

		void Destroy()
		{
			mySocket.CloseAsync(this);
		}

		auto ReserveAccept(iconer::net::Socket& listener)
		{
			return listener.ReserveAccept(this, mySocket);
		}

		User(User&&) noexcept(nothrow_move_constructibles<Super, ContextType>) = default;
		User& operator=(User&&) noexcept(nothrow_move_assignables<Super, ContextType>) = default;

		iconer::net::Socket mySocket;

	private:
		User(const User&) = delete;
		void operator=(const User&) = delete;
	};
}
