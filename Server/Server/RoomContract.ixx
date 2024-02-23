export module Iconer.Application.RoomContract;
import Iconer.Utility.Constraints;
import <cstdint>;
import <atomic>;

export namespace iconer::app
{
	enum class [[nodiscard]] RoomContract : std::uint8_t
	{
		Unknown = 0 // Shall not be happened
		, CannotLocateEmptyRoom // Cannot create a room
		, NoRoomFoundWithId // Cannot find any room with a specific id
		, RoomIsFull // Full of members
		, RoomIsBusy // State mismatching
		, AnotherRoomIsAlreadyAssigned // The client already have a room id
		, UnstableRoom // Room's state is changed at time
		, ServerError // Unknown internal error
	};
}
