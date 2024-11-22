// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FuckyouVegan7 : ModuleRules
{
	public FuckyouVegan7(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
