// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Interface/SagaAttackAnimationInterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaAttackAnimationInterface() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
	SAGAGAME_API UClass* Z_Construct_UClass_USagaAttackAnimationInterface();
	SAGAGAME_API UClass* Z_Construct_UClass_USagaAttackAnimationInterface_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void USagaAttackAnimationInterface::StaticRegisterNativesUSagaAttackAnimationInterface()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USagaAttackAnimationInterface);
	UClass* Z_Construct_UClass_USagaAttackAnimationInterface_NoRegister()
	{
		return USagaAttackAnimationInterface::StaticClass();
	}
	struct Z_Construct_UClass_USagaAttackAnimationInterface_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USagaAttackAnimationInterface_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInterface,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAttackAnimationInterface_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaAttackAnimationInterface_Statics::Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Interface/SagaAttackAnimationInterface.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USagaAttackAnimationInterface_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ISagaAttackAnimationInterface>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_USagaAttackAnimationInterface_Statics::ClassParams = {
		&USagaAttackAnimationInterface::StaticClass,
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
		0x000840A1u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAttackAnimationInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_USagaAttackAnimationInterface_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_USagaAttackAnimationInterface()
	{
		if (!Z_Registration_Info_UClass_USagaAttackAnimationInterface.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USagaAttackAnimationInterface.OuterSingleton, Z_Construct_UClass_USagaAttackAnimationInterface_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_USagaAttackAnimationInterface.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<USagaAttackAnimationInterface>()
	{
		return USagaAttackAnimationInterface::StaticClass();
	}
	USagaAttackAnimationInterface::USagaAttackAnimationInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(USagaAttackAnimationInterface);
	USagaAttackAnimationInterface::~USagaAttackAnimationInterface() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Interface_SagaAttackAnimationInterface_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Interface_SagaAttackAnimationInterface_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_USagaAttackAnimationInterface, USagaAttackAnimationInterface::StaticClass, TEXT("USagaAttackAnimationInterface"), &Z_Registration_Info_UClass_USagaAttackAnimationInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USagaAttackAnimationInterface), 1071105303U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Interface_SagaAttackAnimationInterface_h_2720279500(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Interface_SagaAttackAnimationInterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Interface_SagaAttackAnimationInterface_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
