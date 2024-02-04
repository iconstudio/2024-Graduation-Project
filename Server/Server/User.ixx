module;
#include "glm/glm.hpp"
#include "glm/vec3.hpp"

export module Iconer.Application.User;
import Iconer.Utility.Constraints;
import Iconer.Net.Socket;
import Iconer.Application.IContext;
import Iconer.Application.ISession;
import <cstdint>;
import <initializer_list>;
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

		constexpr User& PositionX(const float& v) noexcept
		{
			myTransform[3][0] = v;
			return *this;
		}

		[[nodiscard]]
		constexpr float& PositionX() noexcept
		{
			return myTransform[3][0];
		}

		[[nodiscard]]
		constexpr const float& PositionX() const noexcept
		{
			return myTransform[3][0];
		}

		constexpr User& PositionY(const float& v) noexcept
		{
			myTransform[3][1] = v;
			return *this;
		}

		[[nodiscard]]
		constexpr float& PositionY() noexcept
		{
			return myTransform[3][1];
		}

		[[nodiscard]]
		constexpr const float& PositionY() const noexcept
		{
			return myTransform[3][1];
		}

		constexpr User& PositionZ(const float& v) noexcept
		{
			myTransform[3][2] = v;
			return *this;
		}

		[[nodiscard]]
		constexpr float& PositionZ() noexcept
		{
			return myTransform[3][2];
		}

		[[nodiscard]]
		constexpr const float& PositionZ() const noexcept
		{
			return myTransform[3][2];
		}

		[[nodiscard]]
		constexpr glm::vec4& Positions() noexcept
		{
			return myTransform[3];
		}

		[[nodiscard]]
		constexpr const glm::vec4& Positions() const noexcept
		{
			return myTransform[3];
		}

		constexpr User& RotationLook(const std::initializer_list<float> list)
		{
			assert(list.size() == 3);
			auto it = list.begin();
			myTransform[2][0] = *(it++);
			myTransform[2][1] = *(it++);
			myTransform[2][2] = *(it++);
			return *this;
		}
		
		constexpr User& RotationLook(const float(&v)[3]) noexcept
		{
			myTransform[2][0] = v[0];
			myTransform[2][1] = v[1];
			myTransform[2][2] = v[2];
			return *this;
		}
		
		constexpr User& RotationLook(float(&&v)[3]) noexcept
		{
			myTransform[2][0] = std::move(v[0]);
			myTransform[2][1] = std::move(v[1]);
			myTransform[2][2] = std::move(v[2]);
			return *this;
		}

		constexpr User& RotationLook(const std::span<float, 3> v) noexcept
		{
			myTransform[2][0] = v[0];
			myTransform[2][1] = v[1];
			myTransform[2][2] = v[2];
			return *this;
		}

		constexpr User& RotationLook(const glm::vec4& v) noexcept
		{
			myTransform[2][0] = v[0];
			myTransform[2][1] = v[1];
			myTransform[2][2] = v[2];
			myTransform[2][3] = v[3];
			return *this;
		}

		constexpr User& RotationLook(const glm::vec3& v) noexcept
		{
			myTransform[2][0] = v[0];
			myTransform[2][1] = v[1];
			myTransform[2][2] = v[2];
			return *this;
		}

		[[nodiscard]]
		constexpr glm::vec4& RotationLook() noexcept
		{
			return myTransform[2];
		}

		[[nodiscard]]
		constexpr const glm::vec4& RotationLook() const noexcept
		{
			return myTransform[2];
		}
		
		constexpr User& RotationUp(const std::initializer_list<float> list)
		{
			assert(list.size() == 3);
			auto it = list.begin();
			myTransform[1][0] = *(it++);
			myTransform[1][1] = *(it++);
			myTransform[1][2] = *(it++);
			return *this;
		}
		
		constexpr User& RotationUp(const float(&v)[3]) noexcept
		{
			myTransform[1][0] = v[0];
			myTransform[1][1] = v[1];
			myTransform[1][2] = v[2];
			return *this;
		}
		
		constexpr User& RotationUp(float(&&v)[3]) noexcept
		{
			myTransform[1][0] = std::move(v[0]);
			myTransform[1][1] = std::move(v[1]);
			myTransform[1][2] = std::move(v[2]);
			return *this;
		}

		constexpr User& RotationUp(const std::span<float, 3> v) noexcept
		{
			myTransform[1][0] = v[0];
			myTransform[1][1] = v[1];
			myTransform[1][2] = v[2];
			return *this;
		}

		constexpr User& RotationUp(const glm::vec4& v) noexcept
		{
			myTransform[1][0] = v[0];
			myTransform[1][1] = v[1];
			myTransform[1][2] = v[2];
			myTransform[1][3] = v[3];
			return *this;
		}

		constexpr User& RotationUp(const glm::vec3& v) noexcept
		{
			myTransform[1][0] = v[0];
			myTransform[1][1] = v[1];
			myTransform[1][2] = v[2];
			return *this;
		}

		[[nodiscard]]
		constexpr glm::vec4& RotationUp() noexcept
		{
			return myTransform[1];
		}

		[[nodiscard]]
		constexpr const glm::vec4& RotationUp() const noexcept
		{
			return myTransform[1];
		}
		
		constexpr User& RotationRight(const std::initializer_list<float> list)
		{
			assert(list.size() == 3);
			auto it = list.begin();
			myTransform[0][0] = *(it++);
			myTransform[0][1] = *(it++);
			myTransform[0][2] = *(it++);
			return *this;
		}
		
		constexpr User& RotationRight(const float(&v)[3]) noexcept
		{
			myTransform[0][0] = v[0];
			myTransform[0][1] = v[1];
			myTransform[0][2] = v[2];
			return *this;
		}
		
		constexpr User& RotationRight(float(&&v)[3]) noexcept
		{
			myTransform[0][0] = std::move(v[0]);
			myTransform[0][1] = std::move(v[1]);
			myTransform[0][2] = std::move(v[2]);
			return *this;
		}

		constexpr User& RotationRight(const std::span<float, 3> v) noexcept
		{
			myTransform[0][0] = v[0];
			myTransform[0][1] = v[1];
			myTransform[0][2] = v[2];
			return *this;
		}

		constexpr User& RotationRight(const glm::vec4& v) noexcept
		{
			myTransform[0][0] = v[0];
			myTransform[0][1] = v[1];
			myTransform[0][2] = v[2];
			myTransform[0][3] = v[3];
			return *this;
		}

		constexpr User& RotationRight(const glm::vec3& v) noexcept
		{
			myTransform[0][0] = v[0];
			myTransform[0][1] = v[1];
			myTransform[0][2] = v[2];
			return *this;
		}

		[[nodiscard]]
		constexpr glm::vec4& RotationRight() noexcept
		{
			return myTransform[0];
		}

		[[nodiscard]]
		constexpr const glm::vec4& RotationRight() const noexcept
		{
			return myTransform[0];
		}

		std::wstring myName;
		iconer::net::Socket mySocket;
		volatile ptrdiff_t recvOffset;

		glm::mat4 myTransform;

	private:
		User(const User&) = delete;
		void operator=(const User&) = delete;
	};
}
