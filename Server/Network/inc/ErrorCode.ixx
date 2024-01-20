module;
#include <cstdint>
#include <string>
#include <format>

export module Net.ErrorCode;
export import :General;
export import :Open;
export import :Option;
export import :Sending;
export import :Receiving;
export import :Closing;

export namespace net
{
	[[nodiscard]]
	ErrorCodes AcquireNetworkError() noexcept;
	[[nodiscard]]
	SocketOpenErrorCodes AcquireListeningError() noexcept;
	[[nodiscard]]
	SocketClosingErrorCodes AcquireClosingError() noexcept;
	[[nodiscard]]
	SendingErrorCodes AcquireSendingError() noexcept;
	[[nodiscard]]
	ReceivingErrorCodes AcquireReceivingError() noexcept;
	[[nodiscard]]
	SocketOptionErrorCodes AcquireSocketOptionError() noexcept;

	[[nodiscard]]
	constexpr bool operator==(const ErrorCodes& lhs, const SendingErrorCodes& rhs) noexcept
	{
		return static_cast<std::int32_t>(lhs) == static_cast<std::int32_t>(rhs);
	}

	[[nodiscard]]
	constexpr bool operator==(const ErrorCodes& lhs, const ReceivingErrorCodes& rhs) noexcept
	{
		return static_cast<std::int32_t>(lhs) == static_cast<std::int32_t>(rhs);
	}

	[[nodiscard]]
	constexpr bool operator==(const ErrorCodes& lhs, const SocketOpenErrorCodes& rhs) noexcept
	{
		return static_cast<std::int32_t>(lhs) == static_cast<std::int32_t>(rhs);
	}

	[[nodiscard]]
	constexpr bool operator==(const ErrorCodes& lhs, const SocketClosingErrorCodes& rhs) noexcept
	{
		return static_cast<std::int32_t>(lhs) == static_cast<std::int32_t>(rhs);
	}

	[[nodiscard]]
	constexpr bool operator==(const ErrorCodes& lhs, const SocketOptionErrorCodes& rhs) noexcept
	{
		return static_cast<std::int32_t>(lhs) == static_cast<std::int32_t>(rhs);
	}

	[[nodiscard]]
	constexpr bool operator==(const SendingErrorCodes& lhs, const ReceivingErrorCodes& rhs) noexcept
	{
		return static_cast<std::int32_t>(lhs) == static_cast<std::int32_t>(rhs);
	}

	[[nodiscard]]
	constexpr bool operator==(const ReceivingErrorCodes& lhs, const SendingErrorCodes& rhs) noexcept
	{
		return static_cast<std::int32_t>(lhs) == static_cast<std::int32_t>(rhs);
	}
}


