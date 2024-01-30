// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Character/SagaComboActionData.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaComboActionData() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UPrimaryDataAsset();
	SAGAGAME_API UClass* Z_Construct_UClass_USagaComboActionData();
	SAGAGAME_API UClass* Z_Construct_UClass_USagaComboActionData_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void USagaComboActionData::StaticRegisterNativesUSagaComboActionData()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USagaComboActionData);
	UClass* Z_Construct_UClass_USagaComboActionData_NoRegister()
	{
		return USagaComboActionData::StaticClass();
	}
	struct Z_Construct_UClass_USagaComboActionData_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MontageSectionNamePrefix_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_MontageSectionNamePrefix;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxComboCount_MetaData[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_MaxComboCount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FrameRate_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_FrameRate;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_EffectiveFrameCount_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EffectiveFrameCount_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_EffectiveFrameCount;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USagaComboActionData_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UPrimaryDataAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USagaComboActionData_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaComboActionData_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Character/SagaComboActionData.h" },
		{ "ModuleRelativePath", "Character/SagaComboActionData.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaComboActionData_Statics::NewProp_MontageSectionNamePrefix_MetaData[] = {
		{ "Category", "Name" },
		{ "ModuleRelativePath", "Character/SagaComboActionData.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_USagaComboActionData_Statics::NewProp_MontageSectionNamePrefix = { "MontageSectionNamePrefix", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaComboActionData, MontageSectionNamePrefix), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaComboActionData_Statics::NewProp_MontageSectionNamePrefix_MetaData), Z_Construct_UClass_USagaComboActionData_Statics::NewProp_MontageSectionNamePrefix_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaComboActionData_Statics::NewProp_MaxComboCount_MetaData[] = {
		{ "Category", "Name" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Character/SagaComboActionData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_USagaComboActionData_Statics::NewProp_MaxComboCount = { "MaxComboCount", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaComboActionData, MaxComboCount), nullptr, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaComboActionData_Statics::NewProp_MaxComboCount_MetaData), Z_Construct_UClass_USagaComboActionData_Statics::NewProp_MaxComboCount_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaComboActionData_Statics::NewProp_FrameRate_MetaData[] = {
		{ "Category", "Name" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbd\xde\xba\xef\xbf\xbd\xef\xbf\xbd\xd7\xbc\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Character/SagaComboActionData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xde\xba\xef\xbf\xbd\xef\xbf\xbd\xd7\xbc\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USagaComboActionData_Statics::NewProp_FrameRate = { "FrameRate", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaComboActionData, FrameRate), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaComboActionData_Statics::NewProp_FrameRate_MetaData), Z_Construct_UClass_USagaComboActionData_Statics::NewProp_FrameRate_MetaData) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USagaComboActionData_Statics::NewProp_EffectiveFrameCount_Inner = { "EffectiveFrameCount", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaComboActionData_Statics::NewProp_EffectiveFrameCount_MetaData[] = {
		{ "Category", "ComboData" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd3\xb5\xef\xbf\xbd. \xef\xbf\xbd\xef\xbf\xbd\xc8\xae\xef\xbf\xbd\xef\xbf\xbd \xc5\xb8\xef\xbf\xbd\xcc\xb9\xd6\xbf\xef\xbf\xbd \xc3\xbc\xc5\xa9\xef\xbf\xbd\xc7\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd.\n" },
#endif
		{ "ModuleRelativePath", "Character/SagaComboActionData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xd3\xb5\xef\xbf\xbd. \xef\xbf\xbd\xef\xbf\xbd\xc8\xae\xef\xbf\xbd\xef\xbf\xbd \xc5\xb8\xef\xbf\xbd\xcc\xb9\xd6\xbf\xef\xbf\xbd \xc3\xbc\xc5\xa9\xef\xbf\xbd\xc7\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd." },
#endif
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_USagaComboActionData_Statics::NewProp_EffectiveFrameCount = { "EffectiveFrameCount", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaComboActionData, EffectiveFrameCount), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaComboActionData_Statics::NewProp_EffectiveFrameCount_MetaData), Z_Construct_UClass_USagaComboActionData_Statics::NewProp_EffectiveFrameCount_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USagaComboActionData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaComboActionData_Statics::NewProp_MontageSectionNamePrefix,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaComboActionData_Statics::NewProp_MaxComboCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaComboActionData_Statics::NewProp_FrameRate,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaComboActionData_Statics::NewProp_EffectiveFrameCount_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaComboActionData_Statics::NewProp_EffectiveFrameCount,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USagaComboActionData_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USagaComboActionData>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_USagaComboActionData_Statics::ClassParams = {
		&USagaComboActionData::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_USagaComboActionData_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_USagaComboActionData_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaComboActionData_Statics::Class_MetaDataParams), Z_Construct_UClass_USagaComboActionData_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USagaComboActionData_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_USagaComboActionData()
	{
		if (!Z_Registration_Info_UClass_USagaComboActionData.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USagaComboActionData.OuterSingleton, Z_Construct_UClass_USagaComboActionData_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_USagaComboActionData.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<USagaComboActionData>()
	{
		return USagaComboActionData::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(USagaComboActionData);
	USagaComboActionData::~USagaComboActionData() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaComboActionData_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaComboActionData_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_USagaComboActionData, USagaComboActionData::StaticClass, TEXT("USagaComboActionData"), &Z_Registration_Info_UClass_USagaComboActionData, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USagaComboActionData), 408305795U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaComboActionData_h_2971679149(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaComboActionData_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaComboActionData_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
