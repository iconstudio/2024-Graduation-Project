export module Iconer.Net.IoCompletionPort;
import Iconer.Utility.Handler;
import Iconer.Net.ErrorCode;
export import Iconer.Net.IoContext;
export import Iconer.Net.Socket;
import <cstdint>;
import <expected>;

export namespace iconer::net
{
	struct IoEvent
	{
		bool isSucceed;
		std::uint64_t eventId;
		unsigned long ioBytes;
		IoContext* ioContext;
	};

	class IoCompletionPort final : public iconer::util::Handler<void*>
	{
	public:
		explicit constexpr IoCompletionPort() noexcept = default;
		~IoCompletionPort() noexcept = default;

		net::Socket::SocketResult Register(net::Socket& socket, std::uintptr_t id) noexcept;
		bool TryRegister(net::Socket& socket, std::uintptr_t id, net::ErrorCode& error_code) noexcept;
		bool Destroy() noexcept;
		bool Destroy(ErrorCode& error_code) noexcept;

		bool Schedule(IoContext& context, std::uintptr_t id, unsigned long infobytes) noexcept;
		bool Schedule(IoContext* const context, std::uintptr_t id, unsigned long infobytes) noexcept;
		[[nodiscard]] IoEvent WaitForIoResult() noexcept;

		using FactoryResult = std::expected<IoCompletionPort, net::ErrorCode>;
		[[nodiscard]] static FactoryResult Create() noexcept;
		[[nodiscard]] static FactoryResult Create(std::uint32_t concurrency_hint) noexcept;

		constexpr IoCompletionPort(IoCompletionPort&&) noexcept = default;
		constexpr IoCompletionPort& operator=(IoCompletionPort&&) noexcept = default;

	private:
		IoCompletionPort(void* handle) noexcept;

		IoCompletionPort(const IoCompletionPort&) = delete;
		IoCompletionPort& operator=(const IoCompletionPort&) = delete;
	};
}
