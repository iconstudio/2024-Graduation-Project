module;
#include <span>

export module Demo.PacketProcessor;
import Iconer.Utility.Serializer;
import Iconer.Application.BasicPacket;
import Iconer.Application.Resources.String;
import <cstdint>;

export namespace iconer::app
{
	class User;
	class Room;
}

export namespace demo
{
	class Framework;

	[[nodiscard]]
	ptrdiff_t PacketProcessor(Framework& framework, iconer::app::User& user, std::span<std::byte> packet_data, ptrdiff_t last_offset);

	void OnSignOut(iconer::app::User& user);
	void OnRequestVersion(Framework& framework, iconer::app::User& user);
	void OnRequestRoomList(Framework& framework, iconer::app::User& user);
	void OnRequestMemberList(Framework& framework, iconer::app::User& user);
	void OnCreateRoom(Framework& framework, iconer::app::User& user, const wchar_t (&room_title)[16]);
	void OnJoinRoom(Framework& framework, iconer::app::User& user, const std::int32_t& room_id);
	void OnLeaveRoom(Framework& framework, iconer::app::User& user);
	void OnGameStartSignal(Framework& framework, iconer::app::User& user);
	void OnGameLoadedSignal(Framework& framework, iconer::app::User& user);
	void OnReceivePosition(Framework& framework, iconer::app::User& user, float x, float y, float z);
	void OnReceiveRotation(Framework& framework, iconer::app::User& user, float roll, float yaw, float pitch);
}
