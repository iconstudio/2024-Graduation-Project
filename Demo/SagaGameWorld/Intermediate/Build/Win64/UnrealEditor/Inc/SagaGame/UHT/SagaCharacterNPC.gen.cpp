// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Character/SagaCharacterNPC.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaCharacterNPC() {}
// Cross Module References
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaCharacterBase();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaCharacterNPC();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaCharacterNPC_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void ASagaCharacterNPC::StaticRegisterNativesASagaCharacterNPC()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASagaCharacterNPC);
	UClass* Z_Construct_UClass_ASagaCharacterNPC_NoRegister()
	{
		return ASagaCharacterNPC::StaticClass();
	}
	struct Z_Construct_UClass_ASagaCharacterNPC_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASagaCharacterNPC_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ASagaCharacterBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaCharacterNPC_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaCharacterNPC_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Character/SagaCharacterNPC.h" },
		{ "ModuleRelativePath", "Character/SagaCharacterNPC.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASagaCharacterNPC_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASagaCharacterNPC>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASagaCharacterNPC_Statics::ClassParams = {
		&ASagaCharacterNPC::StaticClass,
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
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaCharacterNPC_Statics::Class_MetaDataParams), Z_Construct_UClass_ASagaCharacterNPC_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ASagaCharacterNPC()
	{
		if (!Z_Registration_Info_UClass_ASagaCharacterNPC.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASagaCharacterNPC.OuterSingleton, Z_Construct_UClass_ASagaCharacterNPC_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASagaCharacterNPC.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<ASagaCharacterNPC>()
	{
		return ASagaCharacterNPC::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASagaCharacterNPC);
	ASagaCharacterNPC::~ASagaCharacterNPC() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterNPC_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterNPC_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASagaCharacterNPC, ASagaCharacterNPC::StaticClass, TEXT("ASagaCharacterNPC"), &Z_Registration_Info_UClass_ASagaCharacterNPC, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASagaCharacterNPC), 1626958996U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterNPC_h_1866436657(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterNPC_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterNPC_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
