// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Item/SagaItemBox.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaItemBox() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UParticleSystemComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaItemBox();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaItemBox_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void ASagaItemBox::StaticRegisterNativesASagaItemBox()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASagaItemBox);
	UClass* Z_Construct_UClass_ASagaItemBox_NoRegister()
	{
		return ASagaItemBox::StaticClass();
	}
	struct Z_Construct_UClass_ASagaItemBox_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Trigger_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Trigger;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Mesh;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Effect_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Effect;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASagaItemBox_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaItemBox_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaItemBox_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Item/SagaItemBox.h" },
		{ "ModuleRelativePath", "Item/SagaItemBox.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Trigger_MetaData[] = {
		{ "Category", "Box" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Item/SagaItemBox.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Trigger = { "Trigger", nullptr, (EPropertyFlags)0x00240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASagaItemBox, Trigger), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Trigger_MetaData), Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Trigger_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Mesh_MetaData[] = {
		{ "Category", "Box" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Item/SagaItemBox.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x00240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASagaItemBox, Mesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Mesh_MetaData), Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Mesh_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Effect_MetaData[] = {
		{ "Category", "Effect" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Item/SagaItemBox.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Effect = { "Effect", nullptr, (EPropertyFlags)0x00240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASagaItemBox, Effect), Z_Construct_UClass_UParticleSystemComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Effect_MetaData), Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Effect_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASagaItemBox_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Trigger,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Mesh,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASagaItemBox_Statics::NewProp_Effect,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASagaItemBox_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASagaItemBox>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASagaItemBox_Statics::ClassParams = {
		&ASagaItemBox::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ASagaItemBox_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ASagaItemBox_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaItemBox_Statics::Class_MetaDataParams), Z_Construct_UClass_ASagaItemBox_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaItemBox_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ASagaItemBox()
	{
		if (!Z_Registration_Info_UClass_ASagaItemBox.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASagaItemBox.OuterSingleton, Z_Construct_UClass_ASagaItemBox_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASagaItemBox.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<ASagaItemBox>()
	{
		return ASagaItemBox::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASagaItemBox);
	ASagaItemBox::~ASagaItemBox() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASagaItemBox, ASagaItemBox::StaticClass, TEXT("ASagaItemBox"), &Z_Registration_Info_UClass_ASagaItemBox, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASagaItemBox), 761668150U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_530331237(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
