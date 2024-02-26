export module Iconer.Application.GameContract;
import Iconer.Utility.Constraints;
import <cstdint>;
import <string>;
import <string_view>;
import <format>;

export namespace iconer::app
{
	enum class [[nodiscard]] GameContract : std::uint8_t
	{
		Success = 0
		, NotInRoom
		, ClientIsBusy // The client's state is unmatched
		, LackOfMember
		, InvalidRoom
		, InvalidOperation // Room task is invalid
		, UnstableRoom // Room's state is changed at time
		, ServerError // Unknown internal error
	};
}

export namespace std
{
	[[nodiscard]]
	constexpr string to_string(const iconer::app::GameContract& ctr)
	{
		using enum iconer::app::GameContract;
		switch (ctr)
		{
			case Success: return "Success";
			case NotInRoom: return "NotInRoom";
			case ClientIsBusy: return "ClientIsBusy";
			case LackOfMember: return "LackOfMember";
			case InvalidRoom: return "InvalidRoom";
			case InvalidOperation: return "InvalidOperation";
			case UnstableRoom: return "UnstableRoom";
			case ServerError: return "ServerError";
			default: return "Unknown";
		}
	}

	[[nodiscard]]
	constexpr wstring to_wstring(const iconer::app::GameContract& ctr)
	{
		using enum iconer::app::GameContract;
		switch (ctr)
		{
			case Success: return L"Success";
			case NotInRoom: return L"NotInRoom";
			case ClientIsBusy: return L"ClientIsBusy";
			case LackOfMember: return L"LackOfMember";
			case InvalidRoom: return L"InvalidRoom";
			case InvalidOperation: return L"InvalidOperation";
			case UnstableRoom: return L"UnstableRoom";
			case ServerError: return L"ServerError";
			default: return L"Unknown";
		}
	}
}
