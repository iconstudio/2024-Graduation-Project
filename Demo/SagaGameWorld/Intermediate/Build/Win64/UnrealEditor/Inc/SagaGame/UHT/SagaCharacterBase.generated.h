// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Character/SagaCharacterBase.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SAGAGAME_SagaCharacterBase_generated_h
#error "SagaCharacterBase.generated.h already included, missing '#pragma once' in SagaCharacterBase.h"
#endif
#define SAGAGAME_SagaCharacterBase_generated_h

#define FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_SPARSE_DATA
#define FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_ACCESSORS
#define FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASagaCharacterBase(); \
	friend struct Z_Construct_UClass_ASagaCharacterBase_Statics; \
public: \
	DECLARE_CLASS(ASagaCharacterBase, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SagaGame"), NO_API) \
	DECLARE_SERIALIZER(ASagaCharacterBase)


#define FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASagaCharacterBase(ASagaCharacterBase&&); \
	NO_API ASagaCharacterBase(const ASagaCharacterBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASagaCharacterBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASagaCharacterBase); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASagaCharacterBase) \
	NO_API virtual ~ASagaCharacterBase();


#define FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_16_PROLOG
#define FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_SPARSE_DATA \
	FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_ACCESSORS \
	FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_INCLASS_NO_PURE_DECLS \
	FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SAGAGAME_API UClass* StaticClass<class ASagaCharacterBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_SagaGame_Source_SagaGame_Character_SagaCharacterBase_h


#define FOREACH_ENUM_ECHARACTERCONTROLTYPE(op) \
	op(ECharacterControlType::Shoulder) \
	op(ECharacterControlType::Quater) 

enum class ECharacterControlType : uint8;
template<> struct TIsUEnumClass<ECharacterControlType> { enum { Value = true }; };
template<> SAGAGAME_API UEnum* StaticEnum<ECharacterControlType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
