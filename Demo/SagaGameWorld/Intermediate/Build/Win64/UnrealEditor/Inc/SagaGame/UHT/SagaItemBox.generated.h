// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Item/SagaItemBox.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UParticleSystemComponent;
class UPrimitiveComponent;
struct FHitResult;
#ifdef SAGAGAME_SagaItemBox_generated_h
#error "SagaItemBox.generated.h already included, missing '#pragma once' in SagaItemBox.h"
#endif
#define SAGAGAME_SagaItemBox_generated_h

#define FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_SPARSE_DATA
#define FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnEffectFinished); \
	DECLARE_FUNCTION(execOnOverlapBegin);


#define FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_ACCESSORS
#define FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASagaItemBox(); \
	friend struct Z_Construct_UClass_ASagaItemBox_Statics; \
public: \
	DECLARE_CLASS(ASagaItemBox, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SagaGame"), NO_API) \
	DECLARE_SERIALIZER(ASagaItemBox)


#define FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASagaItemBox(ASagaItemBox&&); \
	NO_API ASagaItemBox(const ASagaItemBox&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASagaItemBox); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASagaItemBox); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASagaItemBox) \
	NO_API virtual ~ASagaItemBox();


#define FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_9_PROLOG
#define FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_SPARSE_DATA \
	FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_ACCESSORS \
	FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_INCLASS_NO_PURE_DECLS \
	FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SAGAGAME_API UClass* StaticClass<class ASagaItemBox>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_SagaGame_Source_SagaGame_Item_SagaItemBox_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
