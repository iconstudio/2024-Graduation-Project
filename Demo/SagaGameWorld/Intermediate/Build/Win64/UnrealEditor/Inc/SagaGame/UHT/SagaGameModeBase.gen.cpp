// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Game/SagaGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaGameModeBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaGameMode();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void ASagaGameMode::StaticRegisterNativesASagaGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASagaGameMode);
	UClass* Z_Construct_UClass_ASagaGameMode_NoRegister()
	{
		return ASagaGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ASagaGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASagaGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaGameMode_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Game/SagaGameModeBase.h" },
		{ "ModuleRelativePath", "Game/SagaGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASagaGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASagaGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASagaGameMode_Statics::ClassParams = {
		&ASagaGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ASagaGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ASagaGameMode()
	{
		if (!Z_Registration_Info_UClass_ASagaGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASagaGameMode.OuterSingleton, Z_Construct_UClass_ASagaGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASagaGameMode.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<ASagaGameMode>()
	{
		return ASagaGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASagaGameMode);
	ASagaGameMode::~ASagaGameMode() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASagaGameMode, ASagaGameMode::StaticClass, TEXT("ASagaGameMode"), &Z_Registration_Info_UClass_ASagaGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASagaGameMode), 3413266777U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameModeBase_h_2223705799(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
