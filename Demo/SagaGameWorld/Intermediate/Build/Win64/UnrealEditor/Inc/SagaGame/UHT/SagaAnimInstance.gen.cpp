// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Animation/SagaAnimInstance.h"
#include "../../Source/Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaAnimInstance() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UAnimInstance();
	ENGINE_API UClass* Z_Construct_UClass_UCharacterMovementComponent_NoRegister();
	SAGAGAME_API UClass* Z_Construct_UClass_USagaAnimInstance();
	SAGAGAME_API UClass* Z_Construct_UClass_USagaAnimInstance_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SagaGame();
// End Cross Module References
	void USagaAnimInstance::StaticRegisterNativesUSagaAnimInstance()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USagaAnimInstance);
	UClass* Z_Construct_UClass_USagaAnimInstance_NoRegister()
	{
		return USagaAnimInstance::StaticClass();
	}
	struct Z_Construct_UClass_USagaAnimInstance_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Owner_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Owner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Movement_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Movement;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GroundSpeed_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_GroundSpeed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bIsIdle_MetaData[];
#endif
		static void NewProp_bIsIdle_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsIdle;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MovingThreshould_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_MovingThreshould;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bIsFalling_MetaData[];
#endif
		static void NewProp_bIsFalling_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsFalling;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bIsJumping_MetaData[];
#endif
		static void NewProp_bIsJumping_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsJumping;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_JumpingThreshould_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_JumpingThreshould;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USagaAnimInstance_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAnimInstance,
		(UObject* (*)())Z_Construct_UPackage__Script_SagaGame,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaAnimInstance_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "AnimInstance" },
		{ "IncludePath", "Animation/SagaAnimInstance.h" },
		{ "ModuleRelativePath", "Animation/SagaAnimInstance.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Owner_MetaData[] = {
		{ "Category", "Character" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//anim graph\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Animation/SagaAnimInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "anim graph\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Owner = { "Owner", nullptr, (EPropertyFlags)0x0024080000020015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaAnimInstance, Owner), Z_Construct_UClass_ACharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Owner_MetaData), Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Owner_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Movement_MetaData[] = {
		{ "Category", "Character" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Animation/SagaAnimInstance.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Movement = { "Movement", nullptr, (EPropertyFlags)0x00240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaAnimInstance, Movement), Z_Construct_UClass_UCharacterMovementComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Movement_MetaData), Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Movement_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Velocity_MetaData[] = {
		{ "Category", "Character" },
		{ "ModuleRelativePath", "Animation/SagaAnimInstance.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaAnimInstance, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Velocity_MetaData), Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Velocity_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_GroundSpeed_MetaData[] = {
		{ "Category", "Character" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbd\xd3\xb5\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Animation/SagaAnimInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xd3\xb5\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_GroundSpeed = { "GroundSpeed", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaAnimInstance, GroundSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_GroundSpeed_MetaData), Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_GroundSpeed_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsIdle_MetaData[] = {
		{ "Category", "Character" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//idle\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc6\xb4\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Animation/SagaAnimInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "idle\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xc6\xb4\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	void Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsIdle_SetBit(void* Obj)
	{
		((USagaAnimInstance*)Obj)->bIsIdle = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsIdle = { "bIsIdle", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(uint8), sizeof(USagaAnimInstance), &Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsIdle_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsIdle_MetaData), Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsIdle_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_MovingThreshould_MetaData[] = {
		{ "Category", "Character" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xb4\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd Idle\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Animation/SagaAnimInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xb4\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd Idle\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_MovingThreshould = { "MovingThreshould", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaAnimInstance, MovingThreshould), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_MovingThreshould_MetaData), Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_MovingThreshould_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsFalling_MetaData[] = {
		{ "Category", "Character" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Animation/SagaAnimInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	void Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsFalling_SetBit(void* Obj)
	{
		((USagaAnimInstance*)Obj)->bIsFalling = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsFalling = { "bIsFalling", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(uint8), sizeof(USagaAnimInstance), &Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsFalling_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsFalling_MetaData), Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsFalling_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsJumping_MetaData[] = {
		{ "Category", "Character" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Animation/SagaAnimInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	void Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsJumping_SetBit(void* Obj)
	{
		((USagaAnimInstance*)Obj)->bIsJumping = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsJumping = { "bIsJumping", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(uint8), sizeof(USagaAnimInstance), &Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsJumping_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsJumping_MetaData), Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsJumping_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_JumpingThreshould_MetaData[] = {
		{ "Category", "Character" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Animation/SagaAnimInstance.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_JumpingThreshould = { "JumpingThreshould", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USagaAnimInstance, JumpingThreshould), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_JumpingThreshould_MetaData), Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_JumpingThreshould_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USagaAnimInstance_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Owner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Movement,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_Velocity,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_GroundSpeed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsIdle,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_MovingThreshould,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsFalling,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_bIsJumping,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USagaAnimInstance_Statics::NewProp_JumpingThreshould,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USagaAnimInstance_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USagaAnimInstance>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_USagaAnimInstance_Statics::ClassParams = {
		&USagaAnimInstance::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_USagaAnimInstance_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::PropPointers),
		0,
		0x009000A8u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_USagaAnimInstance_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USagaAnimInstance_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_USagaAnimInstance()
	{
		if (!Z_Registration_Info_UClass_USagaAnimInstance.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USagaAnimInstance.OuterSingleton, Z_Construct_UClass_USagaAnimInstance_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_USagaAnimInstance.OuterSingleton;
	}
	template<> SAGAGAME_API UClass* StaticClass<USagaAnimInstance>()
	{
		return USagaAnimInstance::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(USagaAnimInstance);
	USagaAnimInstance::~USagaAnimInstance() {}
	struct Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Animation_SagaAnimInstance_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Animation_SagaAnimInstance_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_USagaAnimInstance, USagaAnimInstance::StaticClass, TEXT("USagaAnimInstance"), &Z_Registration_Info_UClass_USagaAnimInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USagaAnimInstance), 1528047536U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Animation_SagaAnimInstance_h_4140068408(TEXT("/Script/SagaGame"),
		Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Animation_SagaAnimInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_SagaGame_Source_SagaGame_Animation_SagaAnimInstance_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
