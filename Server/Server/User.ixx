export module Iconer.Application.User;
import Iconer.Application.IContext;
import Iconer.Application.ISession;
import Iconer.Utility.TypeTraits;
import Iconer.Net.Socket;
import Iconer.Net.IoContext;
import <cstdint>;
import <atomic>;

export namespace iconer::app
{
	enum class [[nodiscard]] UserStates
	{
		None, Listening, Connecting, Idle, Closing, Dead
	};

	class UserContext : public IContext<UserStates>
	{
	public:
		using Super = IContext<UserStates>;

		using Super::Super;
	};

	class [[nodiscard]] User : ISession<std::int32_t>
	{
	public:
		using Super = ISession<std::int32_t>;
		using Super::HandleType;
		using Super::GetHandle;

		User(iconer::net::Socket&& socket, HandleType id) noexcept
			: Super(id)
			, mySocket(std::exchange(socket, iconer::net::Socket{})), myContext()
		{
		}

		constexpr User(User&& other) noexcept
			: Super(std::move(other).GetHandle())
			, mySocket(std::exchange(other.mySocket, iconer::net::Socket{}))
			, myContext(std::exchange(other.myContext, nullptr))
		{
		}

		virtual ~User() override
		{
			if (mySocket.IsAvailable())
			{
				std::exchange(mySocket, iconer::net::Socket{}).Close();
			}

			if (myContext)
			{
				delete myContext;
			}
		}

		constexpr User& operator=(User&& other) noexcept
		{
			myHandle = std::move(other).GetHandle();
			Name = std::move(other.Name);
			mySocket = std::exchange(other.mySocket, iconer::net::Socket{});
			myContext = std::exchange(other.myContext, nullptr);

			return *this;
		}

		bool OnAwake() override
		{
			myContext = new UserContext{ UserStates::None };
			if (nullptr == myContext)
			{
				return false;
			}

			return mySocket.IsAvailable();
		}

		void OnStart() override
		{

		}

		void OnUpdate(float dt) override
		{
		}

		void OnDestroy() override
		{
			mySocket.CloseAsync(myContext);
		}

		auto ReserveAccept(iconer::net::Socket& listener)
		{
			return listener.ReserveAccept(myContext, mySocket);
		}

		[[nodiscard]]
		UserStates GetState(std::memory_order order = std::memory_order_relaxed) const noexcept
		{
			return myContext->GetState(order);
		}

		[[nodiscard]]
		constexpr UserContext& GetContext()&
		{
			return *myContext;
		}

		[[nodiscard]]
		constexpr const UserContext& GetContext() const&
		{
			return *myContext;
		}

		[[nodiscard]]
		constexpr UserContext&& GetContext()&&
		{
			return std::move(*myContext);
		}

		[[nodiscard]]
		constexpr const UserContext&& GetContext() const&&
		{
			return std::move(*myContext);
		}

		UserContext* myContext;
		iconer::net::Socket mySocket;
	};
}
