// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Game/SagaGameState.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaGameState() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameStateBase();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaGameState();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaGameState_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void ASagaGameState::StaticRegisterNativesASagaGameState()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASagaGameState);
	UClass* Z_Construct_UClass_ASagaGameState_NoRegister()
	{
		return ASagaGameState::StaticClass();
	}
	struct Z_Construct_UClass_ASagaGameState_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASagaGameState_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameStateBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaGameState_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaGameState_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Game/SagaGameState.h" },
		{ "ModuleRelativePath", "Game/SagaGameState.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASagaGameState_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASagaGameState>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASagaGameState_Statics::ClassParams = {
		&ASagaGameState::StaticClass,
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
		0x009002A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaGameState_Statics::Class_MetaDataParams), Z_Construct_UClass_ASagaGameState_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ASagaGameState()
	{
		if (!Z_Registration_Info_UClass_ASagaGameState.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASagaGameState.OuterSingleton, Z_Construct_UClass_ASagaGameState_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASagaGameState.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<ASagaGameState>()
	{
		return ASagaGameState::StaticClass();
	}
	ASagaGameState::ASagaGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASagaGameState);
	ASagaGameState::~ASagaGameState() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameState_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameState_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASagaGameState, ASagaGameState::StaticClass, TEXT("ASagaGameState"), &Z_Registration_Info_UClass_ASagaGameState, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASagaGameState), 195234077U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameState_h_675383901(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameState_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Game_SagaGameState_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
