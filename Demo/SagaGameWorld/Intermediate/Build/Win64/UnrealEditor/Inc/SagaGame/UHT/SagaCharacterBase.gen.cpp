// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Character/SagaCharacterBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaCharacterBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaCharacterBase();
	SAGAGAME_API UClass* Z_Construct_UClass_ASagaCharacterBase_NoRegister();
	SAGAGAME_API UClass* Z_Construct_UClass_USagaAttackAnimationInterface_NoRegister();
	SAGAGAME_API UClass* Z_Construct_UClass_USagaCharacterControlData_NoRegister();
	SAGAGAME_API UClass* Z_Construct_UClass_USagaComboActionData_NoRegister();
	SAGAGAME_API UEnum* Z_Construct_UEnum_SagaGame_ECharacterControlType();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECharacterControlType;
	static UEnum* ECharacterControlType_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ECharacterControlType.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ECharacterControlType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_SagaGame_ECharacterControlType, (UObject*)Z_Construct_UPackage__Script_SagaGame(), TEXT("ECharacterControlType"));
		}
		return Z_Registration_Info_UEnum_ECharacterControlType.OuterSingleton;
	}
	template<> SAGAGAME_API UEnum* StaticEnum<ECharacterControlType>()
	{
		return ECharacterControlType_StaticEnum();
	}
	struct Z_Construct_UEnum_SagaGame_ECharacterControlType_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_SagaGame_ECharacterControlType_Statics::Enumerators[] = {
		{ "ECharacterControlType::Shoulder", (int64)ECharacterControlType::Shoulder },
		{ "ECharacterControlType::Quater", (int64)ECharacterControlType::Quater },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_SagaGame_ECharacterControlType_Statics::Enum_MetaDataParams[] = {
		{ "ModuleRelativePath", "Character/SagaCharacterBase.h" },
		{ "Quater.Name", "ECharacterControlType::Quater" },
		{ "Shoulder.Name", "ECharacterControlType::Shoulder" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_SagaGame_ECharacterControlType_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_SagaGame,
		nullptr,
		"ECharacterControlType",
		"ECharacterControlType",
		Z_Construct_UEnum_SagaGame_ECharacterControlType_Statics::Enumerators,
		RF_Public|RF_Transient|RF_MarkAsNative,
		UE_ARRAY_COUNT(Z_Construct_UEnum_SagaGame_ECharacterControlType_Statics::Enumerators),
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_SagaGame_ECharacterControlType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_SagaGame_ECharacterControlType_Statics::Enum_MetaDataParams)
	};
	UEnum* Z_Construct_UEnum_SagaGame_ECharacterControlType()
	{
		if (!Z_Registration_Info_UEnum_ECharacterControlType.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECharacterControlType.InnerSingleton, Z_Construct_UEnum_SagaGame_ECharacterControlType_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ECharacterControlType.InnerSingleton;
	}
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
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CharacterControlManager_ValueProp;
		static const UECodeGen_Private::FBytePropertyParams NewProp_CharacterControlManager_Key_KeyProp_Underlying;
		static const UECodeGen_Private::FEnumPropertyParams NewProp_CharacterControlManager_Key_KeyProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CharacterControlManager_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_CharacterControlManager;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ComboActionMontage_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_ComboActionMontage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ComboActionData_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_ComboActionData;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DeadMontage_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_DeadMontage;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
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
		{ "IncludePath", "Character/SagaCharacterBase.h" },
		{ "ModuleRelativePath", "Character/SagaCharacterBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_CharacterControlManager_ValueProp = { "CharacterControlManager", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UClass_USagaCharacterControlData_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_CharacterControlManager_Key_KeyProp_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_CharacterControlManager_Key_KeyProp = { "CharacterControlManager_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_SagaGame_ECharacterControlType, METADATA_PARAMS(0, nullptr) }; // 2868312813
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_CharacterControlManager_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "CharacterControl" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xd1\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xbf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xb7\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Character/SagaCharacterBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae\xef\xbf\xbd\xd1\xb5\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcd\xbf\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xd4\xb7\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_CharacterControlManager = { "CharacterControlManager", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASagaCharacterBase, CharacterControlManager), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_CharacterControlManager_MetaData), Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_CharacterControlManager_MetaData) }; // 2868312813
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_ComboActionMontage_MetaData[] = {
		{ "Category", "Animation" },
		{ "ModuleRelativePath", "Character/SagaCharacterBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_ComboActionMontage = { "ComboActionMontage", nullptr, (EPropertyFlags)0x0024080000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASagaCharacterBase, ComboActionMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_ComboActionMontage_MetaData), Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_ComboActionMontage_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_ComboActionData_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Attack" },
		{ "ModuleRelativePath", "Character/SagaCharacterBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_ComboActionData = { "ComboActionData", nullptr, (EPropertyFlags)0x0024080000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASagaCharacterBase, ComboActionData), Z_Construct_UClass_USagaComboActionData_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_ComboActionData_MetaData), Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_ComboActionData_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_DeadMontage_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Stat" },
		{ "ModuleRelativePath", "Character/SagaCharacterBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_DeadMontage = { "DeadMontage", nullptr, (EPropertyFlags)0x0024080000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASagaCharacterBase, DeadMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_DeadMontage_MetaData), Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_DeadMontage_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASagaCharacterBase_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_CharacterControlManager_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_CharacterControlManager_Key_KeyProp_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_CharacterControlManager_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_CharacterControlManager,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_ComboActionMontage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_ComboActionData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASagaCharacterBase_Statics::NewProp_DeadMontage,
	};
		const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_ASagaCharacterBase_Statics::InterfaceParams[] = {
			{ Z_Construct_UClass_USagaAttackAnimationInterface_NoRegister, (int32)VTABLE_OFFSET(ASagaCharacterBase, ISagaAttackAnimationInterface), false },  // 1071105303
		};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaCharacterBase_Statics::InterfaceParams) < 64);
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASagaCharacterBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASagaCharacterBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASagaCharacterBase_Statics::ClassParams = {
		&ASagaCharacterBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ASagaCharacterBase_Statics::PropPointers,
		InterfaceParams,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ASagaCharacterBase_Statics::PropPointers),
		UE_ARRAY_COUNT(InterfaceParams),
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaCharacterBase_Statics::Class_MetaDataParams), Z_Construct_UClass_ASagaCharacterBase_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASagaCharacterBase_Statics::PropPointers) < 2048);
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
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_Statics::EnumInfo[] = {
		{ ECharacterControlType_StaticEnum, TEXT("ECharacterControlType"), &Z_Registration_Info_UEnum_ECharacterControlType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2868312813U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASagaCharacterBase, ASagaCharacterBase::StaticClass, TEXT("ASagaCharacterBase"), &Z_Registration_Info_UClass_ASagaCharacterBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASagaCharacterBase), 283542531U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_2394186782(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
