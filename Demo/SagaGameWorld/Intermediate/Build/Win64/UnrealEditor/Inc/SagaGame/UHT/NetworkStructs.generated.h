// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Network/NetworkStructs.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SAGAGAME_NetworkStructs_generated_h
#error "NetworkStructs.generated.h already included, missing '#pragma once' in NetworkStructs.h"
#endif
#define SAGAGAME_NetworkStructs_generated_h

#define FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_21_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FClientNetworkStruct_Statics; \
	SAGAGAME_API static class UScriptStruct* StaticStruct();


template<> SAGAGAME_API UScriptStruct* StaticStruct<struct FClientNetworkStruct>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h


#define FOREACH_ENUM_EPACKETPROTOCOL(op) \
	op(EPacketProtocol::UNKNOWN) \
	op(EPacketProtocol::CS_SIGNIN) \
	op(EPacketProtocol::CS_SIGNOUT) \
	op(EPacketProtocol::CS_SIGNUP) \
	op(EPacketProtocol::CS_REQUEST_VERSION) \
	op(EPacketProtocol::CS_REQUEST_ROOMS) \
	op(EPacketProtocol::CS_REQUEST_USERS) \
	op(EPacketProtocol::CS_ROOM_CREATE) \
	op(EPacketProtocol::CS_ROOM_DESTROY) \
	op(EPacketProtocol::CS_ROOM_JOIN) \
	op(EPacketProtocol::CS_ROOM_MATCH) \
	op(EPacketProtocol::CS_ROOM_LEAVE) \
	op(EPacketProtocol::CS_GAME_START) \
	op(EPacketProtocol::CS_GAME_EXIT) \
	op(EPacketProtocol::CS_MY_POSITION) \
	op(EPacketProtocol::CS_MY_TRANSFORM) \
	op(EPacketProtocol::CS_MY_INPUT_PRESS) \
	op(EPacketProtocol::CS_MY_INPUT_RELEASE) \
	op(EPacketProtocol::CS_MY_ANIMATION_START) \
	op(EPacketProtocol::CS_MY_ANIMATION_END) \
	op(EPacketProtocol::CS_CHAT) \
	op(EPacketProtocol::SC_SIGNIN_SUCCESS) \
	op(EPacketProtocol::SC_SIGNIN_FAILURE) \
	op(EPacketProtocol::SC_SIGNUP_SUCCESS) \
	op(EPacketProtocol::SC_SIGNUP_FAILURE) \
	op(EPacketProtocol::SC_SERVER_INFO) \
	op(EPacketProtocol::SC_RESPOND_ROOMS) \
	op(EPacketProtocol::SC_RESPOND_USERS) \
	op(EPacketProtocol::SC_RESPOND_VERSION) \
	op(EPacketProtocol::SC_ROOM_CREATED_BY_SELF) \
	op(EPacketProtocol::SC_ROOM_CREATED) \
	op(EPacketProtocol::SC_ROOM_CREATE_FAILED) \
	op(EPacketProtocol::SC_ROOM_DESTROYED) \
	op(EPacketProtocol::SC_ROOM_JOINED) \
	op(EPacketProtocol::SC_ROOM_JOIN_FAILED) \
	op(EPacketProtocol::SC_ROOM_LEFT) \
	op(EPacketProtocol::SC_ROOM_MEMBER_LEFT) \
	op(EPacketProtocol::SC_GAME_START) \
	op(EPacketProtocol::SC_GAME_VICTORY) \
	op(EPacketProtocol::SC_GAME_DEFEAT) \
	op(EPacketProtocol::SC_CREATE_PLAYER) \
	op(EPacketProtocol::SC_CREATE_OBJET) \
	op(EPacketProtocol::SC_CREATE_VFX) \
	op(EPacketProtocol::SC_MOVE_CHARACTER) \
	op(EPacketProtocol::SC_MOVE_OBJET) \
	op(EPacketProtocol::SC_UPDATE_CHARACTER) \
	op(EPacketProtocol::SC_UPDATE_OBJET) \
	op(EPacketProtocol::SC_REMOVE_CHARACTER) \
	op(EPacketProtocol::SC_REMOVE_OBJET) \
	op(EPacketProtocol::SC_PLAY_SFX) \
	op(EPacketProtocol::SC_PLAY_MUSIC) \
	op(EPacketProtocol::SC_ANIMATION_START) \
	op(EPacketProtocol::SC_CHAT) 

enum class EPacketProtocol : uint8;
template<> struct TIsUEnumClass<EPacketProtocol> { enum { Value = true }; };
template<> SAGAGAME_API UEnum* StaticEnum<EPacketProtocol>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
