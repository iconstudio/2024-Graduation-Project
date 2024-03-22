#pragma once
#include "CoreMinimal.h"
#include <limits>

UENUM(BlueprintType, Blueprintable)
enum class [[nodiscard]] EPacketProtocol : uint8
{
	UNKNOWN = 0,

	CS_SIGNIN,
	CS_SIGNOUT,
	CS_SIGNUP,

	CS_REQUEST_VERSION,
	CS_REQUEST_ROOMS,
	CS_REQUEST_USERS,

	CS_ROOM_CREATE,
	CS_ROOM_DESTROY,
	CS_ROOM_JOIN,
	CS_ROOM_MATCH,
	CS_ROOM_LEAVE,

	CS_GAME_START, // 방장
	CS_GAME_EXIT,

	CS_MY_POSITION, // 좌표
	CS_MY_TRANSFORM, // 좌표, 회전각
	CS_MY_INPUT_PRESS,
	CS_MY_INPUT_RELEASE,
	CS_MY_ANIMATION_START,
	CS_MY_ANIMATION_END,

	CS_CHAT,

	SC_SIGNIN_SUCCESS = 120,
	SC_SIGNIN_FAILURE,
	SC_SIGNUP_SUCCESS,
	SC_SIGNUP_FAILURE,

	SC_SERVER_INFO,
	SC_RESPOND_ROOMS,
	SC_RESPOND_USERS,
	SC_RESPOND_VERSION,

	SC_ROOM_CREATED_BY_SELF,
	SC_ROOM_CREATED,
	SC_ROOM_CREATE_FAILED,
	SC_ROOM_DESTROYED,
	SC_ROOM_JOINED,
	SC_ROOM_JOIN_FAILED,
	SC_ROOM_LEFT,
	SC_ROOM_MEMBER_LEFT,

	SC_GAME_START,
	SC_GAME_VICTORY,
	SC_GAME_DEFEAT,

	SC_CREATE_PLAYER,
	SC_CREATE_OBJET,
	SC_CREATE_VFX,
	SC_MOVE_CHARACTER,
	SC_MOVE_OBJET,
	SC_UPDATE_CHARACTER,
	SC_UPDATE_OBJET,
	SC_REMOVE_CHARACTER,
	SC_REMOVE_OBJET,

	SC_PLAY_SFX,
	SC_PLAY_MUSIC,
	SC_ANIMATION_START,

	SC_CHAT = std::numeric_limits<uint8>::max(),
};

namespace net
{
	using Protocol = ::EPacketProtocol;
}
