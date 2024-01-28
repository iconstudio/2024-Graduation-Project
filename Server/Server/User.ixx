export module Iconer.Application.User;
import Iconer.Utility.Constraints;
import Iconer.Net.Socket;
import Iconer.Application.IContext;
import Iconer.Application.ISession;
import <cstdint>;
import <atomic>;
import <span>;

export namespace iconer::app
{
	enum class [[nodiscard]] UserStates
	{
		None, Reserved, Idle, InLobby, InRoom, InGame, Dead
	};

	enum class [[nodiscard]] UserOperations
	{
		None,
		Accept,
		Connect, // Sign in
		Disconnect, // Sign out (Quit)
		Recv, Send,
		CreateRoom, EnterRoom, LeaveRoom,
		EnterGame, ReadyGame, StartGame, LeaveGame
	};

	class [[nodiscard]] User : protected ISession<std::int32_t>, public IContext<UserStates>
	{
	public:
		using Super = ISession<std::int32_t>;
		using Super::IdType;
		using Super::GetID;
		using ContextType = IContext<UserStates>;
		using SocketResult = iconer::net::Socket::SocketResult;

		[[nodiscard]]
		explicit constexpr User(const IdType& id, iconer::net::Socket&& socket)
			noexcept(nothrow_constructible<Super, const IdType&> and nothrow_default_constructibles<ContextType> and nothrow_move_constructibles<iconer::net::Socket>)
			: Super(id), ContextType()
			, mySocket(std::exchange(socket, iconer::net::Socket{}))
		{
		}

		[[nodiscard]]
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

		User(User&& other) noexcept(nothrow_move_constructibles<Super, ContextType, iconer::net::Socket>)
			: Super(std::move(other)), ContextType(std::move(other))
			, mySocket(std::exchange(other.mySocket, iconer::net::Socket{}))
		{
		}

		User& operator=(User&& other) noexcept(nothrow_move_assignables<Super, ContextType, iconer::net::Socket>)
		{
			Super::operator=(std::move(other));
			ContextType::operator=(std::move(other));
			mySocket = std::exchange(other.mySocket, iconer::net::Socket{});
			lastOperation = std::exchange(other.lastOperation, UserOperations::None);
			recvOffset = std::exchange(other.recvOffset, 0);
			return *this;
		}

		constexpr void SetOperation(UserOperations op) noexcept
		{
			lastOperation = op;
		}

		[[nodiscard]]
		constexpr UserOperations GetOperation() const noexcept
		{
			return lastOperation;
		}

		void Awake() noexcept
		{
			ContextType::Clear();
		}

		template<size_t Size>
		[[nodiscard]]
		SocketResult Receive(std::span<std::byte, Size> buffer)
		{
			if constexpr (Size == std::dynamic_extent)
			{
				return mySocket.Receive(*this, buffer, buffer.size());
			}
			else
			{
				return mySocket.Receive(*this, buffer, Size);
			}
		}

		bool Destroy() noexcept
		{
			SetOperation(UserOperations::Disconnect);
			return mySocket.CloseAsync(this);
		}

		iconer::net::Socket mySocket;
		volatile UserOperations lastOperation;
		volatile ptrdiff_t recvOffset;

	private:
		User(const User&) = delete;
		void operator=(const User&) = delete;
	};
}
