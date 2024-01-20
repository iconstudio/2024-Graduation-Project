// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SagaGame : ModuleRules
{
	public SagaGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "SagaGame" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Networking" });
	}
}
