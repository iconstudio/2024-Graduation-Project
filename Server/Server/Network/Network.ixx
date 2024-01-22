export module Iconer.Net;
import <optional>;

export namespace iconer::net
{
	enum class ErrorCode;

	/// <returns>
	/// WSAEFAULT, WSASYSNOTREADY, WSAVERNOTSUPPORTED, WSAEINPROGRESS, WSAEPROCLIM
	/// </returns>
	std::optional<ErrorCode> Startup() noexcept;
	/// <returns>
	/// WSANOTINITIALISED, WSAENETDOWN, WSAEINPROGRESS
	/// </returns>
	std::optional<ErrorCode> Cleanup() noexcept;
}
