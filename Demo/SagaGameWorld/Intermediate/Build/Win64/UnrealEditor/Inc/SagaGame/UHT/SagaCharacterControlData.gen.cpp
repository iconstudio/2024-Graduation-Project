// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Character/SagaCharacterControlData.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaCharacterControlData() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
	ENGINE_API UClass* Z_Construct_UClass_UPrimaryDataAsset();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
	SAGAGAME_API UClass* Z_Construct_UClass_USagaCharacterControlData();
	SAGAGAME_API UClass* Z_Construct_UClass_USagaCharacterControlData_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void USagaCharacterControlData::StaticRegisterNativesUSagaCharacterControlData()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USagaCharacterControlData);
	UClass* Z_Construct_UClass_USagaCharacterControlData_NoRegister()
	{
		return USagaCharacterControlData::StaticClass();
	}
	struct Z_Construct_UClass_USagaCharacterControlData_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bUseControllerRotationYaw_MetaData[];
#endif
		static void NewProp_bUseControllerRotationYaw_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseControllerRotationYaw;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bOrientRotationToMovement_MetaData[];
#endif
		static void NewProp_bOrientRotationToMovement_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bOrientRotationToMovement;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bUseControllerDesiredRotation_MetaData[];
#endif
		static void NewProp_bUseControllerDesiredRotation_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseControllerDesiredRotation;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RotationRate_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_RotationRate;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InputMappingContext_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_InputMappingContext;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TargetArmLength_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_TargetArmLength;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RelativeRotation_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_RelativeRotation;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bUsePawnControlRotation_MetaData[];
#endif
		static void NewProp_bUsePawnControlRotation_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bUsePawnControlRotation;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bInheritPitch_MetaData[];
#endif
		static void NewProp_bInheritPitch_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bInheritPitch;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bInheritYaw_MetaData[];
#endif
		static void NewProp_bInheritYaw_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bInheritYaw;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bInheritRoll_MetaData[];
#endif
		static void NewProp_bInheritRoll_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bInheritRoll;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bDoCollisionTest_MetaData[];
