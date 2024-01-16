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
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_Statics::ScriptStructInfo[] = {
		{ FClientNetworkStruct::StaticStruct, Z_Construct_UScriptStruct_FClientNetworkStruct_Statics::NewStructOps, TEXT("ClientNetworkStruct"), &Z_Registration_Info_UScriptStruct_ClientNetworkStruct, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FClientNetworkStruct), 354666819U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_871721306(TEXT("/Script/SagaGame"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkStructs_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
