// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Game/SagaGameGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaGameGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaGameGameMode();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaGameGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void ASagaGameGameMode::StaticRegisterNativesASagaGameGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASagaGameGameMode);
	UClass* Z_Construct_UClass_ASagaGameGameMode_NoRegister()
	{
		return ASagaGameGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ASagaGameGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASagaGameGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaGameGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaGameGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Game/SagaGameGameMode.h" },
		{ "ModuleRelativePath", "Game/SagaGameGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASagaGameGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASagaGameGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASagaGameGameMode_Statics::ClassParams = {
		&ASagaGameGameMode::StaticClass,
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
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaGameGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ASagaGameGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ASagaGameGameMode()
	{
		if (!Z_Registration_Info_UClass_ASagaGameGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASagaGameGameMode.OuterSingleton, Z_Construct_UClass_ASagaGameGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASagaGameGameMode.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<ASagaGameGameMode>()
	{
		return ASagaGameGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASagaGameGameMode);
	ASagaGameGameMode::~ASagaGameGameMode() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASagaGameGameMode, ASagaGameGameMode::StaticClass, TEXT("ASagaGameGameMode"), &Z_Registration_Info_UClass_ASagaGameGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASagaGameGameMode), 180902407U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameGameMode_h_344969972(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