export namespace std
{
	[[nodiscard]]
	constexpr std::string to_string(const net::ErrorCodes& err)
	{
		using namespace std::string_literals;

		switch (err)
		{
			case net::ErrorCodes::PendedIoOperation:
			{
				return "PendedIoOperation"s;
			}

			case net::ErrorCodes::WSA_IO_INCOMPLETE:
			{
				return "WSA_IO_INCOMPLETE"s;
			}

			case net::ErrorCodes::WSA_INVALID_HANDLE:
			{
				return "WSA_INVALID_HANDLE"s;
			}

			case net::ErrorCodes::WSA_INVALID_PARAMETER:
			{
				return "WSA_INVALID_PARAMETER"s;
			}

			case net::ErrorCodes::WSA_NOT_ENOUGH_MEMORY:
			{
				return "WSA_NOT_ENOUGH_MEMORY"s;
			}

			case net::ErrorCodes::OPERATION_ABORTED:
			{
				return "OPERATION_ABORTED"s;
			}

			case net::ErrorCodes::WSA_WAIT_EVENT_0:
			{
				return "WSA_WAIT_EVENT_0"s;
			}

			case net::ErrorCodes::WSA_WAIT_IO_COMPLETION:
			{
				return "WSA_WAIT_IO_COMPLETION"s;
			}

			case net::ErrorCodes::WSABASEERR:
			{
				return "WSABASEERR"s;
			}

			case net::ErrorCodes::BlockingCallsInterrupted:
			{
				return "BlockingCallsInterrupted"s;
			}

			case net::ErrorCodes::WSAEBADF:
			{
				return "WSAEBADF"s;
			}

			case net::ErrorCodes::WSAEACCES:
			{
				return "WSAEACCES"s;
			}

			case net::ErrorCodes::WSAEFAULT:
			{
				return "WSAEFAULT"s;
			}

			case net::ErrorCodes::WSAEINVAL:
			{
				return "WSAEINVAL"s;
			}

			case net::ErrorCodes::WSAEMFILE:
			{
				return "WSAEMFILE"s;
			}

			case net::ErrorCodes::NonBlockedOperation:
			{
				return "NonBlockedOperation"s;
			}

			case net::ErrorCodes::YetInProgress:
			{
				return "YetInProgress"s;
			}

			case net::ErrorCodes::WSAEALREADY:
			{
				return "WSAEALREADY"s;
			}

			case net::ErrorCodes::NotASocket:
			{
				return "NotASocket"s;
			}

			case net::ErrorCodes::WSAEDESTADDRREQ:
			{
				return "WSAEDESTADDRREQ"s;
			}

			case net::ErrorCodes::WSAEMSGSIZE:
			{
				return "WSAEMSGSIZE"s;
			}

			case net::ErrorCodes::WSAEPROTOTYPE:
			{
				return "WSAEPROTOTYPE"s;
			}

			case net::ErrorCodes::WSAENOPROTOOPT:
			{
				return "WSAENOPROTOOPT"s;
			}

			case net::ErrorCodes::WSAEPROTONOSUPPORT:
			{
				return "WSAEPROTONOSUPPORT"s;
			}

			case net::ErrorCodes::WSAESOCKTNOSUPPORT:
			{
				return "WSAESOCKTNOSUPPORT"s;
			}

			case net::ErrorCodes::NoSupportOperation:
			{
				return "NoSupportOperation"s;
			}

			case net::ErrorCodes::WSAEPFNOSUPPORT:
			{
				return "WSAEPFNOSUPPORT"s;
			}

			case net::ErrorCodes::WSAEAFNOSUPPORT:
			{
				return "WSAEAFNOSUPPORT"s;
			}

			case net::ErrorCodes::CannotUseThisAddress:
			{
				return "CannotUseThisAddress"s;
			}

			case net::ErrorCodes::WSAEADDRNOTAVAIL:
			{
				return "WSAEADDRNOTAVAIL"s;
			}

			case net::ErrorCodes::NetworkIsDown:
			{
				return "NetworkIsDown"s;
			}

			case net::ErrorCodes::WSAENETUNREACH:
			{
				return "WSAENETUNREACH"s;
			}

			case net::ErrorCodes::WSAENETRESET:
			{
				return "WSAENETRESET"s;
			}

			case net::ErrorCodes::ConnectionAborted:
			{
				return "ConnectionAborted"s;
			}

			case net::ErrorCodes::ConnectionStateReset:
			{
				return "ConnectionStateReset"s;
			}

			case net::ErrorCodes::NoBufferStorage:
			{
				return "NoBufferStorage"s;
			}

			case net::ErrorCodes::WSAEISCONN:
			{
				return "WSAEISCONN"s;
			}

			case net::ErrorCodes::NotConnected:
			{
				return "NotConnected"s;
			}

			case net::ErrorCodes::ClosedSocket:
			{
				return "ClosedSocket"s;
			}

			case net::ErrorCodes::WSAETOOMANYREFS:
			{
				return "WSAETOOMANYREFS"s;
			}

			case net::ErrorCodes::NetworkTimeOut:
			{
				return "NetworkTimeOut"s;
			}

			case net::ErrorCodes::WSAECONNREFUSED:
			{
				return "WSAECONNREFUSED"s;
			}

			case net::ErrorCodes::WSAELOOP:
			{
				return "WSAELOOP"s;
			}

			case net::ErrorCodes::WSAENAMETOOLONG:
			{
				return "WSAENAMETOOLONG"s;
			}

			case net::ErrorCodes::WSAEHOSTDOWN:
			{
				return "WSAEHOSTDOWN"s;
			}

			case net::ErrorCodes::WSAEHOSTUNREACH:
			{
				return "WSAEHOSTUNREACH"s;
			}

			case net::ErrorCodes::WSAENOTEMPTY:
			{
				return "WSAENOTEMPTY"s;
			}

			case net::ErrorCodes::WSAEPROCLIM:
			{
				return "WSAEPROCLIM"s;
			}

			case net::ErrorCodes::WSAEUSERS:
			{
				return "WSAEUSERS"s;
			}

			case net::ErrorCodes::WSAEDQUOT:
			{
				return "WSAEDQUOT"s;
			}

			case net::ErrorCodes::WSAESTALE:
			{
				return "WSAESTALE"s;
			}

			case net::ErrorCodes::WSAEREMOTE:
			{
				return "WSAEREMOTE"s;
			}

			case net::ErrorCodes::WSASYSNOTREADY:
			{
				return "WSASYSNOTREADY"s;
			}

			case net::ErrorCodes::WSAVERNOTSUPPORTED:
			{
				return "WSAVERNOTSUPPORTED"s;
			}

			case net::ErrorCodes::NotInitializedSocketSystem:
			{
				return "NotInitializedSocketSystem"s;
			}

			case net::ErrorCodes::WSAEDISCON:
			{
				return "WSAEDISCON"s;
			}

			case net::ErrorCodes::WSAENOMORE:
			{
				return "WSAENOMORE"s;
			}

			case net::ErrorCodes::WSAECANCELLED:
			{
				return "WSAECANCELLED"s;
			}

			case net::ErrorCodes::WSAEINVALIDPROCTABLE:
			{
				return "WSAEINVALIDPROCTABLE"s;
			}

			case net::ErrorCodes::WSAEINVALIDPROVIDER:
			{
				return "WSAEINVALIDPROVIDER"s;
			}

			case net::ErrorCodes::WSAEPROVIDERFAILEDINIT:
			{
				return "WSAEPROVIDERFAILEDINIT"s;
			}

			case net::ErrorCodes::WSASYSCALLFAILURE:
			{
				return "WSASYSCALLFAILURE"s;
			}

			case net::ErrorCodes::WSASERVICE_NOT_FOUND:
			{
				return "WSASERVICE_NOT_FOUND"s;
			}

			case net::ErrorCodes::WSATYPE_NOT_FOUND:
			{
				return "WSATYPE_NOT_FOUND"s;
			}

			case net::ErrorCodes::WSA_E_NO_MORE:
			{
				return "WSA_E_NO_MORE"s;
			}

			case net::ErrorCodes::WSA_E_CANCELLED:
			{
				return "WSA_E_CANCELLED"s;
			}

			case net::ErrorCodes::WSAEREFUSED:
			{
				return "WSAEREFUSED"s;
			}

			case net::ErrorCodes::WSAHOST_NOT_FOUND:
			{
				return "WSAHOST_NOT_FOUND"s;
			}

			case net::ErrorCodes::WSATRY_AGAIN:
			{
				return "WSATRY_AGAIN"s;
			}

			case net::ErrorCodes::WSANO_RECOVERY:
			{
				return "WSANO_RECOVERY"s;
			}

			case net::ErrorCodes::WSANO_DATA:
			{
				return "WSANO_DATA"s;
			}

			default:
			{
				return std::to_string(static_cast<int>(err));
			}
		}
	}
}

