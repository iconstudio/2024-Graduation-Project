export module Demo.Framework.PacketProcessor;
import Iconer.Application.User;
import Demo.Framework;
import <span>;

export namespace demo
{
	[[nodiscard]]
	ptrdiff_t PacketProcessor(Framework& framework, const iconer::app::User& user, std::span<std::byte, Framework::userRecvSize> packet_data, ptrdiff_t last_offset);
}