#endif
		static void NewProp_bDoCollisionTest_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bDoCollisionTest;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USagaCharacterControlData_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UPrimaryDataAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Character/SagaCharacterControlData.h" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerRotationYaw_MetaData[] = {
		{ "Category", "Pawn" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
	void Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerRotationYaw_SetBit(void* Obj)
	{
		((USagaCharacterControlData*)Obj)->bUseControllerRotationYaw = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerRotationYaw = { "bUseControllerRotationYaw", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(uint8), sizeof(USagaCharacterControlData), &Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerRotationYaw_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerRotationYaw_MetaData), Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerRotationYaw_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bOrientRotationToMovement_MetaData[] = {
		{ "Category", "CharacterMovement" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
	void Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bOrientRotationToMovement_SetBit(void* Obj)
	{
		((USagaCharacterControlData*)Obj)->bOrientRotationToMovement = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bOrientRotationToMovement = { "bOrientRotationToMovement", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(uint8), sizeof(USagaCharacterControlData), &Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bOrientRotationToMovement_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bOrientRotationToMovement_MetaData), Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bOrientRotationToMovement_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerDesiredRotation_MetaData[] = {
		{ "Category", "CharacterMovement" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
	void Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerDesiredRotation_SetBit(void* Obj)
	{
		((USagaCharacterControlData*)Obj)->bUseControllerDesiredRotation = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerDesiredRotation = { "bUseControllerDesiredRotation", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(uint8), sizeof(USagaCharacterControlData), &Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerDesiredRotation_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerDesiredRotation_MetaData), Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerDesiredRotation_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_RotationRate_MetaData[] = {
		{ "Category", "CharacterMovement" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_RotationRate = { "RotationRate", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaCharacterControlData, RotationRate), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_RotationRate_MetaData), Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_RotationRate_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_InputMappingContext_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_InputMappingContext = { "InputMappingContext", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaCharacterControlData, InputMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_InputMappingContext_MetaData), Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_InputMappingContext_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_TargetArmLength_MetaData[] = {
		{ "Category", "SpringArm" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_TargetArmLength = { "TargetArmLength", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaCharacterControlData, TargetArmLength), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_TargetArmLength_MetaData), Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_TargetArmLength_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_RelativeRotation_MetaData[] = {
		{ "Category", "SpringArm" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_RelativeRotation = { "RelativeRotation", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaCharacterControlData, RelativeRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_RelativeRotation_MetaData), Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_RelativeRotation_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUsePawnControlRotation_MetaData[] = {
		{ "Category", "SpringArm" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
	void Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUsePawnControlRotation_SetBit(void* Obj)
	{
		((USagaCharacterControlData*)Obj)->bUsePawnControlRotation = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUsePawnControlRotation = { "bUsePawnControlRotation", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(uint8), sizeof(USagaCharacterControlData), &Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUsePawnControlRotation_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUsePawnControlRotation_MetaData), Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUsePawnControlRotation_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritPitch_MetaData[] = {
		{ "Category", "SpringArm" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
	void Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritPitch_SetBit(void* Obj)
	{
		((USagaCharacterControlData*)Obj)->bInheritPitch = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritPitch = { "bInheritPitch", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(uint8), sizeof(USagaCharacterControlData), &Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritPitch_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritPitch_MetaData), Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritPitch_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritYaw_MetaData[] = {
		{ "Category", "SpringArm" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
	void Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritYaw_SetBit(void* Obj)
	{
		((USagaCharacterControlData*)Obj)->bInheritYaw = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritYaw = { "bInheritYaw", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(uint8), sizeof(USagaCharacterControlData), &Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritYaw_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritYaw_MetaData), Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritYaw_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritRoll_MetaData[] = {
		{ "Category", "SpringArm" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
	void Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritRoll_SetBit(void* Obj)
	{
		((USagaCharacterControlData*)Obj)->bInheritRoll = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritRoll = { "bInheritRoll", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(uint8), sizeof(USagaCharacterControlData), &Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritRoll_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritRoll_MetaData), Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritRoll_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bDoCollisionTest_MetaData[] = {
		{ "Category", "SpringArm" },
		{ "ModuleRelativePath", "Character/SagaCharacterControlData.h" },
	};
#endif
	void Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bDoCollisionTest_SetBit(void* Obj)
	{
		((USagaCharacterControlData*)Obj)->bDoCollisionTest = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bDoCollisionTest = { "bDoCollisionTest", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(uint8), sizeof(USagaCharacterControlData), &Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bDoCollisionTest_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bDoCollisionTest_MetaData), Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bDoCollisionTest_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USagaCharacterControlData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerRotationYaw,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bOrientRotationToMovement,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUseControllerDesiredRotation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_RotationRate,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_InputMappingContext,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_TargetArmLength,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_RelativeRotation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bUsePawnControlRotation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritPitch,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritYaw,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bInheritRoll,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaCharacterControlData_Statics::NewProp_bDoCollisionTest,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USagaCharacterControlData_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USagaCharacterControlData>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_USagaCharacterControlData_Statics::ClassParams = {
		&USagaCharacterControlData::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_USagaCharacterControlData_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::Class_MetaDataParams), Z_Construct_UClass_USagaCharacterControlData_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USagaCharacterControlData_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_USagaCharacterControlData()
	{
		if (!Z_Registration_Info_UClass_USagaCharacterControlData.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USagaCharacterControlData.OuterSingleton, Z_Construct_UClass_USagaCharacterControlData_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_USagaCharacterControlData.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<USagaCharacterControlData>()
	{
		return USagaCharacterControlData::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(USagaCharacterControlData);
	USagaCharacterControlData::~USagaCharacterControlData() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterControlData_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterControlData_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_USagaCharacterControlData, USagaCharacterControlData::StaticClass, TEXT("USagaCharacterControlData"), &Z_Registration_Info_UClass_USagaCharacterControlData, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USagaCharacterControlData), 577681184U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterControlData_h_4251752429(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterControlData_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Character_SagaCharacterControlData_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
