// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FireEmblemEditor : ModuleRules
{
	public FireEmblemEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                "FireEmblemEditor/Public"
            });

        PrivateIncludePaths.AddRange(
            new string[]
            {
                "FireEmblemEditor/Private"
            });

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "UnrealEd",
                "FireEmblem"
            }); 
        
        PrivateDependencyModuleNames.AddRange(
            new string[] 
            { 
                "CoreUObject", 
                "Engine", 
                "Slate",
                "SlateCore",
                "UnrealEd"
            });
    }
}
