export module Iconer.Application.User;
import Iconer.Utility.Constraints;
import Iconer.Net.Socket;
import Iconer.Application.IContext;
import Iconer.Application.ISession;
import <cstdint>;
import <atomic>;
import <string>;
import <span>;

export namespace iconer::app
{
	enum class [[nodiscard]] UserStates
	{
		None
		, Reserved
		, Connected, PendingID, Idle
		, InLobby, InRoom
		, InGame
		, Dead
	};

	class [[nodiscard]] User : protected ISession<std::int32_t>, public IContext<UserStates>
	{
	public:
		using Super = ISession<std::int32_t>;
		using Super::IdType;
		using Super::GetID;
		using ContextType = IContext<UserStates>;
		using SendResult = iconer::net::Socket::SyncSendResult;
		using RecvResult = iconer::net::Socket::AsyncRecvResult;

		static inline constexpr size_t nicknameLength = 64;

		explicit User() = default;

		[[nodiscard]]
		explicit constexpr User(const IdType& id, iconer::net::Socket&& socket)
			noexcept(nothrow_constructible<Super, const IdType&> and nothrow_default_constructibles<std::wstring, ContextType> and nothrow_move_constructibles<iconer::net::Socket>)
			: Super(id), ContextType()
			, mySocket(std::exchange(socket, iconer::net::Socket{}))
			, myName(), recvOffset(0)
		{
		}

		[[nodiscard]]
		explicit constexpr User(IdType&& id, iconer::net::Socket&& socket)
			noexcept(nothrow_constructible<Super, IdType&&> and nothrow_default_constructibles<std::wstring, ContextType> and nothrow_move_constructibles<iconer::net::Socket>)
			: Super(std::move(id)), ContextType()
			, mySocket(std::exchange(socket, iconer::net::Socket{}))
			, myName(), recvOffset(0)
		{
		}

		~User() noexcept(nothrow_destructibles<Super, ContextType, std::wstring, iconer::net::Socket>)
		{
			if (mySocket.IsAvailable())
			{
				std::exchange(mySocket, iconer::net::Socket{}).Close();
			}
		}

		User(User&& other)
			noexcept(nothrow_move_constructibles<Super, ContextType, std::wstring, iconer::net::Socket>)
			: Super(std::move(other)), ContextType(std::move(other))
			, myName(std::exchange(other.myName, {}))
			, mySocket(std::exchange(other.mySocket, iconer::net::Socket{}))
			, recvOffset(std::exchange(other.recvOffset, 0))
		{
		}

		User& operator=(User&& other)
			noexcept(nothrow_move_assignables<Super, ContextType, std::wstring, iconer::net::Socket>)
		{
			Super::operator=(std::move(other));
			ContextType::operator=(std::move(other));
			myName = std::exchange(other.myName, {});
			mySocket = std::exchange(other.mySocket, iconer::net::Socket{});
			recvOffset = std::exchange(other.recvOffset, 0);
			return *this;
		}

		void Awake()
		{
			ContextType::Clear();
			recvOffset = 0;
			myName.reserve(nicknameLength);
		}

		void Cleanup() noexcept
		{
			ContextType::Clear();
			recvOffset = 0;
			myName.clear();
		}

		template<size_t Size>
		[[nodiscard]]
		RecvResult Send(std::span<std::byte, Size> buffer)
		{
			if constexpr (Size == std::dynamic_extent)
			{
				return mySocket.Receive(*this, buffer.subspan(recvOffset), buffer.size() - recvOffset);
			}
			else
			{
				return mySocket.Receive(*this, buffer.subspan(recvOffset), Size - recvOffset);
			}
		}

		template<size_t Size>
		[[nodiscard]]
		RecvResult Receive(std::span<std::byte, Size> buffer)
		{
			if constexpr (Size == std::dynamic_extent)
			{
				return mySocket.Receive(*this, buffer.subspan(recvOffset), buffer.size() - recvOffset);
			}
			else
			{
				return mySocket.Receive(*this, buffer.subspan(recvOffset), Size - recvOffset);
			}
		}

		SendResult SendSignInPacket();

		bool Destroy() noexcept
		{
			SetOperation(Operations::OpDisconnect);
			return mySocket.CloseAsync(this);
		}

		std::wstring myName;
		iconer::net::Socket mySocket;
		volatile ptrdiff_t recvOffset;

	private:
		User(const User&) = delete;
		void operator=(const User&) = delete;
	};
}
