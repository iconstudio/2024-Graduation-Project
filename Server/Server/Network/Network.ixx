export module Iconer.Net;
export import Iconer.Net.ErrorCode;
import <optional>;

export namespace iconer::net
{
	std::optional<ErrorCode> Startup() noexcept;
	std::optional<ErrorCode> Cleanup() noexcept;
}
