// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Prog_Test : ModuleRules
{
	public Prog_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
