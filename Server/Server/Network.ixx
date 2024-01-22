export module Iconer.Net;

export namespace iconer::net
{
	/// <returns>
	/// WSAEFAULT, WSASYSNOTREADY, WSAVERNOTSUPPORTED, WSAEINPROGRESS, WSAEPROCLIM
	/// </returns>
	bool Startup() noexcept;
	/// <returns>
	/// WSANOTINITIALISED, WSAENETDOWN, WSAEINPROGRESS
	/// </returns>
	bool Cleanup() noexcept;
}
