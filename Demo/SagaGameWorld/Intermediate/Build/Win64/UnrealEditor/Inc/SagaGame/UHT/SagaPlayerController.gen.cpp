// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Player/SagaPlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaPlayerController() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaPlayerController();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaPlayerController_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void ASagaPlayerController::StaticRegisterNativesASagaPlayerController()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASagaPlayerController);
	UClass* Z_Construct_UClass_ASagaPlayerController_NoRegister()
	{
		return ASagaPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_ASagaPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASagaPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaPlayerController_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaPlayerController_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Player/SagaPlayerController.h" },
		{ "ModuleRelativePath", "Player/SagaPlayerController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASagaPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASagaPlayerController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASagaPlayerController_Statics::ClassParams = {
		&ASagaPlayerController::StaticClass,
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_ASagaPlayerController_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ASagaPlayerController()
	{
		if (!Z_Registration_Info_UClass_ASagaPlayerController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASagaPlayerController.OuterSingleton, Z_Construct_UClass_ASagaPlayerController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASagaPlayerController.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<ASagaPlayerController>()
	{
		return ASagaPlayerController::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASagaPlayerController);
	ASagaPlayerController::~ASagaPlayerController() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Player_SagaPlayerController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Player_SagaPlayerController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASagaPlayerController, ASagaPlayerController::StaticClass, TEXT("ASagaPlayerController"), &Z_Registration_Info_UClass_ASagaPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASagaPlayerController), 1054181165U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Player_SagaPlayerController_h_3261179824(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Player_SagaPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Player_SagaPlayerController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
