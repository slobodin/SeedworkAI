// Copyright (c) Mistfly Games. All Rights Reserved.

using UnrealBuildTool;

public class SeedworkAI : ModuleRules
{
    public SeedworkAI(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
        [
            "Core"
        ]);

        PrivateDependencyModuleNames.AddRange(
        [
            "CoreUObject",
            "Engine",
        ]);
    }
}
