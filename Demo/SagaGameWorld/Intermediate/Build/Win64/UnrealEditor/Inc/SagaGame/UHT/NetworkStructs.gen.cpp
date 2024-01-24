// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Network/NetworkStructs.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNetworkStructs() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	SAGAGAME_API UEnum* Z_Construct_UEnum_SagaGame_EPacketProtocol();
	SAGAGAME_API UScriptStruct* Z_Construct_UScriptStruct_FClientNetworkStruct();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ClientNetworkStruct;
class UScriptStruct* FClientNetworkStruct::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ClientNetworkStruct.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ClientNetworkStruct.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FClientNetworkStruct, (UObject*)Z_Construct_UPackage__Script_SagaGame(), TEXT("ClientNetworkStruct"));
	}
	return Z_Registration_Info_UScriptStruct_ClientNetworkStruct.OuterSingleton;
}
template<> SAGAGAME_API UScriptStruct* StaticStruct<FClientNetworkStruct>()
{
	return FClientNetworkStruct::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FClientNetworkStruct_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_id_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_id;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_pos_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_pos;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Network/NetworkStructs.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FClientNetworkStruct>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewProp_id_MetaData[] = {
		{ "Category", "ClientNetworkStruct" },
		{ "ModuleRelativePath", "Network/NetworkStructs.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FClientNetworkStruct, id), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewProp_id_MetaData), Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewProp_id_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewProp_pos_MetaData[] = {
		{ "Category", "ClientNetworkStruct" },
		{ "ModuleRelativePath", "Network/NetworkStructs.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewProp_pos = { "pos", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FClientNetworkStruct, pos), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewProp_pos_MetaData), Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewProp_pos_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewProp_id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewProp_pos,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
		nullptr,
		&NewStructOps,
		"ClientNetworkStruct",
		Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::PropPointers),
		sizeof(FClientNetworkStruct),
		alignof(FClientNetworkStruct),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000011),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FClientNetworkStruct()
	{
		if (!Z_Registration_Info_UScriptStruct_ClientNetworkStruct.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ClientNetworkStruct.InnerSingleton, Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_ClientNetworkStruct.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EPacketProtocol;
	static UEnum* EPacketProtocol_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EPacketProtocol.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EPacketProtocol.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_SagaGame_EPacketProtocol, (UObject*)Z_Construct_UPackage__Script_SagaGame(), TEXT("EPacketProtocol"));
		}
		return Z_Registration_Info_UEnum_EPacketProtocol.OuterSingleton;
	}
	template<> SAGAGAME_API UEnum* StaticEnum<EPacketProtocol>()
	{
		return EPacketProtocol_StaticEnum();
	}
	struct Z_Construct_UEnum_SagaGame_EPacketProtocol_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_SagaGame_EPacketProtocol_Statics::Enumerators[] = {
		{ "EPacketProtocol::UNKNOWN", (int64)EPacketProtocol::UNKNOWN },
		{ "EPacketProtocol::CS_SIGNIN", (int64)EPacketProtocol::CS_SIGNIN },
		{ "EPacketProtocol::CS_SIGNOUT", (int64)EPacketProtocol::CS_SIGNOUT },
		{ "EPacketProtocol::CS_SIGNUP", (int64)EPacketProtocol::CS_SIGNUP },
		{ "EPacketProtocol::CS_REQUEST_VERSION", (int64)EPacketProtocol::CS_REQUEST_VERSION },
		{ "EPacketProtocol::CS_REQUEST_ROOMS", (int64)EPacketProtocol::CS_REQUEST_ROOMS },
		{ "EPacketProtocol::CS_REQUEST_USERS", (int64)EPacketProtocol::CS_REQUEST_USERS },
		{ "EPacketProtocol::CS_ROOM_CREATE", (int64)EPacketProtocol::CS_ROOM_CREATE },
		{ "EPacketProtocol::CS_ROOM_DESTROY", (int64)EPacketProtocol::CS_ROOM_DESTROY },
		{ "EPacketProtocol::CS_ROOM_JOIN", (int64)EPacketProtocol::CS_ROOM_JOIN },
		{ "EPacketProtocol::CS_ROOM_MATCH", (int64)EPacketProtocol::CS_ROOM_MATCH },
		{ "EPacketProtocol::CS_ROOM_LEAVE", (int64)EPacketProtocol::CS_ROOM_LEAVE },
		{ "EPacketProtocol::CS_GAME_START", (int64)EPacketProtocol::CS_GAME_START },
		{ "EPacketProtocol::CS_GAME_EXIT", (int64)EPacketProtocol::CS_GAME_EXIT },
		{ "EPacketProtocol::CS_MY_POSITION", (int64)EPacketProtocol::CS_MY_POSITION },
		{ "EPacketProtocol::CS_MY_TRANSFORM", (int64)EPacketProtocol::CS_MY_TRANSFORM },
		{ "EPacketProtocol::CS_MY_INPUT_PRESS", (int64)EPacketProtocol::CS_MY_INPUT_PRESS },
		{ "EPacketProtocol::CS_MY_INPUT_RELEASE", (int64)EPacketProtocol::CS_MY_INPUT_RELEASE },
		{ "EPacketProtocol::CS_MY_ANIMATION_START", (int64)EPacketProtocol::CS_MY_ANIMATION_START },
		{ "EPacketProtocol::CS_MY_ANIMATION_END", (int64)EPacketProtocol::CS_MY_ANIMATION_END },
		{ "EPacketProtocol::CS_CHAT", (int64)EPacketProtocol::CS_CHAT },
		{ "EPacketProtocol::SC_SIGNIN_SUCCESS", (int64)EPacketProtocol::SC_SIGNIN_SUCCESS },
		{ "EPacketProtocol::SC_SIGNIN_FAILURE", (int64)EPacketProtocol::SC_SIGNIN_FAILURE },
		{ "EPacketProtocol::SC_SIGNUP_SUCCESS", (int64)EPacketProtocol::SC_SIGNUP_SUCCESS },
		{ "EPacketProtocol::SC_SIGNUP_FAILURE", (int64)EPacketProtocol::SC_SIGNUP_FAILURE },
		{ "EPacketProtocol::SC_SERVER_INFO", (int64)EPacketProtocol::SC_SERVER_INFO },
		{ "EPacketProtocol::SC_RESPOND_ROOMS", (int64)EPacketProtocol::SC_RESPOND_ROOMS },
		{ "EPacketProtocol::SC_RESPOND_USERS", (int64)EPacketProtocol::SC_RESPOND_USERS },
		{ "EPacketProtocol::SC_RESPOND_VERSION", (int64)EPacketProtocol::SC_RESPOND_VERSION },
		{ "EPacketProtocol::SC_ROOM_CREATED_BY_SELF", (int64)EPacketProtocol::SC_ROOM_CREATED_BY_SELF },
		{ "EPacketProtocol::SC_ROOM_CREATED", (int64)EPacketProtocol::SC_ROOM_CREATED },
		{ "EPacketProtocol::SC_ROOM_CREATE_FAILED", (int64)EPacketProtocol::SC_ROOM_CREATE_FAILED },
		{ "EPacketProtocol::SC_ROOM_DESTROYED", (int64)EPacketProtocol::SC_ROOM_DESTROYED },
		{ "EPacketProtocol::SC_ROOM_JOINED", (int64)EPacketProtocol::SC_ROOM_JOINED },
		{ "EPacketProtocol::SC_ROOM_JOIN_FAILED", (int64)EPacketProtocol::SC_ROOM_JOIN_FAILED },
		{ "EPacketProtocol::SC_ROOM_LEFT", (int64)EPacketProtocol::SC_ROOM_LEFT },
		{ "EPacketProtocol::SC_ROOM_MEMBER_LEFT", (int64)EPacketProtocol::SC_ROOM_MEMBER_LEFT },
		{ "EPacketProtocol::SC_GAME_START", (int64)EPacketProtocol::SC_GAME_START },
		{ "EPacketProtocol::SC_GAME_VICTORY", (int64)EPacketProtocol::SC_GAME_VICTORY },
		{ "EPacketProtocol::SC_GAME_DEFEAT", (int64)EPacketProtocol::SC_GAME_DEFEAT },
		{ "EPacketProtocol::SC_CREATE_PLAYER", (int64)EPacketProtocol::SC_CREATE_PLAYER },
		{ "EPacketProtocol::SC_CREATE_OBJET", (int64)EPacketProtocol::SC_CREATE_OBJET },
		{ "EPacketProtocol::SC_CREATE_VFX", (int64)EPacketProtocol::SC_CREATE_VFX },
		{ "EPacketProtocol::SC_MOVE_CHARACTER", (int64)EPacketProtocol::SC_MOVE_CHARACTER },
		{ "EPacketProtocol::SC_MOVE_OBJET", (int64)EPacketProtocol::SC_MOVE_OBJET },
		{ "EPacketProtocol::SC_UPDATE_CHARACTER", (int64)EPacketProtocol::SC_UPDATE_CHARACTER },
		{ "EPacketProtocol::SC_UPDATE_OBJET", (int64)EPacketProtocol::SC_UPDATE_OBJET },
		{ "EPacketProtocol::SC_REMOVE_CHARACTER", (int64)EPacketProtocol::SC_REMOVE_CHARACTER },
		{ "EPacketProtocol::SC_REMOVE_OBJET", (int64)EPacketProtocol::SC_REMOVE_OBJET },
		{ "EPacketProtocol::SC_PLAY_SFX", (int64)EPacketProtocol::SC_PLAY_SFX },
		{ "EPacketProtocol::SC_PLAY_MUSIC", (int64)EPacketProtocol::SC_PLAY_MUSIC },
		{ "EPacketProtocol::SC_ANIMATION_START", (int64)EPacketProtocol::SC_ANIMATION_START },
		{ "EPacketProtocol::SC_CHAT", (int64)EPacketProtocol::SC_CHAT },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_SagaGame_EPacketProtocol_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "CS_CHAT.Name", "EPacketProtocol::CS_CHAT" },
		{ "CS_GAME_EXIT.Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
		{ "CS_GAME_EXIT.Name", "EPacketProtocol::CS_GAME_EXIT" },
		{ "CS_GAME_EXIT.ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
		{ "CS_GAME_START.Name", "EPacketProtocol::CS_GAME_START" },
		{ "CS_MY_ANIMATION_END.Name", "EPacketProtocol::CS_MY_ANIMATION_END" },
		{ "CS_MY_ANIMATION_START.Name", "EPacketProtocol::CS_MY_ANIMATION_START" },
		{ "CS_MY_INPUT_PRESS.Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc7\xa5, \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
		{ "CS_MY_INPUT_PRESS.Name", "EPacketProtocol::CS_MY_INPUT_PRESS" },
		{ "CS_MY_INPUT_PRESS.ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc7\xa5, \xc8\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
		{ "CS_MY_INPUT_RELEASE.Name", "EPacketProtocol::CS_MY_INPUT_RELEASE" },
		{ "CS_MY_POSITION.Name", "EPacketProtocol::CS_MY_POSITION" },
		{ "CS_MY_TRANSFORM.Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xc7\xa5\n" },
		{ "CS_MY_TRANSFORM.Name", "EPacketProtocol::CS_MY_TRANSFORM" },
		{ "CS_MY_TRANSFORM.ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc7\xa5" },
		{ "CS_REQUEST_ROOMS.Name", "EPacketProtocol::CS_REQUEST_ROOMS" },
		{ "CS_REQUEST_USERS.Name", "EPacketProtocol::CS_REQUEST_USERS" },
		{ "CS_REQUEST_VERSION.Name", "EPacketProtocol::CS_REQUEST_VERSION" },
		{ "CS_ROOM_CREATE.Name", "EPacketProtocol::CS_ROOM_CREATE" },
		{ "CS_ROOM_DESTROY.Name", "EPacketProtocol::CS_ROOM_DESTROY" },
		{ "CS_ROOM_JOIN.Name", "EPacketProtocol::CS_ROOM_JOIN" },
		{ "CS_ROOM_LEAVE.Name", "EPacketProtocol::CS_ROOM_LEAVE" },
		{ "CS_ROOM_MATCH.Name", "EPacketProtocol::CS_ROOM_MATCH" },
		{ "CS_SIGNIN.Name", "EPacketProtocol::CS_SIGNIN" },
		{ "CS_SIGNOUT.Name", "EPacketProtocol::CS_SIGNOUT" },
		{ "CS_SIGNUP.Name", "EPacketProtocol::CS_SIGNUP" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Network/NetworkStructs.h" },
		{ "SC_ANIMATION_START.Name", "EPacketProtocol::SC_ANIMATION_START" },
		{ "SC_CHAT.Name", "EPacketProtocol::SC_CHAT" },
		{ "SC_CREATE_OBJET.Name", "EPacketProtocol::SC_CREATE_OBJET" },
		{ "SC_CREATE_PLAYER.Name", "EPacketProtocol::SC_CREATE_PLAYER" },
		{ "SC_CREATE_VFX.Name", "EPacketProtocol::SC_CREATE_VFX" },
		{ "SC_GAME_DEFEAT.Name", "EPacketProtocol::SC_GAME_DEFEAT" },
		{ "SC_GAME_START.Name", "EPacketProtocol::SC_GAME_START" },
		{ "SC_GAME_VICTORY.Name", "EPacketProtocol::SC_GAME_VICTORY" },
		{ "SC_MOVE_CHARACTER.Name", "EPacketProtocol::SC_MOVE_CHARACTER" },
		{ "SC_MOVE_OBJET.Name", "EPacketProtocol::SC_MOVE_OBJET" },
		{ "SC_PLAY_MUSIC.Name", "EPacketProtocol::SC_PLAY_MUSIC" },
		{ "SC_PLAY_SFX.Name", "EPacketProtocol::SC_PLAY_SFX" },
		{ "SC_REMOVE_CHARACTER.Name", "EPacketProtocol::SC_REMOVE_CHARACTER" },
		{ "SC_REMOVE_OBJET.Name", "EPacketProtocol::SC_REMOVE_OBJET" },
		{ "SC_RESPOND_ROOMS.Name", "EPacketProtocol::SC_RESPOND_ROOMS" },
		{ "SC_RESPOND_USERS.Name", "EPacketProtocol::SC_RESPOND_USERS" },
		{ "SC_RESPOND_VERSION.Name", "EPacketProtocol::SC_RESPOND_VERSION" },
		{ "SC_ROOM_CREATE_FAILED.Name", "EPacketProtocol::SC_ROOM_CREATE_FAILED" },
		{ "SC_ROOM_CREATED.Name", "EPacketProtocol::SC_ROOM_CREATED" },
		{ "SC_ROOM_CREATED_BY_SELF.Name", "EPacketProtocol::SC_ROOM_CREATED_BY_SELF" },
		{ "SC_ROOM_DESTROYED.Name", "EPacketProtocol::SC_ROOM_DESTROYED" },
		{ "SC_ROOM_JOIN_FAILED.Name", "EPacketProtocol::SC_ROOM_JOIN_FAILED" },
		{ "SC_ROOM_JOINED.Name", "EPacketProtocol::SC_ROOM_JOINED" },
		{ "SC_ROOM_LEFT.Name", "EPacketProtocol::SC_ROOM_LEFT" },
		{ "SC_ROOM_MEMBER_LEFT.Name", "EPacketProtocol::SC_ROOM_MEMBER_LEFT" },
		{ "SC_SERVER_INFO.Name", "EPacketProtocol::SC_SERVER_INFO" },
		{ "SC_SIGNIN_FAILURE.Name", "EPacketProtocol::SC_SIGNIN_FAILURE" },
		{ "SC_SIGNIN_SUCCESS.Name", "EPacketProtocol::SC_SIGNIN_SUCCESS" },
		{ "SC_SIGNUP_FAILURE.Name", "EPacketProtocol::SC_SIGNUP_FAILURE" },
		{ "SC_SIGNUP_SUCCESS.Name", "EPacketProtocol::SC_SIGNUP_SUCCESS" },
		{ "SC_UPDATE_CHARACTER.Name", "EPacketProtocol::SC_UPDATE_CHARACTER" },
		{ "SC_UPDATE_OBJET.Name", "EPacketProtocol::SC_UPDATE_OBJET" },
		{ "UNKNOWN.Name", "EPacketProtocol::UNKNOWN" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_SagaGame_EPacketProtocol_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_SagaGame,
		nullptr,
		"EPacketProtocol",
		"EPacketProtocol",
		Z_Construct_UEnum_SagaGame_EPacketProtocol_Statics::Enumerators,
		RF_Public|RF_Transient|RF_MarkAsNative,
		UE_ARRAY_COUNT(Z_Construct_UEnum_SagaGame_EPacketProtocol_Statics::Enumerators),
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_SagaGame_EPacketProtocol_Statics::Enum_MetaDataParams), Z_Construct_UEnum_SagaGame_EPacketProtocol_Statics::Enum_MetaDataParams)
	};
	UEnum* Z_Construct_UEnum_SagaGame_EPacketProtocol()
	{
		if (!Z_Registration_Info_UEnum_EPacketProtocol.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EPacketProtocol.InnerSingleton, Z_Construct_UEnum_SagaGame_EPacketProtocol_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EPacketProtocol.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_Statics::EnumInfo[] = {
		{ EPacketProtocol_StaticEnum, TEXT("EPacketProtocol"), &Z_Registration_Info_UEnum_EPacketProtocol, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 54294722U) },
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_Statics::ScriptStructInfo[] = {
		{ FClientNetworkStruct::StaticStruct, Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewStructOps, TEXT("ClientNetworkStruct"), &Z_Registration_Info_UScriptStruct_ClientNetworkStruct, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FClientNetworkStruct), 354666819U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_1112793254(TEXT("/Script/SagaGame"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_Statics::ScriptStructInfo),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
