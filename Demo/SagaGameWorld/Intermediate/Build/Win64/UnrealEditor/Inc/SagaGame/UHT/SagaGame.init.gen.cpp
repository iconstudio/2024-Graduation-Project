// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSagaGame_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_SagaGame;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_SagaGame()
	{
		if (!Z_Registration_Info_UPackage__Script_SagaGame.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/SagaGame",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x9967AA61,
				0x5FDABFDF,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_SagaGame.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_SagaGame.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_SagaGame(Z_Construct_UPackage__Script_SagaGame, TEXT("/Script/SagaGame"), Z_Registration_Info_UPackage__Script_SagaGame, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x9967AA61, 0x5FDABFDF));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
