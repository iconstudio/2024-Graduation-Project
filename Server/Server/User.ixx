export module Iconer.Application.User;
import Iconer.Application.ISession;
import Iconer.Utility.TypeTraits;
import Iconer.Net.Socket;
import Iconer.Net.IoContext;
import <cstdint>;
import <type_traits>;

export namespace iconer::app
{
	class UserContext : public iconer::net::IoContext
	{
	public:
	};

	class [[nodiscard]] User : ISession<std::int32_t>
	{
	public:
		using Super = ISession<std::int32_t>;
		using Super::HandleType;
		using Super::GetHandle;

		User(iconer::net::Socket&& socket, HandleType id) noexcept
			: Super(id)
			, mySocket(std::move(socket)), myContext()
		{
		}

		bool OnAwake() noexcept override
		{
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
			mySocket.CloseAsync(&myContext);
		}

		[[nodiscard]]
		constexpr UserContext& GetContext() & noexcept
		{
			return myContext;
		}

		[[nodiscard]]
		constexpr const UserContext& GetContext() const& noexcept
		{
			return myContext;
		}

		[[nodiscard]]
		constexpr UserContext&& GetContext() && noexcept
		{
			return std::move(myContext);
		}

		[[nodiscard]]
		constexpr const UserContext&& GetContext() const&& noexcept
		{
			return std::move(myContext);
		}

		UserContext myContext;
		iconer::net::Socket&& mySocket;
	};
}
