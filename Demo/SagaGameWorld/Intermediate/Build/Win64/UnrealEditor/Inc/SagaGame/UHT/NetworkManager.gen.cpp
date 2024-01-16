// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Network/NetworkManager.h"
#include "Network/NetworkStructs.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNetworkManager() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	SAGAGAME_API UClass* Z_Construct_UClass_ANetworkManager();
	SAGAGAME_API UClass* Z_Construct_UClass_ANetworkManager_NoRegister();
	SAGAGAME_API UScriptStruct* Z_Construct_UScriptStruct_FClientNetworkStruct();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void ANetworkManager::StaticRegisterNativesANetworkManager()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ANetworkManager);
	UClass* Z_Construct_UClass_ANetworkManager_NoRegister()
	{
		return ANetworkManager::StaticClass();
	}
	struct Z_Construct_UClass_ANetworkManager_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_cs_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_cs;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ANetworkManager_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkManager_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANetworkManager_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Network/NetworkManager.h" },
		{ "ModuleRelativePath", "Network/NetworkManager.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ANetworkManager_Statics::NewProp_cs_MetaData[] = {
		{ "Category", "NetworkManager" },
		{ "ModuleRelativePath", "Network/NetworkManager.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ANetworkManager_Statics::NewProp_cs = { "cs", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ANetworkManager, cs), Z_Construct_UScriptStruct_FClientNetworkStruct, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkManager_Statics::NewProp_cs_MetaData), Z_Construct_UClass_ANetworkManager_Statics::NewProp_cs_MetaData) }; // 354666819
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ANetworkManager_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ANetworkManager_Statics::NewProp_cs,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ANetworkManager_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANetworkManager>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ANetworkManager_Statics::ClassParams = {
		&ANetworkManager::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ANetworkManager_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkManager_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkManager_Statics::Class_MetaDataParams), Z_Construct_UClass_ANetworkManager_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANetworkManager_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ANetworkManager()
	{
		if (!Z_Registration_Info_UClass_ANetworkManager.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANetworkManager.OuterSingleton, Z_Construct_UClass_ANetworkManager_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ANetworkManager.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<ANetworkManager>()
	{
		return ANetworkManager::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ANetworkManager);
	ANetworkManager::~ANetworkManager() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ANetworkManager, ANetworkManager::StaticClass, TEXT("ANetworkManager"), &Z_Registration_Info_UClass_ANetworkManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANetworkManager), 1311450334U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_2800833420(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
