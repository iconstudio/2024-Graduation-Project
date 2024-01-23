// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Network/NetworkManager.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SAGAGAME_NetworkManager_generated_h
#error "NetworkManager.generated.h already included, missing '#pragma once' in NetworkManager.h"
#endif
#define SAGAGAME_NetworkManager_generated_h

#define FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_SPARSE_DATA
#define FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_ACCESSORS
#define FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesANetworkManager(); \
	friend struct Z_Construct_UClass_ANetworkManager_Statics; \
public: \
	DECLARE_CLASS(ANetworkManager, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SagaGame"), NO_API) \
	DECLARE_SERIALIZER(ANetworkManager)


#define FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ANetworkManager(ANetworkManager&&); \
	NO_API ANetworkManager(const ANetworkManager&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANetworkManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANetworkManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ANetworkManager) \
	NO_API virtual ~ANetworkManager();


#define FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_9_PROLOG
#define FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_SPARSE_DATA \
	FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_ACCESSORS \
	FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_INCLASS_NO_PURE_DECLS \
	FID_SagaGame_Source_SagaGame_Network_NetworkManager_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SAGAGAME_API UClass* StaticClass<class ANetworkManager>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_SagaGame_Source_SagaGame_Network_NetworkManager_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
