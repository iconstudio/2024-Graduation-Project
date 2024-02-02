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

		explicit constexpr IoContext() noexcept
			: Super()
		{
			Internal = 0;
			InternalHigh = 0;
			hEvent = nullptr;
		}

		IoContext(IoContext&& other) noexcept
		{
			Internal = std::exchange(other.Internal, 0);
			InternalHigh = std::exchange(other.InternalHigh, 0);
			//Offset = std::exchange(other.Offset, 0);
			//OffsetHigh = std::exchange(other.OffsetHigh, 0);
			memcpy(std::addressof(Offset), std::addressof(other.Offset), sizeof(void*));
			memset(std::addressof(other.Offset), 0, sizeof(void*));
			hEvent = std::exchange(other.hEvent, nullptr);
		}

		IoContext& operator=(IoContext&& other) noexcept
		{
			Internal = std::exchange(other.Internal, 0);
			InternalHigh = std::exchange(other.InternalHigh, 0);
			memcpy(std::addressof(Offset), std::addressof(other.Offset), sizeof(void*));
			memset(std::addressof(other.Offset), 0, sizeof(void*));
			hEvent = std::exchange(other.hEvent, nullptr);

			return *this;
		}

		void Clear() noexcept
		{
			::memset(this, 0, sizeof(Super));
		}

		[[nodiscard]]
		constexpr bool operator==(const IoContext& other) const noexcept
		{
			return std::addressof(other) == this;
		}

	private:
		IoContext(const IoContext&) = delete;
		IoContext& operator=(const IoContext&) = delete;
	};
}