export template<> struct std::formatter<net::ErrorCodes>
{
	static std::format_parse_context::iterator parse(std::format_parse_context& context) noexcept
	{
		return context.begin();
	}

	static auto format(const net::ErrorCodes& err, std::format_context& context) noexcept
	{
		return std::format_to(context.out(), "{}", to_string(err));
	}
};

export template<> struct std::formatter<net::ReceivingErrorCodes>
{
	static std::format_parse_context::iterator parse(std::format_parse_context& context) noexcept
	{
		return context.begin();
	}

	static auto format(const net::ReceivingErrorCodes& err, std::format_context& context) noexcept
	{
		return std::format_to(context.out(), "{}", to_string(static_cast<net::ErrorCodes>(err)));
	}
};

export template<> struct std::formatter<net::SendingErrorCodes>
{
	static std::format_parse_context::iterator parse(std::format_parse_context& context) noexcept
	{
		return context.begin();
	}

	static auto format(const net::SendingErrorCodes& err, std::format_context& context) noexcept
	{
		return std::format_to(context.out(), "{}", to_string(static_cast<net::ErrorCodes>(err)));
	}
};

export template<> struct std::formatter<net::SocketOpenErrorCodes>
{
	static std::format_parse_context::iterator parse(std::format_parse_context& context) noexcept
	{
		return context.begin();
	}

	static auto format(const net::SocketOpenErrorCodes& err, std::format_context& context) noexcept
	{
		return std::format_to(context.out(), "{}", to_string(static_cast<net::ErrorCodes>(err)));
	}
};

export template<> struct std::formatter<net::SocketOptionErrorCodes>
{
	static std::format_parse_context::iterator parse(std::format_parse_context& context) noexcept
	{
		return context.begin();
	}

	static auto format(const net::SocketOptionErrorCodes& err, std::format_context& context) noexcept
	{
		return std::format_to(context.out(), "{}", to_string(static_cast<net::ErrorCodes>(err)));
	}
};

export template<> struct std::formatter<net::SocketClosingErrorCodes>
{
	static std::format_parse_context::iterator parse(std::format_parse_context& context) noexcept
	{
		return context.begin();
	}

	static auto format(const net::SocketClosingErrorCodes& err, std::format_context& context) noexcept
	{
		return std::format_to(context.out(), "{}", to_string(static_cast<net::ErrorCodes>(err)));
	}
};
