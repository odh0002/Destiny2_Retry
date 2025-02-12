// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Destiny2 : ModuleRules
{
	public Destiny2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara", "UMG" });
	}
}
