module;
#include <WinSock2.h>

export module Iconer.Net.IoContext;
import <cstdint>;
import <new>;
import <utility>;

export namespace iconer::net
{
	class [[nodiscard]] IoContext : public WSAOVERLAPPED
	{
	public:
		using Super = WSAOVERLAPPED;

		constexpr IoContext() noexcept
			: Super()
		{ }

		~IoContext() noexcept = default;

		IoContext(IoContext&& other) noexcept
		{
			this->Internal = std::exchange(other.Internal, 0);
			this->InternalHigh = std::exchange(other.InternalHigh, 0);
			//this->Offset = std::exchange(other.Offset, 0);
			//this->OffsetHigh = std::exchange(other.OffsetHigh, 0);
			CopyMemory(std::addressof(Offset), std::addressof(other.Offset), sizeof(void*));
			ZeroMemory(std::addressof(other.Offset), sizeof(void*));
			this->hEvent = std::exchange(other.hEvent, nullptr);
		}

		IoContext& operator=(IoContext&& other) noexcept
		{
			this->Internal = std::exchange(other.Internal, 0);
			this->InternalHigh = std::exchange(other.InternalHigh, 0);
			CopyMemory(std::addressof(Offset), std::addressof(other.Offset), sizeof(void*));
			ZeroMemory(std::addressof(other.Offset), sizeof(void*));
			this->hEvent = std::exchange(other.hEvent, nullptr);

			return *this;
		}

		void Clear() noexcept
		{
			::ZeroMemory(this, sizeof(Super));
		}

		[[nodiscard]]
		constexpr bool operator==(const IoContext& other) const noexcept
		{
			return std::addressof(other) == this;
		}

	protected:

	private:
		IoContext(const IoContext&) = delete;
		IoContext& operator=(const IoContext&) = delete;
	};
}
