// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SagaCharacterBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaCharacterBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaCharacterBase();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaCharacterBase_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void ASagaCharacterBase::StaticRegisterNativesASagaCharacterBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASagaCharacterBase);
	UClass* Z_Construct_UClass_ASagaCharacterBase_NoRegister()
	{
		return ASagaCharacterBase::StaticClass();
	}
	struct Z_Construct_UClass_ASagaCharacterBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASagaCharacterBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaCharacterBase_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaCharacterBase_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "SagaCharacterBase.h" },
		{ "ModuleRelativePath", "SagaCharacterBase.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASagaCharacterBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASagaCharacterBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASagaCharacterBase_Statics::ClassParams = {
		&ASagaCharacterBase::StaticClass,
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaCharacterBase_Statics::Class_MetaDataParams), Z_Construct_UClass_ASagaCharacterBase_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ASagaCharacterBase()
	{
		if (!Z_Registration_Info_UClass_ASagaCharacterBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASagaCharacterBase.OuterSingleton, Z_Construct_UClass_ASagaCharacterBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASagaCharacterBase.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<ASagaCharacterBase>()
	{
		return ASagaCharacterBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASagaCharacterBase);
	ASagaCharacterBase::~ASagaCharacterBase() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_SagaCharacterBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_SagaCharacterBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASagaCharacterBase, ASagaCharacterBase::StaticClass, TEXT("ASagaCharacterBase"), &Z_Registration_Info_UClass_ASagaCharacterBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASagaCharacterBase), 3142332138U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_SagaCharacterBase_h_2382460776(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_SagaCharacterBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_SagaCharacterBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
