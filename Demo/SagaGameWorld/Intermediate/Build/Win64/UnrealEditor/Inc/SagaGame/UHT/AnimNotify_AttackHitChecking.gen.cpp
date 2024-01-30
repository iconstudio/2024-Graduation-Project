// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnimNotify_AttackHitChecking.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnimNotify_AttackHitChecking() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UAnimNotify();
	SAGAGAME_API UClass* Z_Construct_UClass_UAnimNotify_AttackHitChecking();
	SAGAGAME_API UClass* Z_Construct_UClass_UAnimNotify_AttackHitChecking_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void UAnimNotify_AttackHitChecking::StaticRegisterNativesUAnimNotify_AttackHitChecking()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAnimNotify_AttackHitChecking);
	UClass* Z_Construct_UClass_UAnimNotify_AttackHitChecking_NoRegister()
	{
		return UAnimNotify_AttackHitChecking::StaticClass();
	}
	struct Z_Construct_UClass_UAnimNotify_AttackHitChecking_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAnimNotify_AttackHitChecking_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAnimNotify,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimNotify_AttackHitChecking_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAnimNotify_AttackHitChecking_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "AnimNotify_AttackHitChecking.h" },
		{ "ModuleRelativePath", "AnimNotify_AttackHitChecking.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAnimNotify_AttackHitChecking_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAnimNotify_AttackHitChecking>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UAnimNotify_AttackHitChecking_Statics::ClassParams = {
		&UAnimNotify_AttackHitChecking::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001120A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAnimNotify_AttackHitChecking_Statics::Class_MetaDataParams), Z_Construct_UClass_UAnimNotify_AttackHitChecking_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UAnimNotify_AttackHitChecking()
	{
		if (!Z_Registration_Info_UClass_UAnimNotify_AttackHitChecking.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAnimNotify_AttackHitChecking.OuterSingleton, Z_Construct_UClass_UAnimNotify_AttackHitChecking_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UAnimNotify_AttackHitChecking.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<UAnimNotify_AttackHitChecking>()
	{
		return UAnimNotify_AttackHitChecking::StaticClass();
	}
	UAnimNotify_AttackHitChecking::UAnimNotify_AttackHitChecking(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAnimNotify_AttackHitChecking);
	UAnimNotify_AttackHitChecking::~UAnimNotify_AttackHitChecking() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_AnimNotify_AttackHitChecking_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_AnimNotify_AttackHitChecking_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UAnimNotify_AttackHitChecking, UAnimNotify_AttackHitChecking::StaticClass, TEXT("UAnimNotify_AttackHitChecking"), &Z_Registration_Info_UClass_UAnimNotify_AttackHitChecking, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAnimNotify_AttackHitChecking), 1707916409U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_AnimNotify_AttackHitChecking_h_359418860(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_AnimNotify_AttackHitChecking_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_AnimNotify_AttackHitChecking_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
