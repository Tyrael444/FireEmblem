// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FireEmblem : ModuleRules
{
	public FireEmblem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"NavigationSystem", 
			"AIModule",
			"Niagara", 
			"EnhancedInput", 
			"GameplayAbilities", 
			"GameplayTags",
			"GameplayTasks" });
    }
}