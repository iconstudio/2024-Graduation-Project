module;
#include <span>

export module Demo.Framework.PacketProcessor;
import Iconer.Application.User;
import Demo.Framework;

export namespace demo
{
	[[nodiscard]]
	ptrdiff_t PacketProcessor(Framework& framework, iconer::app::User& user, std::span<std::byte, Framework::userRecvSize> packet_data, ptrdiff_t last_offset);
}