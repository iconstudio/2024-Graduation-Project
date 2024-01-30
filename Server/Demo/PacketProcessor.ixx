export module Demo.Framework.PacketProcessor;
import Iconer.Application.User;
import Demo.Framework;

export namespace demo
{
	[[nodiscard]]
	ptrdiff_t PacketProcessor(Framework& framework, const iconer::app::User& user, const Framework::IdType& user_id, iconer::app::UserStates& transit_state, std::span<std::byte, Framework::userRecvSize> packet_data, ptrdiff_t last_offset);
}