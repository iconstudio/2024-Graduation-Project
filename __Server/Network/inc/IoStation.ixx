export module Net.Io.Station;
import Net.NativeHandle;
import Iconer.Utility.Handler;
import Net.Socket;
import Net.ErrorCode;
import Net.Io.Event;
import Net.Io.Context;
import Net.Io.Schedule;
import <cstdint>;
import <limits>;
import <expected>;
import <memory>;

export namespace net::io
{
	class [[nodiscard]] Station final
		: public net::Handler<net::NativeHandle>, public std::enable_shared_from_this<Station>
	{
	public:
		using Stationary = std::expected<net::io::Station, net::ErrorCodes>;

		Station() = default;
		~Station() = default;

		net::SocketResult Register(net::Socket& socket, std::uintptr_t id) noexcept;
		bool TryRegister(net::Socket& socket, std::uintptr_t id, net::ErrorCodes& error_code) noexcept;
		bool Destroy() noexcept;
		bool Destroy(net::ErrorCodes& error_code) noexcept;

		bool Schedule(net::io::Context& context, std::uintptr_t id, unsigned long infobytes) noexcept;
		bool Schedule(net::io::Context* const context, std::uintptr_t id, unsigned long infobytes) noexcept;
		[[nodiscard]] net::io::Event WaitForIoResult() noexcept;

		[[nodiscard]] static Stationary Create() noexcept;
		[[nodiscard]] static Stationary Create(std::uint32_t concurrency_hint) noexcept;

		constexpr Station(Station&&) noexcept = default;
		constexpr Station& operator=(Station&&) noexcept = default;

	private:
		Station(net::NativeHandle&& handle) noexcept;

		Station(const Station&) = delete;
		Station& operator=(const Station&) = delete;
	};
}